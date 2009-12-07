/* vim: set ts=8 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_home.h"

int luasofia_su_home_new(lua_State *L)
{
    su_home_t *home = NULL;
    luasofia_su_home_t *lhome = NULL;
    int size = luaL_optint(L, 1, sizeof(su_home_t));

    /* create the su_home */
    home = su_home_new(size);
    if (!home)
        luaL_error(L, "su_home_new failed!");

    /* create a su_home object */
    lhome = (luasofia_su_home_t*) lua_newuserdata(L, sizeof(luasofia_su_home_t));
    /* set Lua state */
    lhome->L = L;
    lhome->home = home;

    /* set its metatable */
    luaL_getmetatable(L, SU_HOME_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_home_ref(lua_State *L)
{
    luasofia_su_home_t *lhome = NULL;
   
    /* get and check first argument (should be a engine) */
    lhome = (luasofia_su_home_t*)luaL_checkudata(L, 1, SU_HOME_MTABLE);

    lhome->home  = su_home_ref(lhome->home);
    return 0;
}

static int luasofia_su_home_unref(lua_State *L)
{
    int freed = 0;
    luasofia_su_home_t *lhome = NULL;

    /* get and check first argument (should be a engine) */
    lhome = (luasofia_su_home_t*)luaL_checkudata(L, 1, SU_HOME_MTABLE);

    if (lhome->home) {
        freed = su_home_unref(lhome->home);
        if (freed)
            lhome->home = NULL;
    }
    lua_pushinteger(L, freed);
    return 1;
}

static const luaL_Reg su_home_meths[] = {
    {"ref",  luasofia_su_home_ref },
    {"unref", luasofia_su_home_unref },
    {"__gc", luasofia_su_home_unref },
    {NULL, NULL}
};

int luasofia_su_home_register_meta(lua_State *L)
{
    luaL_newmetatable(L, SU_HOME_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, su_home_meths);
    lua_pop(L, 1);

    return 0;
}

