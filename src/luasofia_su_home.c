/* vim: set ts=8 et sw=4 sta ai cin: */
#include <sofia-sip/su_wait.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_home.h"

static int lua_su_home_ref(lua_State *L)
{
    lua_su_home_t *lhome = NULL;
   
    /* get and check first argument (should be a engine) */
    lhome = (lua_su_home_t*)luaL_checkudata(L, 1, SU_HOME_MTABLE);

    lhome->home  = su_home_ref(lhome->home);
    return 0;
}

static int lua_su_home_unref(lua_State *L)
{
    int freed = 0;
    lua_su_home_t *lhome = NULL;

    /* get and check first argument (should be a engine) */
    lhome = (lua_su_home_t*)luaL_checkudata(L, 1, SU_HOME_MTABLE);

    if (lhome->home) {
        freed = su_home_unref(lhome->home);
        if (freed)
            lhome->home = NULL;
    }
    lua_pushinteger(L, freed);
    return 1;
}

static const luaL_Reg su_home_meths[] = {
    {"ref",  lua_su_home_ref },
    {"unref", lua_su_home_unref },
    {"__gc", lua_su_home_unref },
    {NULL, NULL}
};

int luaopen_su_home(lua_State *L)
{
    luaL_newmetatable(L, SU_HOME_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_home_meths);
    lua_pop(L, 1);

    return 0;
}

