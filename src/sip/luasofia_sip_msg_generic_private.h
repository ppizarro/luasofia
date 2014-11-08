/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Bjoern Kalkbrenner <bjoern.kalkbrenner@belnet.de>
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

#ifndef __LUASOFIA_SIP_MSG_GENERIC_PRIVATE_H__
#define __LUASOFIA_SIP_MSG_GENERIC_PRIVATE_H__

#define SIP_MSG_GENERIC_TABLE_NAME "luasofia_sip_msg_generic_t" 

static const luasofia_proxy_info_t sip_msg_generic_info[] = {
{"g_next",   luasofia_proxy_get_pointer, offsetof(msg_generic_t, g_next),  0},
{"g_string", luasofia_proxy_get_string,  offsetof(msg_generic_t, g_string),0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_msg_generic(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_MSG_GENERIC_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_MSG_GENERIC_PRIVATE_H__
