/* vim: set ts=4 et sw=4 sta ai cin: */
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

#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "utils/luasofia_proxy.h"

static int proxy_table_ref = LUA_REFNIL;

#define LUASOFIA_PROXY_META "luasofia_proxy"

int luasofia_proxy_register_info_table(lua_State *L, const char* name, const luasofia_proxy_info_t *l)
{
    if (!name || !l) return 0;

    /* put the proxy table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, proxy_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get proxy info table!");

    lua_pushstring(L, name);
    lua_newtable(L);
    for (; l->name; l++) {
        /* new_table[l->name] = l */
        lua_pushstring(L, l->name);
        lua_pushlightuserdata(L, (void*)l);
        lua_rawset(L, -3);
    }
    /* proxy_table[name] = new_table*/
    lua_rawset(L, -3);
    lua_pop(L, 1);
    return 0;
}

int luasofia_proxy_create(lua_State *L, const char* name)
{
    void **ust = NULL;
    void *p = lua_touserdata(L, -1);
    luaL_argcheck(L, p != NULL, -1, "lightuserdata expected");

    /* put the proxy_table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, proxy_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get proxy info table!");

    /* put the info_table of the given proxy name at the stack. stach.push(proxy_table[name]) */
    lua_pushstring(L, name);
    lua_rawget(L, -2);

    /* check the info_table at stack top */
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get info table!");
    
    /* remove proxy_table from the stack */
    lua_remove(L, -2);

    /* create a userdata struct */
    ust = (void**)lua_newuserdata(L, sizeof(void*));
    *ust = p;

    /* set the proxy_metatable as the metatable for the userdata */
    luaL_getmetatable(L, LUASOFIA_PROXY_META);
    lua_setmetatable(L, -2);

    /* push the info_table at the top of the stack */
    lua_pushvalue(L, -2);

    /* set the info_table as environment var for this userdata */
    lua_setfenv(L, -2);

    /* remove the info_table from the stack, returning the userdata at the lua_State L stack*/
    lua_remove(L, -2);
    return 1;
}

int luasofia_proxy_get_int (lua_State *L, void *v)
{
    lua_pushnumber(L, *(int*)v);
    return 1;
}

int luasofia_proxy_get_boolean (lua_State *L, void *v)
{
    lua_pushboolean(L, *(int*)v);
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
    void** ust = luaL_checkudata(L, -2, LUASOFIA_PROXY_META);

    /* put struct info table at stack */
    lua_getfenv(L, -2);

    /* put index at stack top */
    lua_pushvalue(L, -2);

    /* lookup member by name */
    lua_rawget(L, -2);      
    if (!lua_islightuserdata(L, -1))
        luaL_error(L, "cannot get member '%s'", lua_tostring(L, -3));
    m = (luasofia_proxy_info_t*)lua_touserdata(L, -1);

    /* drop lightuserdata and info table */
    lua_pop(L, 2);

    /* for get: stack has userdata, index, lightuserdata */
    return m->get_func(L, (void *)(((char *)*ust) + m->offset));
}

static int luasofia_proxy_tostring(lua_State *L)
{
    /* stack has userdata */
    void** ust = luaL_checkudata(L, -1, LUASOFIA_PROXY_META);

    if (ust)
        lua_pushfstring(L, "proxy: %p", *ust);
    else
        lua_pushstring(L, "proxy: nil");
    return 1;
}

void luasofia_proxy_init(lua_State *L)
{
    /* create userdata table */
    lua_newtable(L);
   
    /* now lets store the proxy table at the LUA_REGISTRYINDEX, */
    proxy_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    luaL_newmetatable(L, LUASOFIA_PROXY_META);

    lua_pushliteral(L, "__index");
    lua_pushcfunction(L, luasofia_proxy_index);
    lua_settable(L, -3);

    lua_pushliteral(L, "__tostring");
    lua_pushcfunction(L, luasofia_proxy_tostring);
    lua_settable(L, -3);

    lua_pop(L, 1);
}

