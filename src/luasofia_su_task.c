/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_task.h"

int lua_su_task_init(lua_State *L)
{
    lua_su_task_t *ltask = NULL;

    /* create a su_task object */
    ltask = (lua_su_task_t*) lua_newuserdata(L, sizeof(lua_su_task_t));
    /* set Lua state */
    ltask->L = L;
    ltask->ptask = su_task_init(ltask->task);

    /* set its metatable */
    luaL_getmetatable(L, SU_TASK_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

int lua_su_task_create(lua_State *L, _su_task_r ptask)
{
    lua_su_task_t *ltask = NULL;

    /* create a su_task object */
    ltask = (lua_su_task_t*) lua_newuserdata(L, sizeof(lua_su_task_t));
    /* set Lua state */
    ltask->L = L;
    ltask->ptask = ptask;

    /* set its metatable */
    luaL_getmetatable(L, SU_TASK_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_su_task_destroy(lua_State *L)
{
    lua_su_task_t *ltask = NULL;
   
    /* get and check first argument (should be a engine) */
    ltask = (lua_su_task_t*)luaL_checkudata(L, 1, SU_TASK_MTABLE);

    if (ltask->ptask == (_su_task_t*)&(ltask->task)) {
        su_task_deinit(ltask->task);
        ltask->ptask = NULL;
    }
    return 0;
}

static int lua_su_task_deinit(lua_State *L)
{
    lua_su_task_t *ltask = NULL;
   
    /* get and check first argument (should be a engine) */
    ltask = (lua_su_task_t*)luaL_checkudata(L, 1, SU_TASK_MTABLE);

    su_task_deinit(ltask->task);
    return 0;
}

static int lua_su_task_copy(lua_State *L)
{
    return 0;
}

static int lua_su_task_move(lua_State *L)
{
    return 0;
}

static int lua_su_task_cmp(lua_State *L)
{
    return 0;
}

static int lua_su_task_is_running(lua_State *L)
{
    return 0;
}

static int lua_su_task_root(lua_State *L)
{
    return 0;
}

static int lua_su_task_wakeup(lua_State *L)
{
    lua_su_task_t *ltask = NULL;
    int ret = -1;
   
    /* get and check first argument (should be a engine) */
    ltask = (lua_su_task_t*)luaL_checkudata(L, 1, SU_TASK_MTABLE);

    ret = su_task_wakeup(ltask->task);
    lua_pushinteger(L, ret);
    return 1;
}

static const luaL_Reg su_task_meths[] = {
    {"deinit",     lua_su_task_deinit },
    {"copy",       lua_su_task_copy },
    {"move",       lua_su_task_move },
    {"cmp",        lua_su_task_cmp },
    {"is_running", lua_su_task_is_running },
    {"root",       lua_su_task_root },
    {"wakeup",     lua_su_task_wakeup },
    {"__gc",       lua_su_task_destroy },
    {NULL, NULL}
};

int luasofia_register_task_meta(lua_State *L)
{
    luaL_newmetatable(L, SU_TASK_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_task_meths);
    lua_pop(L, 1);

    return 0;
}

