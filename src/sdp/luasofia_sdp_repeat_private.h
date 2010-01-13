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

#ifndef __LUASOFIA_SDP_REPEAT_PRIVATE_H__
#define __LUASOFIA_SDP_REPEAT_PRIVATE_H__

#define SDP_REPEAT_TABLE_NAME "luasofia_sdp_repeat_t"

static const luasofia_proxy_info_t sdp_repeat_info[] = {
{"r_size",              luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_size),              0},
{"r_number_of_offsets", luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_number_of_offsets), 0},
{"r_interval",          luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_interval),          0},
{"r_duration",          luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_duration),          0},
// FIXME {"r_offsets",         luasofia_proxy_get_int,  offsetof(sdp_repeat_t, r_offsets),          0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_repeat(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_REPEAT_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_REPEAT_PRIVATE_H__ */

