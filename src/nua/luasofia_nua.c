/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 *
 * This file is part of Luasofia.
 *
 * Luasofia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Luasofia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "su/luasofia_su_root.h"
#include "utils/luasofia_weak_table.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"
#include "nua/luasofia_nua_handle.h"

#include <sofia-sip/nua.h>
#include <sofia-sip/nua_tag.h>
#include <sofia-sip/soa_tag.h>
#include <sofia-sip/su_tag_io.h>

typedef struct luasofia_nua_s luasofia_nua_t;

#define NUA_MTABLE              "luasofia_nua_t"

#define NUA_EVENT_DEFAULT_INDEX -10

#define ENV_CALLBACK_INDEX      1
#define ENV_MAGIC_INDEX         2

struct luasofia_nua_s {
    nua_t *nua;
};

static int luasofia_nua_set_params(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_t) */
    su_home_t *home = su_home_create();
    luasofia_nua_t *lnua = (luasofia_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);
    tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

    nua_set_params(lnua->nua, TAG_NEXT(tags));
    su_home_unref(home);
    return 0;
}

static int luasofia_nua_create_handle(lua_State *L)
{
    luasofia_nua_t *lnua = NULL;

    /* get and check first argument (should be a nua_t) */
    lnua = (luasofia_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    return luasofia_nua_handle_create(L, lnua->nua);
}

static int luasofia_nua_destroy(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_t) */
    luasofia_nua_t *lnua = (luasofia_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    if (lnua->nua) {
        /* remove lnua of the luasofia weak table */
        luasofia_weak_table_remove(L, lnua->nua);

        nua_shutdown(lnua->nua);
        lnua->nua = NULL;
    }
    return 0;
}

static int luasofia_nua_shutdown(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_t) */
    luasofia_nua_t *lnua = (luasofia_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);
    nua_shutdown(lnua->nua);
    return 0;
}

/* NUA event callback */
static void nua_event_callback(nua_event_t event,
                               int status, char const *phrase,
                               nua_t *nua, nua_magic_t *magic,
                               nua_handle_t *nh, nua_hmagic_t *hmagic,
                               sip_t const *sip,
                               tagi_t tags[])
{
    lua_State *L = (lua_State *)magic;

    //printf("nua_event_callback: event[%d] status[%d] phrase[%s] nua[%p] magic[%p] sip[%p] tags[%p]\n",
    //       event, status, phrase, nua, magic, sip, tags);

    /* put nua userdatum at stack and check if it is ok. */
    luasofia_weak_table_get(L, nua);

    if (lua_isnil(L, -1)) {
        if (event == nua_r_shutdown && status >= 200) {
            nua_destroy(nua);
        }
        return;
    }
    luaL_checkudata(L, -1, NUA_MTABLE);

    /* put env table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        return;
    }

    /* put callback table at stack */
    lua_rawgeti(L, -1, ENV_CALLBACK_INDEX);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 3);
        return;
    }

    /* get event callback */
    lua_rawgeti(L, -1, event);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        /* get event default callback */
        lua_rawgeti(L, -1, NUA_EVENT_DEFAULT_INDEX);
        if (lua_isnil(L, -1)) {
            lua_pop(L, 4);
            return;
        }
    }

    lua_pushinteger(L, event);
    lua_pushinteger(L, status);
    lua_pushstring(L, phrase);
    lua_pushvalue(L, -7);

    /* get magic field */
    lua_rawgeti(L, -7, ENV_MAGIC_INDEX);

    if (nh) { 
        /* put nua_handle userdatum at stack */
        luasofia_weak_table_get(L, nh);
        if (lua_isnil(L, -1)) {
            /* create a new nua_handle userdatum */
            lua_pop(L, 1);
            luasofia_nua_handle_create_userdata(L, nh);
            lua_pushnil(L);
        } else {
            /* check if it is a nua_handle */
            luaL_checkudata(L, -1, NUA_HANDLE_MTABLE);
            
            /* put env table at stack */
            lua_getfenv(L, -1);
        }
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
    }

    sip ? lua_pushlightuserdata(L, (void*)sip) : lua_pushnil(L);

    tags ? lua_pushlightuserdata(L, (void*)tags) : lua_pushnil(L);

    lua_call(L, 9, 0);
    lua_pop(L, 3);
}

static int luasofia_nua_create(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;
    luasofia_nua_t *lnua = NULL;
    nua_t *nua = NULL;
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();

    /* get and check first argument (should be a root_t) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, 1, SU_ROOT_MTABLE);

    /* check the callback table */
    if (!lua_isnoneornil(L, 2))
        luaL_checktype(L, 2, LUA_TTABLE);

    tags = luasofia_tags_table_to_taglist(L, 4, home);

    /* create a nua object */
    lnua = (luasofia_nua_t*) lua_newuserdata(L, sizeof(luasofia_nua_t));

    /* create the nua_t */
    nua = nua_create(lroot->root, nua_event_callback, L, TAG_NEXT(tags));
    if (!nua)
        luaL_error(L, "nua_create failed!");

    /* save nua object */
    lnua->nua = nua;

    /* set its metatable */
    luaL_getmetatable(L, NUA_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua at luasofia weak table */
    luasofia_weak_table_set(L, nua);

    /* create env table */
    lua_createtable(L, 2, 0);

    /* save second argument (callbacks) on env table */
    if (!lua_isnoneornil(L, 2)) {
        lua_pushvalue(L, 2);
        lua_rawseti(L, -2, ENV_CALLBACK_INDEX);
    }

    /* save third argument (magic) on env table */
    if (!lua_isnoneornil(L, 3)) {
        lua_pushvalue(L, 3);
        lua_rawseti(L, -2, ENV_MAGIC_INDEX);
    }

    /* set env table as environment for udata */
    lua_setfenv(L, -2);

    su_home_unref(home);
    return 1;
}

static int luasofia_nua_event_name(lua_State *L)
{
    nua_event_t event = lua_tointeger(L, -1);
    char const *name = nua_event_name(event);
    lua_pushstring(L, name);
    return 1;
}

static const luaL_Reg nua_meths[] = {
    {"set_params",    luasofia_nua_set_params },
    {"handle_create", luasofia_nua_create_handle },
    {"shutdown",      luasofia_nua_shutdown },
    {"__gc",          luasofia_nua_destroy },
    {NULL, NULL}
};

static const luaL_Reg nua_lib[] = {
    {"create", luasofia_nua_create },
    {"event_name", luasofia_nua_event_name },
    {NULL, NULL}
};

static const luasofia_tag_reg_t nua_tags[] = {
    {"NUTAG_ANY", nutag_any },
    {"NUTAG_URL", nutag_url },
    {"NUTAG_ADDRESS", nutag_address },
    {"NUTAG_WITH", nutag_with },
    {"NUTAG_DIALOG", nutag_dialog },
    {"NUTAG_METHOD", nutag_method },
    {"NUTAG_MAX_SUBSCRIPTIONS", nutag_max_subscriptions },
    {"NUTAG_UICC", nutag_uicc },
    {"NUTAG_USE_DIALOG", nutag_use_dialog },
    {"NUTAG_RETRY_COUNT", nutag_retry_count },
    {"NUTAG_SOA_NAME", nutag_soa_name },
    {"NUTAG_EARLY_MEDIA", nutag_early_media },
    {"NUTAG_ONLY183_100REL", nutag_only183_100rel },
    {"NUTAG_EARLY_ANSWER", nutag_early_answer },
    {"NUTAG_INCLUDE_EXTRA_SDP", nutag_include_extra_sdp },
    {"NUTAG_INVITE_TIMER", nutag_invite_timer },
    {"NUTAG_SESSION_TIMER", nutag_session_timer },
    {"NUTAG_MIN_SE", nutag_min_se },
    {"NUTAG_SESSION_REFRESHER", nutag_session_refresher },
    {"NUTAG_UPDATE_REFRESH", nutag_update_refresh },
    {"NUTAG_REFRESH_WITHOUT_SDP", nutag_refresh_without_sdp },
    {"NUTAG_AUTOALERT", nutag_autoalert },
    {"NUTAG_AUTOACK", nutag_autoack },
    {"NUTAG_AUTOANSWER", nutag_autoanswer },
    {"NUTAG_ENABLEINVITE", nutag_enableinvite },
    {"NUTAG_ENABLEMESSAGE", nutag_enablemessage },
    {"NUTAG_ENABLEMESSENGER", nutag_enablemessenger },
    {"NUTAG_SMIME_ENABLE", nutag_smime_enable },
    {"NUTAG_SMIME_OPT", nutag_smime_opt },
    {"NUTAG_SMIME_PROTECTION_MODE", nutag_smime_protection_mode },
    {"NUTAG_SMIME_MESSAGE_DIGEST", nutag_smime_message_digest },
    {"NUTAG_SMIME_SIGNATURE", nutag_smime_signature },
    {"NUTAG_SMIME_KEY_ENCRYPTION", nutag_smime_key_encryption },
    {"NUTAG_SMIME_MESSAGE_ENCRYPTION", nutag_smime_message_encryption },
    {"NUTAG_CERTIFICATE_DIR", nutag_certificate_dir },
    {"NUTAG_CERTIFICATE_PHRASE", nutag_certificate_phrase },
    {"NUTAG_SIPS_URL", nutag_sips_url },
    {"NUTAG_PROXY",  ntatag_default_proxy },
    {"NUTAG_INITIAL_ROUTE", nutag_initial_route },
    {"NUTAG_INITIAL_ROUTE_STR", nutag_initial_route_str },
    {"NUTAG_REGISTRAR", nutag_registrar },
    {"NUTAG_OUTBOUND", nutag_outbound },
    {"NUTAG_AUTH", nutag_auth },
    {"NUTAG_AUTH_CACHE", nutag_auth_cache },
    {"NUTAG_KEEPALIVE", nutag_keepalive },
    {"NUTAG_KEEPALIVE_STREAM", nutag_keepalive_stream },
    {"NUTAG_AUTHTIME", nutag_authtime },
    {"NUTAG_M_DISPLAY", nutag_m_display },
    {"NUTAG_M_USERNAME", nutag_m_username },
    {"NUTAG_M_PARAMS", nutag_m_params },
    {"NUTAG_M_FEATURES", nutag_m_features },
    {"NUTAG_EVENT", nutag_event },
    {"NUTAG_STATUS", nutag_status },
    {"NUTAG_PHRASE", nutag_phrase },
    {"NUTAG_HANDLE", nutag_handle },
    {"NUTAG_IDENTITY", nutag_identity },
    {"NUTAG_INSTANCE", nutag_instance },
    {"NUTAG_NOTIFY_REFER", nutag_notify_refer },
    {"NUTAG_REFER_EVENT", nutag_refer_event },
    {"NUTAG_REFER_PAUSE", nutag_refer_pause },
    {"NUTAG_USER_AGENT", nutag_user_agent },
    {"NUTAG_ALLOW", nutag_allow },
    {"NUTAG_APPL_METHOD", nutag_appl_method },
    {"NUTAG_SUPPORTED", nutag_supported },
    {"NUTAG_ALLOW_EVENTS", nutag_allow_events },
    {"NUTAG_CALLSTATE", nutag_callstate },
    {"NUTAG_SUBSTATE", nutag_substate },
    {"NUTAG_SUB_EXPIRES", nutag_sub_expires },
    {"NUTAG_NEWSUB", nutag_newsub },
    {"NUTAG_REFER_EXPIRES", nutag_refer_expires },
    {"NUTAG_REFER_WITH_ID", nutag_refer_with_id },
    {"NUTAG_MEDIA_FEATURES", nutag_media_features },
    {"NUTAG_CALLEE_CAPS", nutag_callee_caps },
    {"NUTAG_PATH_ENABLE", nutag_path_enable },
    {"NUTAG_SERVICE_ROUTE_ENABLE", nutag_service_route_enable },
    {"NUTAG_MEDIA_ENABLE", nutag_media_enable },
    {"NUTAG_OFFER_RECV", nutag_offer_recv },
    {"NUTAG_ANSWER_RECV", nutag_answer_recv },
    {"NUTAG_OFFER_SENT", nutag_offer_sent },
    {"NUTAG_ANSWER_SENT", nutag_answer_sent },
    {"NUTAG_DETECT_NETWORK_UPDATES", nutag_detect_network_updates },
    {"NUTAG_SHUTDOWN_EVENTS", nutag_shutdown_events },
    {"NUTAG_MEDIA_ADDRESS", soatag_address },
    {"NUTAG_HOLD", soatag_hold },
    {"NUTAG_ACTIVE_AUDIO", soatag_active_audio },
    {"NUTAG_ACTIVE_VIDEO", soatag_active_video },
    {"NUTAG_ACTIVE_IMAGE", soatag_active_image },
    {"NUTAG_ACTIVE_CHAT", soatag_active_chat },
    {"NUTAG_SRTP_ENABLE", soatag_srtp_enable },
    {"NUTAG_SRTP_CONFIDENTIALITY", soatag_srtp_confidentiality },
    {"NUTAG_SRTP_INTEGRITY_PROTECTION", soatag_srtp_integrity },
    {NULL, NULL}
};

static const luasofia_reg_const_t nua_constants[] = {
    { "nua_event_default", NUA_EVENT_DEFAULT_INDEX },
    { "nua_i_error", nua_i_error },
    { "nua_i_invite", nua_i_invite },
    { "nua_i_cancel", nua_i_cancel },
    { "nua_i_ack", nua_i_ack },
    { "nua_i_fork", nua_i_fork },
    { "nua_i_active", nua_i_active },
    { "nua_i_terminated", nua_i_terminated },
    { "nua_i_state", nua_i_state },
    { "nua_i_outbound", nua_i_outbound },
    { "nua_i_bye", nua_i_bye },
    { "nua_i_options", nua_i_options },
    { "nua_i_refer", nua_i_refer },
    { "nua_i_publish", nua_i_publish },
    { "nua_i_prack", nua_i_prack },
    { "nua_i_info", nua_i_info },
    { "nua_i_update", nua_i_update },
    { "nua_i_message", nua_i_message },
    { "nua_i_chat", nua_i_chat },
    { "nua_i_subscribe", nua_i_subscribe },
    { "nua_i_subscription", nua_i_subscription },
    { "nua_i_notify", nua_i_notify },
    { "nua_i_method", nua_i_method },
    { "nua_i_media_error", nua_i_media_error },
    { "nua_r_set_params", nua_r_set_params },
    { "nua_r_get_params", nua_r_get_params },
    { "nua_r_shutdown", nua_r_shutdown },
    { "nua_r_notifier", nua_r_notifier },
    { "nua_r_terminate", nua_r_terminate },
    { "nua_r_authorize", nua_r_authorize },
    { "nua_r_register", nua_r_register },
    { "nua_r_unregister", nua_r_unregister },
    { "nua_r_invite", nua_r_invite },
    { "nua_r_cancel", nua_r_cancel },
    { "nua_r_bye", nua_r_bye },
    { "nua_r_options", nua_r_options },
    { "nua_r_refer", nua_r_refer },
    { "nua_r_publish", nua_r_publish },
    { "nua_r_unpublish", nua_r_unpublish },
    { "nua_r_info", nua_r_info },
    { "nua_r_prack", nua_r_prack },
    { "nua_r_update", nua_r_update },
    { "nua_r_message", nua_r_message },
    { "nua_r_chat", nua_r_chat },
    { "nua_r_subscribe", nua_r_subscribe },
    { "nua_r_unsubscribe", nua_r_unsubscribe },
    { "nua_r_notify", nua_r_notify },
    { "nua_r_method", nua_r_method },
    { "nua_r_authenticate", nua_r_authenticate },
    { "nua_i_network_changed", nua_i_network_changed },
    { "nua_i_register", nua_i_register },
    { "nua_callstate_init", nua_callstate_init},
    { "nua_callstate_authenticating", nua_callstate_authenticating},
    { "nua_callstate_calling", nua_callstate_calling},
    { "nua_callstate_proceeding", nua_callstate_proceeding},
    { "nua_callstate_completing", nua_callstate_completing},
    { "nua_callstate_received ", nua_callstate_received},
    { "nua_callstate_early", nua_callstate_early},
    { "nua_callstate_completed", nua_callstate_completed},
    { "nua_callstate_ready", nua_callstate_ready},
    { "nua_callstate_terminating", nua_callstate_terminating},
    { "nua_callstate_terminated", nua_callstate_terminated},
    { "nua_no_refresher", nua_no_refresher},
    { "nua_local_refresher", nua_local_refresher},
    { "nua_remote_refresher", nua_remote_refresher},
    { "nua_any_refresher", nua_any_refresher},
    { "nua_substate_extended", nua_substate_extended},
    { "nua_substate_embryonic", nua_substate_embryonic},
    { "nua_substate_pending", nua_substate_pending},
    { "nua_substate_active", nua_substate_active},
    { "nua_substate_terminated", nua_substate_terminated},
    {NULL, 0 }
};

int luaopen_sofia_nua(lua_State *L)
{
    luaopen_sofia(L);

    luaL_newmetatable(L, NUA_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_meths);
    lua_pop(L, 1);

    luasofia_nua_handle_register_meta(L);
    luasofia_tags_register_tags(L, nua_tags);

    /* luasofia[nua] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "nua");
    luaL_register(L, NULL, nua_lib);

    luasofia_const_register_constants(L, nua_constants);

    return 1;
}

