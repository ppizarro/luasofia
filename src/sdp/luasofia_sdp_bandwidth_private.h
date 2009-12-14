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

#ifndef __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__
#define __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__

#define SDP_BANDWIDTH_TABLE_NAME "luasofia_sdp_bandwidth_t"

static const luasofia_proxy_info_t sdp_bandwidth_info[] = {
{"b_size",         luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_size),     0},
{"b_next",         luasofia_proxy_get_pointer, offsetof(sdp_bandwidth_t, b_next),     0},
{"b_modifier",     luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_modifier), 0},
{"b_modifier_name",luasofia_proxy_get_string,  offsetof(sdp_bandwidth_t, b_modifier_name), 0},
{"b_value",        luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_value),0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_bandwidth(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_BANDWIDTH_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__ */

