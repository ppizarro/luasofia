/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 * @author Guilherme Silveira <xguiga@gmail.com>
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

#ifndef __LUASOFIA_SIP_SUBSCRIPTION_STATE_PRIVATE_H__
#define __LUASOFIA_SIP_SUBSCRIPTION_STATE_PRIVATE_H__

#define SIP_SUBSCRIPTION_STATE_TABLE_NAME "luasofia_sip_subscription_state_t" 

static const luasofia_proxy_info_t sip_subscription_state_info[] = {
{"ss_next",        luasofia_proxy_get_pointer, offsetof(sip_subscription_state_t, ss_next), 0},
{"ss_substate",    luasofia_proxy_get_string, offsetof(sip_subscription_state_t, ss_substate), 0},
{"ss_params",      luasofia_proxy_get_pointer, offsetof(sip_subscription_state_t, ss_params), 0},
{"ss_reason",      luasofia_proxy_get_string, offsetof(sip_subscription_state_t, ss_reason), 0},
{"ss_expires",     luasofia_proxy_get_string, offsetof(sip_subscription_state_t, ss_expires), 0},
{"ss_retry_after", luasofia_proxy_get_string, offsetof(sip_subscription_state_t, ss_retry_after), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_subscription_state(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_SUBSCRIPTION_STATE_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_SUBSCRIPTION_STATE_PRIVATE_H__
