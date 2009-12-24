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

#ifndef __LUASOFIA_SIP_ALLOW_PRIVATE_H__
#define __LUASOFIA_SIP_ALLOW_PRIVATE_H__

#define SIP_ALLOW_TABLE_NAME "luasofia_sip_allow_t" 

static const luasofia_proxy_info_t sip_allow_info[] = {
{"k_next",   luasofia_proxy_get_pointer, offsetof(sip_allow_t, k_next), 0},
{"k_items",  luasofia_proxy_get_pointer, offsetof(sip_allow_t, k_items), 0},
{"k_bitmap", luasofia_proxy_get_int, offsetof(sip_allow_t, k_bitmap), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_allow(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_ALLOW_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_ALLOW_PRIVATE_H__
