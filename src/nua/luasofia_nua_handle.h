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

#ifndef __LUASOFIA_NUA_HANDLE_H__
#define __LUASOFIA_NUA_HANDLE_H__

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <sofia-sip/nua.h>

#define NUA_HANDLE_MTABLE "luasofia_nua_handle_t"

int luasofia_nua_handle_register_meta(lua_State* L);

int luasofia_nua_handle_create(lua_State *L, nua_t *nua);

int luasofia_nua_handle_create_userdata(lua_State *L, nua_handle_t *nh);

#endif /* __LUASOFIA_NUA_HANDLE_H__ */
