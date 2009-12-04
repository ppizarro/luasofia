/* vim: set ts=4 et sw=4 sta ai cin: */

#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_proxy.h"
#include "luasofia_utils.h"

#define LUASOFIA_PROXY_META "luasofia_proxy"

int luasofia_proxy_create_info_table(lua_State *L, const luasofia_proxy_info_t *l)
{
    lua_newtable(L);
    for (; l->name; l++) {
        lua_pushstring(L, l->name);
        lua_pushlightuserdata(L, (void*)l);
        lua_rawset(L, -3);
    }
    return 1;
}

int luasofia_proxy_create(lua_State *L)
{
    void **ust = NULL;
    void *p = lua_touserdata(L, -2);
    luaL_argcheck(L, p != NULL, -2, "lightuserdata expected");
         
    /* check the struct info table at stack top */
    luaL_checktype(L, -1, LUA_TTABLE);

    /* create a userdata struct */
    ust = (void**)lua_newuserdata(L, sizeof(void*));
    *ust = p;

    luaL_getmetatable(L, LUASOFIA_PROXY_META);
    lua_setmetatable(L, -2);

    /* set struct info table as environment for udata */
    lua_pushvalue(L, -2);
    lua_setfenv(L, -2);
    return 1;
}

int luasofia_proxy_get_int (lua_State *L, void *v)
{
    lua_pushnumber(L, *(int*)v);
    return 1;
}

int luasofia_proxy_get_short (lua_State *L, void *v)
{
    lua_pushnumber(L, *(short*)v);
    return 1;
}

int luasofia_proxy_get_char (lua_State *L, void *v)
{
    lua_pushnumber(L, *(char*)v);
    return 1;
}

int luasofia_proxy_get_number (lua_State *L, void *v)
{
    lua_pushnumber(L, *(lua_Number*)v);
    return 1;
}

int luasofia_proxy_get_string (lua_State *L, void *v)
{
    lua_pushstring(L, *(char**)v );
    return 1;
}

int luasofia_proxy_get_pointer (lua_State *L, void *v)
{
    void *p;
    p = *((void**)v);
    p ? lua_pushlightuserdata(L, p) : lua_pushnil(L);
    return 1;
}

int luasofia_proxy_get_address (lua_State *L, void *v)
{
    lua_pushlightuserdata(L, v);
    return 1;
}

static int luasofia_proxy_index(lua_State *L)
{
    luasofia_proxy_info_t* m = NULL;

    /* stack has userdata, index */
    void** ust = luaL_checkudata(L, 1, LUASOFIA_PROXY_META);

    /* put struct info table at stack */
    lua_getfenv(L, 1);

    /* put index at stack top */
    lua_pushvalue(L, 2);

    /* lookup member by name */
    lua_rawget(L, -2);      
    if (!lua_islightuserdata(L, -1))
        luaL_error(L, "cannot get member '%s'", lua_tostring(L, 2));
    m = (luasofia_proxy_info_t*)lua_touserdata(L, -1);

    /* drop lightuserdata and info table */
    lua_pop(L, 2);

    /* for get: stack has userdata, index, lightuserdata */
    return m->get_func(L, (void *)(((char *)*ust) + m->offset));
}

static int luasofia_proxy_tostring(lua_State *L)
{
    // TODO
    return 0;
}

int luasofia_register_struct_meta(lua_State *L)
{
    luaL_newmetatable(L, LUASOFIA_PROXY_META);

    lua_pushliteral(L, "__index");
    lua_pushcfunction(L, luasofia_proxy_index);
    lua_settable(L, -3);

    lua_pushliteral(L, "__tostring");
    lua_pushcfunction(L, luasofia_proxy_tostring);
    lua_settable(L, -3);

    lua_pop(L, 1);
    return 0;
}

