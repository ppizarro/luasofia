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

#ifndef __LUASOFIA_SIP_CONTENT_DISPOSITION_PRIVATE_H__
#define __LUASOFIA_SIP_CONTENT_DISPOSITION_PRIVATE_H__

#define SIP_CONTENT_DISPOSITION_TABLE_NAME "luasofia_sip_content_disposition_t" 

static const luasofia_proxy_info_t sip_content_disposition_info[] = {
{"cd_params",   luasofia_proxy_get_string, offsetof(sip_content_disposition_t, cd_params),  0},
{"cd_type",     luasofia_proxy_get_string, offsetof(sip_content_disposition_t, cd_type),    0},
{"cd_handling", luasofia_proxy_get_string, offsetof(sip_content_disposition_t, cd_handling),0},
{"cd_flags",    luasofia_proxy_get_int,    offsetof(sip_content_disposition_t, cd_handling)+1,0},
{NULL, NULL, 0 }
};


static int luasofia_sip_get_proxy_content_disposition(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_CONTENT_DISPOSITION_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_CONTENT_DISPOSITION_PRIVATE_H__
