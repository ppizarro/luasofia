/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static int weak_table_ref = LUA_REFNIL;

void luasofia_weak_table_remove(lua_State *L, void* key)
{
    /* put the weak table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, weak_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get weak table!");

    /* weak_table[key] = nil */
    lua_pushlightuserdata(L, key);
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_pop(L, 1);
}

void luasofia_weak_table_get(lua_State *L, void* key)
{
    /* put the weak table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, weak_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get weak table!");

    /* get weak_table[key] */
    lua_pushlightuserdata(L, key);
    lua_rawget(L, -2);

    /* remove the table from the stack */
    lua_remove(L, -2);
}

void luasofia_weak_table_set(lua_State *L, void* key)
{
   /* put the weak table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, weak_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get weak table!");

    /* put key at top of the stack */
    lua_pushlightuserdata(L, key);

    /* put userdata at top of the stack */
    lua_pushvalue(L, -3);

    /* weak_table[key] = userdata */
    lua_rawset(L, -3);
    lua_pop(L, 1);
}

void luasofia_weak_table_create(lua_State *L)
{
    /* create userdata table */
    lua_newtable(L);
   
    /* first create an metatable with __mode=v, */
    /* so only values are weak references */
    luaL_newmetatable(L, "kws_engine_userdata_metatable");
    //luaL_newtable(L);
    lua_pushstring(L,"v");
    lua_setfield(L, -2, "__mode");

    /* now lets set the metatable who holds weak values */
    /* as the metatable of the userdata table */
    lua_setmetatable(L, -2);

    /* now lets store the weak table at the LUA_REGISTRYINDEX, */
    /* so it can be acessed by the unregistered callback functions */
    weak_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

