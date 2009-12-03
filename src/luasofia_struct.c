/* vim: set ts=4 et sw=4 sta ai cin: */

#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_struct.h"
#include "luasofia_utils.h"

#define LUASOFIA_STRUCT_META "luasofia_struct"

int luasofia_struct_create_info_table(lua_State *L, const luasofia_struct_info_t *l)
{
    lua_newtable(L);
    for (; l->name; l++) {
        lua_pushstring(L, l->name);
        lua_pushlightuserdata(L, (void*)l);
        lua_rawset(L, -3);
    }
    return 1;
}

int luasofia_struct_create(lua_State *L, size_t size)
{
    void **ust = NULL;
    void *p = NULL;

    if(lua_type(L, -2) == LUA_TLIGHTUSERDATA) {
        p = lua_touserdata(L, -2);
    } else if(size > 0) {
        p = malloc(size);
        memset(p, 0, size);
        lua_pushlightuserdata(L, p);
        lua_insert(L, -2);
    } else {
        luaL_error(L, "cannot create struct!");
    }

    /* check the struct info table at stack top */
    luaL_checktype(L, -1, LUA_TTABLE);

    /* create a userdata struct */
    ust = (void**)lua_newuserdata(L, sizeof(void*));
    *ust = p;

    luaL_getmetatable(L, LUASOFIA_STRUCT_META);
    lua_setmetatable(L, -2);

    /* set struct info table as environment for udata */
    lua_pushvalue(L, -2);
    lua_setfenv(L, -2);
    return 1;
}

int luasofia_struct_get_int (lua_State *L, void *v)
{
  lua_pushnumber(L, *(int*)v);
  return 1;
}

int luasofia_struct_set_int (lua_State *L, void *v)
{
  *(int*)v = luaL_checkint(L, 3);
  return 0;
}

int luasofia_struct_get_short (lua_State *L, void *v)
{
  lua_pushnumber(L, *(short*)v);
  return 1;
}

int luasofia_struct_set_short (lua_State *L, void *v)
{
  *(short*)v = luaL_checkint(L, 3);
  return 0;
}

int luasofia_struct_get_char (lua_State *L, void *v)
{
  lua_pushnumber(L, *(char*)v);
  return 1;
}

int luasofia_struct_set_char (lua_State *L, void *v)
{
  *(char*)v = luaL_checkint(L, 3);
  return 0;
}

int luasofia_struct_get_number (lua_State *L, void *v)
{
  lua_pushnumber(L, *(lua_Number*)v);
  return 1;
}

int luasofia_struct_set_number (lua_State *L, void *v)
{
  *(lua_Number*)v = luaL_checknumber(L, 3);
  return 0;
}

int luasofia_struct_get_string (lua_State *L, void *v)
{
  lua_pushstring(L, *(char**)v );
  return 1;
}

int luasofia_struct_set_string (lua_State *L, void *v)
{
    // FIXME Criar uma copia da string e liberar a atual
    *((char**)v) = (lua_isnil(L, 3) ? NULL : (char*)lua_tostring(L, 3));
    return 0;
}

static int luasofia_struct_destroy(lua_State *L)
{
    return 0;
}

static int luasofia_struct_index(lua_State *L)
{
    luasofia_struct_info_t* m = NULL;

    /* stack has userdata, index */
    void** ust = luaL_checkudata(L, 1, LUASOFIA_STRUCT_META);

    /* put struct info table at stack */
    lua_getfenv(L, 1);

    /* put index at stack top */
    lua_pushvalue(L, 2);

    /* lookup member by name */
    lua_rawget(L, -2);      
    if (!lua_islightuserdata(L, -1))
        luaL_error(L, "cannot get member '%s'", lua_tostring(L, 2));
    m = (luasofia_struct_info_t*)lua_touserdata(L, -1);

    /* drop lightuserdata and info table */
    lua_pop(L, 2);

    /* for get: stack has userdata, index, lightuserdata */
    return m->get_func(L, (void *)(((char *)*ust) + m->offset));
}

static int luasofia_struct_newindex(lua_State *L)
{
    /* for set: stack has userdata, index, value, lightuserdata */
    return 0;
}

static int luasofia_struct_tostring(lua_State *L)
{
    return 0;
}

int luasofia_register_struct_meta(lua_State *L)
{
    luaL_newmetatable(L, LUASOFIA_STRUCT_META);

    lua_pushliteral(L, "__index");
    lua_pushcfunction(L, luasofia_struct_index);
    lua_settable(L, -3);

    lua_pushliteral(L, "__newindex");
    lua_pushcfunction(L, luasofia_struct_newindex);
    lua_settable(L, -3);

    lua_pushliteral(L, "__tostring");
    lua_pushcfunction(L, luasofia_struct_tostring);
    lua_settable(L, -3);

    lua_pushliteral(L, "__gc");
    lua_pushcfunction(L, luasofia_struct_destroy);
    lua_settable(L, -3);

    lua_pop(L, 1);

    return 0;
}

