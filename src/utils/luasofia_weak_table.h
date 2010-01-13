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

#ifndef __LUASOFIA_WEAK_TABLE_H__
#define __LUASOFIA_WEAK_TABLE_H__

/**
    @brief This module was created to build tables that hold weak references of its values.
           It is usually used to hold userdata that will have to be used on a callback, its a way
           to put the userdata back on the stack using the lighuserdata as key, and not messing up with the Lua GC.
*/

/**
    Create the Luasofia weak table, must be called ONLY once, it is already called by Luasofia main module, never use this
    @param L - The Lua State. 
*/
void luasofia_weak_table_create(lua_State *L);

/**
    Given an userdata at the top of the lua stack, inserts it on the weaktable, weaktable[key] = userdata. 
    @param L   - The Lua State. 
    @param key - The key that will map to the userdata.
*/
void luasofia_weak_table_set(lua_State *L, void* key);

/**
    If there is a entry weaktable[key] it will put the userdata mapped by key on the top of the stack.
    @param L   - The Lua State. 
    @param key - The key that maps to the userdata.
*/
void luasofia_weak_table_get(lua_State *L, void* key);

/**
    Removes the entry key from the weaktable.
    @param L   - The Lua State. 
    @param key - The key to remove from the table.
*/
void luasofia_weak_table_remove(lua_State *L, void* key);

#endif //__LUASOFIA_WEAK_TABLE

