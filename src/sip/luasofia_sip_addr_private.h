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

#ifndef __LUASOFIA_SIP_ADDR_PRIVATE_H__
#define __LUASOFIA_SIP_ADDR_PRIVATE_H__

#define SIP_ADDR_TABLE_NAME    "luasofia_sip_addr_t" 

static const luasofia_proxy_info_t sip_addr_info[] = {
{"a_display", luasofia_proxy_get_string, offsetof(sip_addr_t, a_display), 0},
{"a_url",     luasofia_proxy_get_address, offsetof(sip_addr_t, a_url),   0},
{"a_params",  luasofia_proxy_get_pointer, offsetof(sip_addr_t, a_params), 0},
{"a_comment", luasofia_proxy_get_string, offsetof(sip_addr_t, a_comment), 0},
{"a_tag",     luasofia_proxy_get_string, offsetof(sip_addr_t, a_tag), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_addr(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_ADDR_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_ADDR_PRIVATE_H__
