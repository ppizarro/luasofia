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

#ifndef __LUASOFIA_SIP_EVENT_PRIVATE_H__
#define __LUASOFIA_SIP_EVENT_PRIVATE_H__

#define SIP_EVENT_TABLE_NAME  "luasofia_sip_event_t"

static const luasofia_proxy_info_t sip_event_info[] = {
{"o_type",  luasofia_proxy_get_string,  offsetof(sip_event_t, o_type),   0},
{"o_params",luasofia_proxy_get_pointer, offsetof(sip_event_t, o_params), 0},
{"o_id",    luasofia_proxy_get_string,  offsetof(sip_event_t, o_id),     0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_event(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_EVENT_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_EVENT_PRIVATE_H__
