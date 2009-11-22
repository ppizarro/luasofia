/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_timer.h"
#include "luasofia_weak_table.h"

int lua_su_timer_create(lua_State *L)
{
    su_timer_t *timer = NULL;
    lua_su_timer_t *ltimer = NULL;
    //su_task_r const task = NULL;
    su_duration_t msec = 0;

    // TODO pegar task object
    //task = luaL_checkluserdata(L, 1);

    /* get second argument (a duration int) */
    msec = luaL_checkinteger(L, 2);
printf("su_timer_create...\n");
    /* create the su_timer */
    timer = su_timer_create(NULL, msec);
    if (!timer)
        luaL_error(L, "su_timer_create failed!");
printf("su_timer_create OK!\n");

    /* create a su_timer object */
    ltimer = (lua_su_timer_t*) lua_newuserdata(L, sizeof(lua_su_timer_t));
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

static int lua_su_timer_destroy(lua_State *L)
{
    lua_su_timer_t *ltimer = NULL;
   
    /* get and check first argument (should be a engine) */
    ltimer = (lua_su_timer_t*)luaL_checkudata(L, 1, SU_TIMER_MTABLE);

    if (ltimer->timer) {
        su_timer_destroy(ltimer->timer);
        ltimer->timer = NULL;
    }
    return 0;
}

static void lua_su_timer_callback(su_root_magic_t *magic,
                                  su_timer_t *t,
                                  su_timer_arg_t *arg)
{
    lua_su_timer_t *ltimer = (lua_su_timer_t*)arg;
    lua_State *L = ltimer->L;

    // put userdataum at stack and check if it is ok.
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

    lua_call(L, 2, 0);
}

static int lua_su_timer_set(lua_State *L)
{
    lua_su_timer_t *ltimer = NULL;
   
    /* get and check first argument (should be a engine) */
    ltimer = (lua_su_timer_t*)luaL_checkudata(L, -2, SU_TIMER_MTABLE);

    /* check the callback table */
    luaL_checktype(L, -1, LUA_TTABLE);

    /* set callback table as environment for udata */
    lua_setfenv(L, -2);

    su_timer_set(ltimer->timer, lua_su_timer_callback, NULL);
    return 0;
}

static int lua_su_timer_set_interval(lua_State *L)
{
    return 0;
}

static int lua_su_timer_set_at(lua_State *L)
{
    return 0;
}

static int lua_su_timer_run(lua_State *L)
{
    return 0;
}

static int lua_su_timer_set_for_ever(lua_State *L)
{
    return 0;
}

static int lua_su_timer_reset(lua_State *L)
{
    return 0;
}

static int lua_su_timer_root(lua_State *L)
{
    return 0;
}

static int lua_su_timer_expire(lua_State *L)
{
    return 0;
}

static const luaL_Reg su_timer_meths[] = {
    {"set",          lua_su_timer_set },
    {"set_interval", lua_su_timer_set_interval },
    {"set_at",       lua_su_timer_set_at },
    {"run",          lua_su_timer_run },
    {"set_for_ever", lua_su_timer_set_for_ever },
    {"reset",        lua_su_timer_reset },
    {"root",         lua_su_timer_root },
    {"expire",       lua_su_timer_expire },
    {"__gc",         lua_su_timer_destroy},
    {NULL, NULL}
};

int luaopen_su_timer(lua_State *L)
{
    luaL_newmetatable(L, SU_TIMER_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_timer_meths);
    lua_pop(L, 1);

    return 0;
}

