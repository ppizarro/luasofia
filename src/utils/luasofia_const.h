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

#ifndef __LUASOFIA_UTILS_H__
#define __LUASOFIA_UTILS_H__

typedef struct luasofia_reg_const_s {
  const char *name;
  int value;
} luasofia_reg_const_t;

/**
    Given a consts list, register all then on the table that is on the top of the stack of the lua_State. 
    Table_at_stack_top[const.name] = const.value. There MUST be a table on the top of the stack.
    @param L      - lua state.
    @param consts - NULL terminated array of consts.
*/
void luasofia_const_register_constants(lua_State *L, const luasofia_reg_const_t *consts);

#endif //__LUASOFIA_UTILS

