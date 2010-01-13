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

#ifndef __LUASOFIA_SDP_RTPMAP_PRIVATE_H__
#define __LUASOFIA_SDP_RTPMAP_PRIVATE_H__

#define SDP_RTPMAP_TABLE_NAME "luasofia_sdp_rtpmap_t"

static const luasofia_proxy_info_t sdp_rtpmap_info[] = {
{"rm_size",      luasofia_proxy_get_int,     offsetof(sdp_rtpmap_t, rm_size),     0},
{"rm_next",      luasofia_proxy_get_pointer, offsetof(sdp_rtpmap_t, rm_next),     0},
{"rm_encoding",  luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_encoding), 0},
{"rm_rate",      luasofia_proxy_get_int,     offsetof(sdp_rtpmap_t, rm_rate),     0},
{"rm_params",    luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_params),   0},
{"rm_fmtp",      luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_fmtp),     0},
//FIXME how to acess unsigned rm_predef: 1, rm_pt: 7, rm_any: 1 ?
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_rtpmap(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_RTPMAP_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_RTPMAP_PRIVATE_H__ */
