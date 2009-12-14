/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * Copyright (C) 2009 Digitro Corporation <www.digitro.com.br>
 *
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
#include "utils/luasofia_weak_table.h"
#include "su/luasofia_su_root.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"

#include <sofia-sip/nua.h>
#include <sofia-sip/nua_tag.h>
#include <sofia-sip/soa_tag.h>
#include <sofia-sip/su_tag_io.h>

typedef struct lua_nua_handle_s lua_nua_handle_t;

#define NUA_HANDLE_MTABLE "lua_nua_handle_t"

typedef struct lua_nua_s lua_nua_t;

#define NUA_MTABLE "lua_nua_t"

struct lua_nua_handle_s {
    nua_handle_t *nh;
    lua_State *L;
};

struct lua_nua_s {
    nua_t *nua;
    lua_State *L;
};

static int lua_nua_set_params(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_t) */
    su_home_t *home = su_home_create();
    lua_nua_t *lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);
    tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

    //tl_print(stdout, "lua_nua_set_params:\n", tags);
    nua_set_params(lnua->nua, TAG_NEXT(tags));
    su_home_unref(home);
    return 0;
}

static int lua_nua_handle_invite(lua_State *L)
{
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();
    /* get and check first argument (should be a lua_nua_handle_t) */
    lua_nua_handle_t *lnh = (lua_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);

    tags = luasofia_tags_table_to_taglist(L, 2, home);
    //tl_print(stdout, "lua_nua_invite:\n", tags);
    nua_invite(lnh->nh, TAG_NEXT(tags));
    su_home_unref(home);
    return 0;
}

static int lua_nua_handle_ref(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_handle_t) */
    lua_nua_handle_t *lnh = (lua_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    nua_handle_ref(lnh->nh);
    return 0;
}

static int lua_nua_handle_unref(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_handle_t) */
    lua_nua_handle_t *lnh = (lua_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    nua_handle_unref(lnh->nh);
    return 0;
}

static int lua_nua_handle_destroy(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_handle_t) */
    lua_nua_handle_t *lnh = (lua_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);

    if (lnh->nh) {
        /* remove lnh of the luasofia weak table */
        luasofia_weak_table_remove(L, lnh->nh);
        nua_handle_destroy(lnh->nh);
        lnh->nh = NULL;
    }
    return 0;
}

static int lua_nua_handle_create(lua_State *L)
{
    lua_nua_t *lnua = NULL;
    lua_nua_handle_t *lnh = NULL;
    nua_handle_t *nh = NULL;
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();

    /* get and check first argument (should be a nua_t) */
    lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    tags = luasofia_tags_table_to_taglist(L, 2, home);

    //tl_print(stdout, "lua_nua_handle:\n", tags);

    /* create a nua object */
    lnh = (lua_nua_handle_t*) lua_newuserdata(L, sizeof(lua_nua_handle_t));

    /* create the nua_handle_t */
    nh = nua_handle(lnua->nua, lnh, TAG_NEXT(tags));
    if (!nh)
        luaL_error(L, "nua_handle failed!");

    /* set Lua state */
    lnh->L = L;
    lnh->nh = nh;

    /* set its metatable */
    luaL_getmetatable(L, NUA_HANDLE_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua handle at luasofia weak table */
    luasofia_weak_table_set(L, nh);

    su_home_unref(home);
    return 1;
}

static int lua_nua_destroy(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_t) */
    lua_nua_t *lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    if (lnua->nua) {
        /* remove lnua of the luasofia weak table */
        luasofia_weak_table_remove(L, lnua->nua);

        nua_destroy(lnua->nua);
        lnua->nua = NULL;
    }
    return 0;
}

static int lua_nua_shutdown(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_t) */
    lua_nua_t *lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);
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
    lua_nua_t *lnua = (lua_nua_t*)magic;
    lua_State *L = lnua->L;

    //printf("nua_event_callback: event[%d] status[%d] phrase[%s] nua[%p] magic[%p] sip[%p] tags[%p]\n",
    //       event, status, phrase, nua, magic, sip, tags);

    // put userdatum at stack and check if it is ok.
    luasofia_weak_table_get(L, lnua->nua);
    luaL_checkudata(L, -1, NUA_MTABLE);

    /* put callback table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        return;
    }

    /* get event callback */
    lua_rawgeti(L, -1, event);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        /* get default callback */
        lua_getfield(L, -1, "event_default");
        if (lua_isnil(L, -1)) {
            lua_pop(L, 3);
            return;
        }
    }

    lua_pushinteger(L, event);
    lua_pushinteger(L, status);
    lua_pushstring(L, phrase);
    lua_pushvalue(L, -6);

    sip ? lua_pushlightuserdata(L, (void*)sip) : lua_pushnil(L);

    tags ? lua_pushlightuserdata(L, (void*)tags) : lua_pushnil(L);

    lua_call(L, 6, 0);
    lua_pop(L, 2);
}

static int lua_nua_create(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;
    lua_nua_t *lnua = NULL;
    nua_t *nua = NULL;
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();

    /* get and check first argument (should be a root_t) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, 1, SU_ROOT_MTABLE);

    /* check the callback table */
    luaL_checktype(L, 2, LUA_TTABLE);

    tags = luasofia_tags_table_to_taglist(L, 3, home);

    //tl_print(stdout, "lua_nua_create:\n", tags);

    /* create a nua object */
    lnua = (lua_nua_t*) lua_newuserdata(L, sizeof(lua_nua_t));

    /* create the nua_t */
    nua = nua_create(lroot->root, nua_event_callback, lnua, TAG_NEXT(tags));
    if (!nua)
        luaL_error(L, "nua_create failed!");

    /* set Lua state */
    lnua->L = L;
    lnua->nua = nua;

    /* set its metatable */
    luaL_getmetatable(L, NUA_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua at luasofia weak table */
    luasofia_weak_table_set(L, nua);

    /* set callback table as environment for udata */
    lua_pushvalue(L, 2);
    lua_setfenv(L, -2);

    su_home_unref(home);
    return 1;
}

static int lua_nua_event_name(lua_State *L)
{
    nua_event_t event = lua_tointeger(L, -1);
    char const *name = nua_event_name(event);
    lua_pushstring(L, name);
    return 1;
}

static const luaL_Reg nua_handle_meths[] = {
    {"ref",    lua_nua_handle_ref },
    {"unref",  lua_nua_handle_unref },
    {"invite", lua_nua_handle_invite },
    {"__gc",   lua_nua_handle_destroy },
    {NULL, NULL}
};

static const luaL_Reg nua_meths[] = {
    {"set_params",    lua_nua_set_params },
    {"handle_create", lua_nua_handle_create },
    {"shutdown",      lua_nua_shutdown },
    {"__gc",          lua_nua_destroy },
    {NULL, NULL}
};

static const luaL_Reg nua_lib[] = {
    {"create", lua_nua_create },
    {"event_name", lua_nua_event_name },
    {NULL, NULL}
};

static const luasofia_tag_reg_t nua_tags[] = {
    {"NUTAG_ANY", nutag_any },
    {"NUTAG_URL", nutag_url },
    {"NUTAG_URL_REF", nutag_url_ref },
    {"NUTAG_ADDRESS", nutag_address },
    {"NUTAG_ADDRESS_REF", nutag_address_ref },
    {"NUTAG_WITH", nutag_with },
    {"NUTAG_DIALOG", nutag_dialog },
    {"NUTAG_METHOD", nutag_method },
    {"NUTAG_METHOD_REF", nutag_method_ref },
    {"NUTAG_MAX_SUBSCRIPTIONS", nutag_max_subscriptions },
    {"NUTAG_MAX_SUBSCRIPTIONS_REF", nutag_max_subscriptions_ref },
    {"NUTAG_UICC", nutag_uicc },
    {"NUTAG_UICC_REF", nutag_uicc_ref },
    {"NUTAG_USE_DIALOG", nutag_use_dialog },
    {"NUTAG_USE_DIALOG_REF", nutag_use_dialog_ref },
    {"NUTAG_RETRY_COUNT", nutag_retry_count },
    {"NUTAG_RETRY_COUNT_REF", nutag_retry_count_ref },
    {"NUTAG_SOA_NAME", nutag_soa_name },
    {"NUTAG_SOA_NAME_REF", nutag_soa_name_ref },
    {"NUTAG_EARLY_MEDIA", nutag_early_media },
    {"NUTAG_EARLY_MEDIA_REF", nutag_early_media_ref },
    {"NUTAG_ONLY183_100REL", nutag_only183_100rel },
    {"NUTAG_ONLY183_100REL_REF", nutag_only183_100rel_ref },
    {"NUTAG_EARLY_ANSWER", nutag_early_answer },
    {"NUTAG_EARLY_ANSWER_REF", nutag_early_answer_ref },
    {"NUTAG_INCLUDE_EXTRA_SDP", nutag_include_extra_sdp },
    {"NUTAG_INCLUDE_EXTRA_SDP_REF", nutag_include_extra_sdp_ref },
    {"NUTAG_INVITE_TIMER", nutag_invite_timer },
    {"NUTAG_INVITE_TIMER_REF", nutag_invite_timer_ref },
    {"NUTAG_SESSION_TIMER", nutag_session_timer },
    {"NUTAG_SESSION_TIMER_REF", nutag_session_timer_ref },
    {"NUTAG_MIN_SE", nutag_min_se },
    {"NUTAG_MIN_SE_REF", nutag_min_se_ref },
    {"NUTAG_SESSION_REFRESHER", nutag_session_refresher },
    {"NUTAG_SESSION_REFRESHER_REF", nutag_session_refresher_ref },
    {"NUTAG_UPDATE_REFRESH", nutag_update_refresh },
    {"NUTAG_UPDATE_REFRESH_REF", nutag_update_refresh_ref },
    {"NUTAG_REFRESH_WITHOUT_SDP", nutag_refresh_without_sdp },
    {"NUTAG_REFRESH_WITHOUT_SDP_REF", nutag_refresh_without_sdp_ref },
    {"NUTAG_AUTOALERT", nutag_autoalert },
    {"NUTAG_AUTOALERT_REF", nutag_autoalert_ref },
    {"NUTAG_AUTOACK", nutag_autoack },
    {"NUTAG_AUTOACK_REF", nutag_autoack_ref },
    {"NUTAG_AUTOANSWER", nutag_autoanswer },
    {"NUTAG_AUTOANSWER_REF", nutag_autoanswer_ref },
    {"NUTAG_ENABLEINVITE", nutag_enableinvite },
    {"NUTAG_ENABLEINVITE_REF", nutag_enableinvite_ref },
    {"NUTAG_ENABLEMESSAGE", nutag_enablemessage },
    {"NUTAG_ENABLEMESSAGE_REF", nutag_enablemessage_ref },
    {"NUTAG_ENABLEMESSENGER", nutag_enablemessenger },
    {"NUTAG_ENABLEMESSENGER_REF", nutag_enablemessenger_ref },
    {"NUTAG_SMIME_ENABLE", nutag_smime_enable },
    {"NUTAG_SMIME_ENABLE_REF", nutag_smime_enable_ref },
    {"NUTAG_SMIME_OPT", nutag_smime_opt },
    {"NUTAG_SMIME_OPT_REF", nutag_smime_opt_ref },
    {"NUTAG_SMIME_PROTECTION_MODE", nutag_smime_protection_mode },
    {"NUTAG_SMIME_PROTECTION_MODE_REF", nutag_smime_protection_mode_ref },
    {"NUTAG_SMIME_MESSAGE_DIGEST", nutag_smime_message_digest },
    {"NUTAG_SMIME_MESSAGE_DIGEST_REF", nutag_smime_message_digest_ref },
    {"NUTAG_SMIME_SIGNATURE", nutag_smime_signature },
    {"NUTAG_SMIME_SIGNATURE_REF", nutag_smime_signature_ref },
    {"NUTAG_SMIME_KEY_ENCRYPTION", nutag_smime_key_encryption },
    {"NUTAG_SMIME_KEY_ENCRYPTION_REF", nutag_smime_key_encryption_ref },
    {"NUTAG_SMIME_MESSAGE_ENCRYPTION", nutag_smime_message_encryption },
    {"NUTAG_SMIME_MESSAGE_ENCRYPTION_REF", nutag_smime_message_encryption_ref },
    {"NUTAG_CERTIFICATE_DIR", nutag_certificate_dir },
    {"NUTAG_CERTIFICATE_DIR_REF", nutag_certificate_dir_ref },
    {"NUTAG_CERTIFICATE_PHRASE", nutag_certificate_phrase },
    {"NUTAG_CERTIFICATE_PHRASE_REF", nutag_certificate_phrase_ref },
    {"NUTAG_SIPS_URL", nutag_sips_url },
    {"NUTAG_SIPS_URL_REF", nutag_sips_url_ref },
    {"NUTAG_PROXY",  ntatag_default_proxy },
    {"NUTAG_PROXY_REF", ntatag_default_proxy_ref },
    {"NUTAG_INITIAL_ROUTE", nutag_initial_route },
    {"NUTAG_INITIAL_ROUTE_REF", nutag_initial_route_ref },
    {"NUTAG_INITIAL_ROUTE_STR", nutag_initial_route_str },
    {"NUTAG_INITIAL_ROUTE_STR_REF", nutag_initial_route_str_ref },
    {"NUTAG_REGISTRAR", nutag_registrar },
    {"NUTAG_REGISTRAR_REF", nutag_registrar_ref },
    {"NUTAG_OUTBOUND", nutag_outbound },
    {"NUTAG_OUTBOUND_REF", nutag_outbound_ref },
    {"NUTAG_AUTH", nutag_auth },
    {"NUTAG_AUTH_REF", nutag_auth_ref },
    {"NUTAG_AUTH_CACHE", nutag_auth_cache },
    {"NUTAG_AUTH_CACHE_REF", nutag_auth_cache_ref },
    {"NUTAG_KEEPALIVE", nutag_keepalive },
    {"NUTAG_KEEPALIVE_REF", nutag_keepalive_ref },
    {"NUTAG_KEEPALIVE_STREAM", nutag_keepalive_stream },
    {"NUTAG_KEEPALIVE_STREAM_REF", nutag_keepalive_stream_ref },
    {"NUTAG_AUTHTIME", nutag_authtime },
    {"NUTAG_AUTHTIME_REF", nutag_authtime_ref },
    {"NUTAG_M_DISPLAY", nutag_m_display },
    {"NUTAG_M_DISPLAY_REF", nutag_m_display_ref },
    {"NUTAG_M_USERNAME", nutag_m_username },
    {"NUTAG_M_USERNAME_REF", nutag_m_username_ref },
    {"NUTAG_M_PARAMS", nutag_m_params },
    {"NUTAG_M_PARAMS_REF", nutag_m_params_ref },
    {"NUTAG_M_FEATURES", nutag_m_features },
    {"NUTAG_M_FEATURES_REF", nutag_m_features_ref },
    {"NUTAG_EVENT", nutag_event },
    {"NUTAG_EVENT_REF", nutag_event_ref },
    {"NUTAG_STATUS", nutag_status },
    {"NUTAG_STATUS_REF", nutag_status_ref },
    {"NUTAG_PHRASE", nutag_phrase },
    {"NUTAG_PHRASE_REF", nutag_phrase_ref },
    {"NUTAG_HANDLE", nutag_handle },
    {"NUTAG_HANDLE_REF", nutag_handle_ref },
    {"NUTAG_IDENTITY", nutag_identity },
    {"NUTAG_IDENTITY_REF", nutag_identity_ref },
    {"NUTAG_INSTANCE", nutag_instance },
    {"NUTAG_INSTANCE_REF", nutag_instance_ref },
    {"NUTAG_NOTIFY_REFER", nutag_notify_refer },
    {"NUTAG_NOTIFY_REFER_REF", nutag_notify_refer_ref },
    {"NUTAG_REFER_EVENT", nutag_refer_event },
    {"NUTAG_REFER_EVENT_REF", nutag_refer_event_ref },
    {"NUTAG_REFER_PAUSE", nutag_refer_pause },
    {"NUTAG_REFER_PAUSE_REF", nutag_refer_pause_ref },
    {"NUTAG_USER_AGENT", nutag_user_agent },
    {"NUTAG_USER_AGENT_REF", nutag_user_agent_ref },
    {"NUTAG_ALLOW", nutag_allow },
    {"NUTAG_ALLOW_REF", nutag_allow_ref },
    {"NUTAG_APPL_METHOD", nutag_appl_method },
    {"NUTAG_APPL_METHOD_REF", nutag_appl_method_ref },
    {"NUTAG_SUPPORTED", nutag_supported },
    {"NUTAG_SUPPORTED_REF", nutag_supported_ref },
    {"NUTAG_ALLOW_EVENTS", nutag_allow_events },
    {"NUTAG_ALLOW_EVENTS_REF", nutag_allow_events_ref },
    {"NUTAG_CALLSTATE", nutag_callstate },
    {"NUTAG_CALLSTATE_REF", nutag_callstate_ref },
    {"callstate_REF", nutag_callstate_ref },
    {"NUTAG_SUBSTATE", nutag_substate },
    {"NUTAG_SUBSTATE_REF", nutag_substate_ref },
    {"NUTAG_SUB_EXPIRES", nutag_sub_expires },
    {"NUTAG_SUB_EXPIRES_REF", nutag_sub_expires_ref },
    {"NUTAG_NEWSUB", nutag_newsub },
    {"NUTAG_NEWSUB_REF", nutag_newsub_ref },
    {"NUTAG_REFER_EXPIRES", nutag_refer_expires },
    {"NUTAG_REFER_EXPIRES_REF", nutag_refer_expires_ref },
    {"NUTAG_REFER_WITH_ID", nutag_refer_with_id },
    {"NUTAG_REFER_WITH_ID_REF", nutag_refer_with_id_ref },
    {"NUTAG_MEDIA_FEATURES", nutag_media_features },
    {"NUTAG_MEDIA_FEATURES_REF", nutag_media_features_ref },
    {"NUTAG_CALLEE_CAPS", nutag_callee_caps },
    {"NUTAG_CALLEE_CAPS_REF", nutag_callee_caps_ref },
    {"NUTAG_PATH_ENABLE", nutag_path_enable },
    {"NUTAG_PATH_ENABLE_REF", nutag_path_enable_ref },
    {"NUTAG_SERVICE_ROUTE_ENABLE", nutag_service_route_enable },
    {"NUTAG_SERVICE_ROUTE_ENABLE_REF", nutag_service_route_enable_ref },
    {"NUTAG_MEDIA_ENABLE", nutag_media_enable },
    {"NUTAG_MEDIA_ENABLE_REF", nutag_media_enable_ref },
    {"NUTAG_OFFER_RECV", nutag_offer_recv },
    {"NUTAG_OFFER_RECV_REF", nutag_offer_recv_ref },
    {"NUTAG_ANSWER_RECV", nutag_answer_recv },
    {"NUTAG_ANSWER_RECV_REF", nutag_answer_recv_ref },
    {"NUTAG_OFFER_SENT", nutag_offer_sent },
    {"NUTAG_OFFER_SENT_REF", nutag_offer_sent_ref },
    {"NUTAG_ANSWER_SENT", nutag_answer_sent },
    {"NUTAG_ANSWER_SENT_REF", nutag_answer_sent_ref },
    {"NUTAG_DETECT_NETWORK_UPDATES", nutag_detect_network_updates },
    {"NUTAG_DETECT_NETWORK_UPDATES_REF", nutag_detect_network_updates_ref },
    {"NUTAG_SHUTDOWN_EVENTS", nutag_shutdown_events },
    {"NUTAG_SHUTDOWN_EVENTS_REF", nutag_shutdown_events_ref },
    {"NUTAG_MEDIA_ADDRESS", soatag_address },
    {"NUTAG_MEDIA_ADDRESS_REF", soatag_address_ref },
    {"NUTAG_HOLD", soatag_hold },
    {"NUTAG_ACTIVE_AUDIO", soatag_active_audio },
    {"NUTAG_ACTIVE_AUDIO_REF", soatag_active_audio_ref },
    {"NUTAG_ACTIVE_VIDEO", soatag_active_video },
    {"NUTAG_ACTIVE_VIDEO_REF", soatag_active_video_ref },
    {"NUTAG_ACTIVE_IMAGE", soatag_active_image },
    {"NUTAG_ACTIVE_IMAGE_REF", soatag_active_image_ref },
    {"NUTAG_ACTIVE_CHAT", soatag_active_chat },
    {"NUTAG_ACTIVE_CHAT_REF", soatag_active_chat_ref },
    {"NUTAG_SRTP_ENABLE", soatag_srtp_enable },
    {"NUTAG_SRTP_ENABLE_REF", soatag_srtp_enable_ref },
    {"NUTAG_SRTP_CONFIDENTIALITY", soatag_srtp_confidentiality },
    {"NUTAG_SRTP_CONFIDENTIALITY_REF", soatag_srtp_confidentiality_ref },
    {"NUTAG_SRTP_INTEGRITY_PROTECTION", soatag_srtp_integrity },
    {"NUTAG_SRTP_INTEGRITY_PROTECTION_REF", soatag_srtp_integrity_ref },
    {NULL, NULL}
};

static const luasofia_reg_const_t nua_constants[] = {
    { "nua_i_none", nua_i_none },
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
    {NULL, 0 }
};

int luaopen_luasofia_nua(lua_State *L)
{
    luaL_newmetatable(L, NUA_HANDLE_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_handle_meths);
    lua_pop(L, 1);

    luaL_newmetatable(L, NUA_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_meths);
    lua_pop(L, 1);

    luasofia_tags_register_tags(L, nua_tags);

    luaopen_luasofia(L);

    /* luasofia[nua] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "nua");
    luaL_register(L, NULL, nua_lib);

    luasofia_const_register_constants(L, nua_constants);

    return 1;
}

