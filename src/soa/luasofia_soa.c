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
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"

#include <sofia-sip/soa.h>
#include <sofia-sip/soa_tag.h>

typedef struct lua_soa_session_s lua_soa_session_t;

#define SOA_SESSION_MTABLE "lua_soa_session_t"

struct lua_soa_session_s {
    soa_session_t *soa;
    lua_State *L;
};

static const luaL_Reg soa_session_meths[] = {
    {NULL, NULL}
};

static const luaL_Reg soa_lib[] = {
    {NULL, NULL}
};

static const luasofia_tag_reg_t soa_tags[] = {
    { "SOATAG_ANY", soatag_any },
    { "SOATAG_LOCAL_SDP", soatag_local_sdp },
    { "SOATAG_LOCAL_SDP_STR", soatag_local_sdp_str },
    { "SOATAG_USER_SDP", soatag_user_sdp },
    { "SOATAG_USER_SDP_STR", soatag_user_sdp_str },
    { "SOATAG_CAPS_SDP", soatag_caps_sdp },
    { "SOATAG_CAPS_SDP_STR", soatag_caps_sdp_str },
    { "SOATAG_REMOTE_SDP", soatag_remote_sdp },
    { "SOATAG_REMOTE_SDP_STR", soatag_remote_sdp_str },
    { "SOATAG_LOCAL_SDP", soatag_local_sdp },
    { "SOATAG_LOCAL_SDP_STR", soatag_local_sdp_str },
    { "SOATAG_ADDRESS", soatag_address },
    { "SOATAG_RTP_SELECT", soatag_rtp_select },
    { "SOATAG_AUDIO_AUX", soatag_audio_aux },
    { "SOATAG_RTP_SORT", soatag_rtp_sort },
    { "SOATAG_RTP_MISMATCH", soatag_rtp_mismatch },
    { "SOATAG_ACTIVE_AUDIO", soatag_active_audio },
    { "SOATAG_ACTIVE_VIDEO", soatag_active_video },
    { "SOATAG_ACTIVE_IMAGE", soatag_active_image },
    { "SOATAG_ACTIVE_CHAT", soatag_active_chat },
    { "SOATAG_SRTP_ENABLE", soatag_srtp_enable },
    { "SOATAG_SRTP_CONFIDENTIALITY", soatag_srtp_confidentiality },
    { "SOATAG_SRTP_INTEGRITY", soatag_srtp_integrity },
    { "SOATAG_HOLD", soatag_hold },
    { "SOATAG_ORDERED_USER", soatag_ordered_user },
    { "SOATAG_REUSE_REJECTED", soatag_reuse_rejected },
    { NULL, NULL}
};

static const luasofia_reg_const_t soa_constants[] = {
    {NULL, 0 }
};

int luaopen_luasofia_soa(lua_State *L)
{
    luaL_newmetatable(L, SOA_SESSION_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, soa_session_meths);
    lua_pop(L, 1);

    luasofia_tags_register_tags(L, soa_tags);

    luaopen_luasofia(L);

    /* luasofia[soa] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "soa");
    luaL_register(L, NULL, soa_lib);

    luasofia_const_register_constants(L, soa_constants);

    return 1;
}

