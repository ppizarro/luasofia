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

#ifndef __LUASOFIA_SDP_SESSION_PRIVATE_H__
#define __LUASOFIA_SDP_SESSION_PRIVATE_H__

#define SDP_SESSION_TABLE_NAME "luasofia_sdp_session_t"

static const luasofia_proxy_info_t sdp_session_info[] = {
{"sdp_size",        luasofia_proxy_get_int,     offsetof(sdp_session_t, sdp_size),        0},
{"sdp_next",        luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_next),        0},
{"sdp_origin",      luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_origin),      0},
{"sdp_subject",     luasofia_proxy_get_string,  offsetof(sdp_session_t, sdp_subject),     0},
{"sdp_information", luasofia_proxy_get_string,  offsetof(sdp_session_t, sdp_information), 0},
{"sdp_uri",         luasofia_proxy_get_string,  offsetof(sdp_session_t, sdp_uri),         0},
{"sdp_emails",      luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_emails),      0},
{"sdp_phones",      luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_phones),      0},
{"sdp_connection",  luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_connection),  0},
{"sdp_bandwidths",  luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_bandwidths),  0},
{"sdp_time",        luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_time),        0},
{"sdp_key",         luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_key),         0},
{"sdp_attributes",  luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_attributes),  0},
{"sdp_charset",     luasofia_proxy_get_string,  offsetof(sdp_session_t, sdp_charset),     0},
{"sdp_media",       luasofia_proxy_get_pointer, offsetof(sdp_session_t, sdp_media),       0},
// FIXME  pointer to unsigned int, how to get? {"sdp_version",     luasofia_proxy_get_int,     offsetof(sdp_session_t, sdp_version),     0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_session(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_SESSION_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_SESSION_PRIVATE_H__ */


