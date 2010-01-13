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

#ifndef __LUASOFIA_SDP_MEDIA_PRIVATE_H__
#define __LUASOFIA_SDP_MEDIA_PRIVATE_H__

#define SDP_MEDIA_TABLE_NAME "luasofia_sdp_media_t"

static const luasofia_proxy_info_t sdp_media_info[] = {
{"m_size",            luasofia_proxy_get_int,     offsetof(sdp_media_t, m_size),           0},
{"m_next",            luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_next),           0},
{"m_session",         luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_session),        0},
{"m_type",            luasofia_proxy_get_int,     offsetof(sdp_media_t, m_type),           0},
{"m_type_name",       luasofia_proxy_get_string,  offsetof(sdp_media_t, m_type_name),      0},
{"m_port",            luasofia_proxy_get_int,     offsetof(sdp_media_t, m_port),           0},
{"m_number_of_ports", luasofia_proxy_get_int,     offsetof(sdp_media_t, m_number_of_ports),0},
{"m_proto",           luasofia_proxy_get_int,     offsetof(sdp_media_t, m_proto),          0},
{"m_proto_name",      luasofia_proxy_get_string,  offsetof(sdp_media_t, m_proto_name),     0},
{"m_format",          luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_format),         0},
{"m_rtpmaps",         luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_rtpmaps),        0},
{"m_information",     luasofia_proxy_get_string,  offsetof(sdp_media_t, m_information),    0},
{"m_connections",     luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_connections),    0},
{"m_bandwidths",      luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_bandwidths),     0},
{"m_key",             luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_key),            0},
{"m_attributes",      luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_attributes),     0},
{"m_user",            luasofia_proxy_get_pointer, offsetof(sdp_media_t, m_user),           0},
//FIXME how to access unsigned 	m_rejected: 1 ?
//FIXME how to acess  unsigned 	m_mode: 1 ?
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_media(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_MEDIA_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_MEDIA_PRIVATE_H__ */


