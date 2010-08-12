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

#ifndef __LUASOFIA_UTILS_H__
#define __LUASOFIA_UTILS_H__

/**
    Prints all the content of the stack, usefull for debugging.
    @param L - The lua_State that holds the stack.
*/ 
void stack_dump(lua_State *L);

/**
    Prints all the content of a table, usefull for debugging.
    @param L - The lua_State that holds the stack.
    @param i - The index where the table is at stack.
*/
void print_table(lua_State *L, int i);
 
#endif //__LUASOFIA_UTILS
