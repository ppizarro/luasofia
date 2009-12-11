/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_tags.h"

#define LUASOFIA_TAGS_META "luasofia_tags"

int luasofia_su_tags_get_proxy(lua_State *L)
{
    void **ust = NULL;
    void *p = lua_touserdata(L, -1);
    luaL_argcheck(L, p != NULL, -1, "lightuserdata expected");

    /* create a userdata struct */
    ust = (void**)lua_newuserdata(L, sizeof(void*));
    *ust = p;

    /* set the proxy_metatable as the metatable for the userdata */
    luaL_getmetatable(L, LUASOFIA_TAGS_META);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_tags_index(lua_State *L)
{
    /* stack has userdata, index */
    //void** ust = luaL_checkudata(L, 1, LUASOFIA_TAGS_META);

    lua_pushnil(L);
    return 1;
}

int luasofia_su_tags_register_meta(lua_State *L)
{
    luaL_newmetatable(L, LUASOFIA_TAGS_META);

    lua_pushliteral(L, "__index");
    lua_pushcfunction(L, luasofia_su_tags_index);
    lua_settable(L, -3);

    lua_pop(L, 1);
    return 0;
}

