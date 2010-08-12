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

#include "utils/luasofia_log.h"

/**@var LUASOFIA_DEBUG
 *
 * Environment variable determining the default debug log level.
 *
 * The LUASOFIA_DEBUG environment variable is used to determine the default
 * debug logging level. The normal level is 3.
 *
 * @sa <sofia-sip/su_debug.h>, su_log_global, SOFIA_DEBUG
 */
extern char const LUASOFIA_DEBUG[];

#ifndef SU_DEBUG
#define SU_DEBUG 3
#endif

/**Debug log for @b luasofia module.
 *
 * The luasofia_log is the log object used by @b luasofia module. The level of
 * #luasofia_log is set using #LUASOFIA_DEBUG environment variable.
 */
su_log_t luasofia_log[] = { SU_LOG_INIT("luasofia", "LUASOFIA_DEBUG", SU_DEBUG) };

static void print_value(lua_State *L, int i)
{
    int t = lua_type(L, i);

    if (lua_isnone(L, i) || lua_isnil(L, i)) {
        SU_DEBUG_9(("Invalid value at index[%d]", i));
        return;
    }

    switch (t) {
        case LUA_TSTRING:
            SU_DEBUG_9(("'%s'", lua_tostring(L, i)));
            break;
        case LUA_TBOOLEAN:
            SU_DEBUG_9((lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TNUMBER:
            SU_DEBUG_9(("%g", lua_tonumber(L, i)));
            break;
        default:
            SU_DEBUG_9(("%s", lua_typename(L, t)));
    }
}

void luasofia_stack_dump(lua_State *L)
{
    int i = 1;
    int top = lua_gettop(L);
    SU_DEBUG_9(("stack(%d): ", top));
    for (; i <= top; i++) {
        print_value(L, i);
        SU_DEBUG_9((" "));
    }
    SU_DEBUG_9(("\n"));
}

void luasofia_log_table(lua_State *L, int i)
{
    if (!lua_istable(L, i)) {
        SU_DEBUG_9(("can print only tables !!!\n"));
        return;
    }

    SU_DEBUG_9(("logging table at index[%d]\n", i));
    /* table is in the stack at index 'i' */
    lua_pushnil(L);  /* first key */

    while (lua_next(L, i) != 0) {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        SU_DEBUG_9(("key: "));
        print_value(L, -2);

        SU_DEBUG_9((" value: "));
        print_value(L, -1);
        SU_DEBUG_9(("\n"));
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
    }
}

