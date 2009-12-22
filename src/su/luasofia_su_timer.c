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

#include "su/luasofia_su_timer.h"
#include "su/luasofia_su_task.h"
#include "utils/luasofia_weak_table.h"

int luasofia_su_timer_create(lua_State *L)
{
    su_timer_t *timer = NULL;
    luasofia_su_timer_t *ltimer = NULL;
    luasofia_su_task_t *ltask = NULL;
    //su_task_r const task = NULL;
    su_duration_t msec = 0;

    /* get first argument (a task) */
    ltask = (luasofia_su_task_t*)luaL_checkudata(L, 1, SU_TASK_MTABLE);

    /* get second argument (a duration int) */
    msec = luaL_checkinteger(L, 2);

    /* create the su_timer */
    timer = su_timer_create(ltask->ptask, msec);
    if (!timer)
        luaL_error(L, "su_timer_create failed!");

    /* create a su_timer object */
    ltimer = (luasofia_su_timer_t*) lua_newuserdata(L, sizeof(luasofia_su_timer_t));
    /* set Lua state */
    ltimer->L = L;
    ltimer->timer = timer;

    /* set its metatable */
    luaL_getmetatable(L, SU_TIMER_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua at nua weak table */
    luasofia_weak_table_set(L, timer);
    return 1;
}

static int luasofia_su_timer_destroy(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;

    /* get and check first argument (should be a engine) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, 1, SU_TIMER_MTABLE);

    if (ltimer->timer) {
        /* remove timer of the luasofia weak table */
        luasofia_weak_table_remove(L, ltimer->timer);

        su_timer_destroy(ltimer->timer);
        ltimer->timer = NULL;
    }
    return 0;
}

static void luasofia_su_timer_callback(su_root_magic_t *magic,
                                  su_timer_t *t,
                                  su_timer_arg_t *arg)
{
    luasofia_su_timer_t *ltimer = (luasofia_su_timer_t*)arg;
    lua_State *L = ltimer->L;

    // put userdatum at stack and check if it is ok.
    luasofia_weak_table_get(L, ltimer->timer);
    luaL_checkudata(L, -1, SU_TIMER_MTABLE);

    /* put callback table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        return;
    }

    /* get callback */
    lua_getfield(L, -1, "timer_handler");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 3);
        return;
    }

    lua_pushvalue(L, -3);
    lua_call(L, 1, 0);
    lua_pop(L, 2);
}

static int luasofia_su_timer_set(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;
   
    /* get and check first argument (should be a timer) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -2, SU_TIMER_MTABLE);

    /* check the callback table */
    luaL_checktype(L, -1, LUA_TTABLE);

    /* set callback table as environment for udata */
    lua_setfenv(L, -2);

    su_timer_set(ltimer->timer, luasofia_su_timer_callback, ltimer);
    return 0;
}

static int luasofia_su_timer_set_interval(lua_State *L)
{
    return 0;
}

static int luasofia_su_timer_set_at(lua_State *L)
{
    return 0;
}

static int luasofia_su_timer_run(lua_State *L)
{
    return 0;
}

static int luasofia_su_timer_set_for_ever(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;
   
    /* get and check first argument (should be a timer) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -2, SU_TIMER_MTABLE);

    /* check the callback table */
    luaL_checktype(L, -1, LUA_TTABLE);

    /* set callback table as environment for udata */
    lua_setfenv(L, -2);

    su_timer_set_for_ever(ltimer->timer, luasofia_su_timer_callback, ltimer);
    return 0;
}

static int luasofia_su_timer_reset(lua_State *L)
{
    /* get and check first argument (should be a timer) */
    luasofia_su_timer_t *ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -1, SU_TIMER_MTABLE);
    su_timer_reset(ltimer->timer);
    return 0;
}

static int luasofia_su_timer_root(lua_State *L)
{
    return 0;
}

static int luasofia_su_timer_expire(lua_State *L)
{
    return 0;
}

static const luaL_Reg su_timer_meths[] = {
    {"set",          luasofia_su_timer_set },
    {"set_interval", luasofia_su_timer_set_interval },
    {"set_at",       luasofia_su_timer_set_at },
    {"run",          luasofia_su_timer_run },
    {"set_for_ever", luasofia_su_timer_set_for_ever },
    {"reset",        luasofia_su_timer_reset },
    {"root",         luasofia_su_timer_root },
    {"expire",       luasofia_su_timer_expire },
    {"destroy",      luasofia_su_timer_destroy },
    {"__gc",         luasofia_su_timer_destroy },
    {NULL, NULL}
};

int luasofia_su_timer_register_meta(lua_State *L)
{
    luaL_newmetatable(L, SU_TIMER_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_timer_meths);
    lua_pop(L, 1);

    return 0;
}

