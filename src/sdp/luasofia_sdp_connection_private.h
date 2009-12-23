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

#ifndef __LUASOFIA_SDP_CONNECTION_PRIVATE_H__
#define __LUASOFIA_SDP_CONNECTION_PRIVATE_H__

#define SDP_CONNECTION_TABLE_NAME "luasofia_sdp_connection_t"

static const luasofia_proxy_info_t sdp_connection_info[] = {
{"c_size",     luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_size),     0},
{"c_next",     luasofia_proxy_get_pointer, offsetof(sdp_connection_t, c_next),     0},
{"c_nettype",  luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_nettype),  0},
{"c_addrtype", luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_addrtype), 0},
{"c_address",  luasofia_proxy_get_string,  offsetof(sdp_connection_t, c_address),  0},
// FIXME how to get unsigned  c_ttl : 8; {"c_ttl",      luasofia_proxy_get_char,    offsetof(sdp_connection_t, c_ttl),      0},
// FIXME how to get unsigned  c_mcast : 1; {"c_mcast",    luasofia_proxy_get_boolean, offsetof(sdp_connection_t, c_mcast),    0},
{"c_groups",   luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_groups),   0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_connection(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_CONNECTION_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_CONNECTION_PRIVATE_H__ */

