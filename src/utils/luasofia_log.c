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

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
 
#include "utils/luasofia_utils.h"

static void print_value(lua_State *L, int i)
{
    int t = lua_type(L, i);

    if (lua_isnone(L, i) || lua_isnil(L, i)) {
        printf("Invalid value at index[%d]", i);
        return;
    }

    switch (t) {
        case LUA_TSTRING:
            printf("'%s'", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        default:
            printf("%s", lua_typename(L, t));
    }
}

void stack_dump(lua_State *L)
{
    int i = 1;
    int top = lua_gettop(L);
    printf("stack(%d): ", top);
    for (; i <= top; i++) {
        print_value(L, i);
        printf(" ");
    }
    printf("\n");
}

void print_table(lua_State *L, int i)
{
    if (!lua_istable(L, i)) {
        printf("can print only tables !!!\n");
        return;
    }

    printf("Printing table at index[%d]\n", i);
    /* table is in the stack at index 'i' */
    lua_pushnil(L);  /* first key */

    while (lua_next(L, i) != 0) {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        printf("key: ");
        print_value(L, -2);

        printf(" value: ");
        print_value(L, -1);
        printf("\n");
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
    }
}

