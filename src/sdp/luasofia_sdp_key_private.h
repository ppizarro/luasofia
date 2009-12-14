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

#ifndef __LUASOFIA_SDP_KEY_PRIVATE_H__
#define __LUASOFIA_SDP_KEY_PRIVATE_H__

#define SDP_KEY_TABLE_NAME "luasofia_sdp_key_t"

static const luasofia_proxy_info_t sdp_key_info[] = {
{"k_size",       luasofia_proxy_get_int,     offsetof(sdp_key_t, k_size),        0},
{"k_method",     luasofia_proxy_get_int,     offsetof(sdp_key_t, k_method),      0},
{"k_method_name",luasofia_proxy_get_string,  offsetof(sdp_key_t, k_method_name), 0},
{"k_material",   luasofia_proxy_get_string,  offsetof(sdp_key_t, k_material),    0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_key(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_KEY_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_KEY_PRIVATE_H__ */
