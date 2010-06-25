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

#include "su/luasofia_su_timer.h"
#include "su/luasofia_su_task.h"
#include "utils/luasofia_userdata_table.h"
#include "utils/luasofia_utils.h"

#define SU_TIMER_MTABLE "su_timer_t"

typedef struct luasofia_su_timer_s {
    su_timer_t *timer;
    int for_ever;
} luasofia_su_timer_t;


static void luasofia_su_timer_set_function_env(lua_State *L)
{
    /* check the callback function */
    luaL_checktype(L, -1, LUA_TFUNCTION);

    /* create environment table */
    lua_createtable(L, 1, 0);

    /* put callback function at top */
    lua_pushvalue(L, -2);

    /* t[1] = function */
    lua_rawseti(L, -2, 1);

    lua_setfenv(L, -3);
}


static int luasofia_su_timer_get_function_env(lua_State *L)
{
    /* put enviroment table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    /* get callback function */
    lua_rawgeti(L, -1, 1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        return 0;
    }
    return 1;
}


static void luasofia_su_timer_del_function_env(lua_State *L)
{
    /* put enviroment table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    /* put nil at top */
    lua_pushnil(L);

    /* t[1] = nil */
    lua_rawseti(L, -2, 1);

    /* remove enviroment table from stack */
    lua_pop(L, 1);
}


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
    if (!timer) {
        luaL_error(L, "su_timer_create failed!");
    }

    /* create a su_timer object */
    ltimer = (luasofia_su_timer_t*) lua_newuserdata(L, sizeof(luasofia_su_timer_t));
    /* set Lua state */
    ltimer->timer = timer;
    ltimer->for_ever = 0;

    /* set its metatable */
    luaL_getmetatable(L, SU_TIMER_MTABLE);
    lua_setmetatable(L, -2);

    return 1;
}


static int luasofia_su_timer_destroy(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;

    /* get and check first argument (should be a timer) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, 1, SU_TIMER_MTABLE);

    if (ltimer->timer) {
        su_timer_destroy(ltimer->timer);
        ltimer->timer = NULL;
    }
    return 0;
}


static void luasofia_su_timer_callback(su_root_magic_t *magic,
                                       su_timer_t *t,
                                       su_timer_arg_t *arg)
{
    luasofia_su_timer_t *ltimer = NULL;
    lua_State *L = (lua_State*)arg;

    // put userdatum at stack and check if it is ok.
    luasofia_userdata_table_get(L, t);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        luaL_error(L, "Fatal error on su_timer callback, "
                      "callback called but was impossible "
                      "to recover the su_timer userdata !");     
    }

    ltimer = luaL_checkudata(L, -1, SU_TIMER_MTABLE);

    /* get callback function from enviroment table */
    if(!luasofia_su_timer_get_function_env(L)) {
        lua_pop(L, 1);
        luaL_error(L, "Fatal error on su_timer callback, "
                      "callback called but was impossible "
                      "to recover lua callback function!");
    }

    lua_pushvalue(L, -3);

    if (!ltimer->for_ever) {
        /* remove callback function from enviroment */
        luasofia_su_timer_del_function_env(L);

        /* remove timer of the luasofia userdata table */
        luasofia_userdata_table_remove(L, t);
    }

    lua_call(L, 1, 0);
    lua_pop(L, 2);
}


static int luasofia_su_timer_set(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;

    /* get and check first argument (should be a timer) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -2, SU_TIMER_MTABLE);

    /* store timer at timer userdata table */
    lua_pushvalue(L, -2);
    luasofia_userdata_table_set(L, ltimer->timer);
    lua_pop(L, 1);

    /* set callback function as environment for udata */
    luasofia_su_timer_set_function_env(L);

    su_timer_set(ltimer->timer, luasofia_su_timer_callback, L);
    ltimer->for_ever = 0;
    return 0;
}


static int luasofia_su_timer_set_interval(lua_State *L)
{
    luaL_error(L, "Unimplemented method, feel free to colaborate :-)");
    return 0;
}


static int luasofia_su_timer_run(lua_State *L)
{
    luaL_error(L, "Unimplemented method, feel free to colaborate :-)");
    return 0;
}


static int luasofia_su_timer_set_for_ever(lua_State *L)
{
    luasofia_su_timer_t *ltimer = NULL;
   
    /* get and check first argument (should be a timer) */
    ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -2, SU_TIMER_MTABLE);

    /* store timer at timer userdata table */
    lua_pushvalue(L, -2);
    luasofia_userdata_table_set(L, ltimer->timer);
    lua_pop(L, 1);

    /* set callback function as environment for udata */
    luasofia_su_timer_set_function_env(L);

    su_timer_set_for_ever(ltimer->timer, luasofia_su_timer_callback, L);
    ltimer->for_ever = 1;
    return 0;
}


static int luasofia_su_timer_reset(lua_State *L)
{
    /* get and check first argument (should be a timer) */
    luasofia_su_timer_t *ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -1, SU_TIMER_MTABLE);

    su_timer_reset(ltimer->timer);

    /* remove callback function from enviroment */

    luasofia_su_timer_del_function_env(L);

    /* remove timer of the luasofia userdata table */
    luasofia_userdata_table_remove(L, ltimer->timer);
    return 0;
}

#ifdef HAVE_SOFIA_DEVEL
static int luasofia_su_timer_is_set(lua_State *L)
{
    /* get and check first argument (should be a timer) */
    luasofia_su_timer_t *ltimer = (luasofia_su_timer_t*)luaL_checkudata(L, -1, SU_TIMER_MTABLE);
    lua_pushboolean(L, su_timer_is_set(ltimer->timer));
    return 1;
}
#endif

static int luasofia_su_timer_root(lua_State *L)
{
    luaL_error(L, "Unimplemented method, feel free to colaborate :-)");
    return 0;
}


static const luaL_Reg su_timer_meths[] = {
    {"set",          luasofia_su_timer_set },
    {"set_interval", luasofia_su_timer_set_interval },
    {"set_for_ever", luasofia_su_timer_set_for_ever },
    {"reset",        luasofia_su_timer_reset },
#ifdef HAVE_SOFIA_DEVEL
    {"is_set",       luasofia_su_timer_is_set },
#endif
    {"run",          luasofia_su_timer_run },
    {"root",         luasofia_su_timer_root },
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

