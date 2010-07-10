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

#include "su/luasofia_su_root.h"
#include "su/luasofia_su_task.h"

int luasofia_su_root_create(lua_State *L)
{
    su_root_t *root = NULL;
    luasofia_su_root_t *lroot = NULL;

    /* create the su_root */
    root = su_root_create(NULL);
    if (!root)
        luaL_error(L, "su_root_create failed!");

    /* create a su_root object */
    lroot = (luasofia_su_root_t*) lua_newuserdata(L, sizeof(luasofia_su_root_t));
    /* set Lua state */
    lroot->L = L;
    lroot->root = root;

    /* set its metatable */
    luaL_getmetatable(L, SU_ROOT_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_root_destroy(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;

    /* get and check first argument (should be a root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -1, SU_ROOT_MTABLE);

    if (lroot->root) {
        su_root_destroy(lroot->root);
        lroot->root = NULL;
    }
    return 0;
}

static int luasofia_su_root_register(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_deregister(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_unregister(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_run(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;
   
    /* get and check first argument (should be a root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -1, SU_ROOT_MTABLE);

    su_root_run(lroot->root);
    return 0;
}

static int luasofia_su_root_break(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;
   
    /* get and check first argument (should be a root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -1, SU_ROOT_MTABLE);

    su_root_break(lroot->root);
    return 0;
}

static int luasofia_su_root_threading(lua_State *L)
{
    int enable = 0;

    luasofia_su_root_t *lroot = NULL;
   
    /* get enable param */
    enable = lua_toboolean(L, -1);

    /* get and check first argument (should be a root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -2, SU_ROOT_MTABLE);

    enable = su_root_threading(lroot->root, enable);

    lua_pushboolean(L, enable);
    return 1;
}

static int luasofia_su_root_step(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_get_max_defer(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_set_max_defer(lua_State *L)
{
    return 0;
}

static int luasofia_su_root_task(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;
   
    /* get and check first argument (should be a root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -1, SU_ROOT_MTABLE);

    luasofia_su_task_init(L, su_root_task(lroot->root));
    return 1;
}

static int luasofia_su_root_gsource(lua_State *L)
{
    return 0;
}

static const luaL_Reg su_root_meths[] = {
    {"register", luasofia_su_root_register },
    {"deregister", luasofia_su_root_deregister },
    {"unregister", luasofia_su_root_unregister },
    {"run", luasofia_su_root_run },
    {"quit", luasofia_su_root_break },
    {"step", luasofia_su_root_step },
    {"threading", luasofia_su_root_threading },
    {"get_max_defer", luasofia_su_root_get_max_defer },
    {"set_max_defer", luasofia_su_root_set_max_defer },
    {"task", luasofia_su_root_task },
    {"gsource", luasofia_su_root_gsource },
    {"__gc", luasofia_su_root_destroy },
    {NULL, NULL}
};

int luasofia_su_root_register_meta(lua_State *L)
{
    if (luaL_newmetatable(L, SU_ROOT_MTABLE) != 0) {
        /* metatable.__index = metatable */
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, su_root_meths);
        lua_pop(L, 1);
    }
    return 0;
}

