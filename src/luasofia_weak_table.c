/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

void luasofia_weak_table_set(lua_State *L, int weak_table_ref, void* key)
{
   /* put the weak table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, weak_table_ref);
    if (lua_isnil(L, -1)) {
        luaL_error(L, "Failed to get weak table!");
    }
    /* put userdata at top of the stack */
    lua_pushvalue(L, -2);

    /* userdata_table[key] = userdata */
    lua_rawseti(L, -2, (int)key);
    lua_pop(L, 1);
}

int luasofia_weak_table_create(lua_State *L)
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
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

