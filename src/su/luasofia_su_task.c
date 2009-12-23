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

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "su/luasofia_su_task.h"

int luasofia_su_task_create(lua_State *L)
{
    luasofia_su_task_t *ltask = NULL;

    /* create a su_task object */
    ltask = (luasofia_su_task_t*) lua_newuserdata(L, sizeof(luasofia_su_task_t));
    /* set Lua state */
    ltask->L = L;
    ltask->ptask = su_task_init(ltask->task);

    /* set its metatable */
    luaL_getmetatable(L, SU_TASK_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

int luasofia_su_task_init(lua_State *L, _su_task_r ptask)
{
    luasofia_su_task_t *ltask = NULL;

    /* create a su_task object */
    ltask = (luasofia_su_task_t*) lua_newuserdata(L, sizeof(luasofia_su_task_t));
    /* set Lua state */
    ltask->L = L;
    ltask->ptask = ptask;

    /* set its metatable */
    luaL_getmetatable(L, SU_TASK_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_task_destroy(lua_State *L)
{
    luasofia_su_task_t *ltask = NULL;
   
    /* get and check first argument (should be a engine) */
    ltask = (luasofia_su_task_t*)luaL_checkudata(L, 1, SU_TASK_MTABLE);

    if (ltask->ptask == (_su_task_t*)&(ltask->task)) {
        su_task_deinit(ltask->task);
        ltask->ptask = NULL;
    }
    return 0;
}

static int luasofia_su_task_copy(lua_State *L)
{
    return 0;
}

static int luasofia_su_task_move(lua_State *L)
{
    return 0;
}

static int luasofia_su_task_cmp(lua_State *L)
{
    return 0;
}

static int luasofia_su_task_is_running(lua_State *L)
{
    return 0;
}

static int luasofia_su_task_root(lua_State *L)
{
    return 0;
}

static const luaL_Reg su_task_meths[] = {
    {"copy",       luasofia_su_task_copy },
    {"move",       luasofia_su_task_move },
    {"cmp",        luasofia_su_task_cmp },
    {"is_running", luasofia_su_task_is_running },
    {"root",       luasofia_su_task_root },
    {"__gc",       luasofia_su_task_destroy },
    {NULL, NULL}
};

int luasofia_su_task_register_meta(lua_State *L)
{
    luaL_newmetatable(L, SU_TASK_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_task_meths);
    lua_pop(L, 1);

    return 0;
}

