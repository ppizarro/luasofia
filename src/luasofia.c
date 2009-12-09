/* vim: set ts=4 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_weak_table.h"
#include "luasofia_tags.h"
#include "luasofia_proxy.h"

static const struct luaL_reg core_lib[] = {
  {NULL, NULL},
};

int luaopen_luasofia(lua_State *L)
{ 
    lua_getglobal(L, "luasofia");
    if(!lua_isnil(L, -1))
        return 1;

    /* create luasofia weak table at REGISTRYINDEX */
    luasofia_weak_table_create(L);

    /* create luasofia tag table at REGISTRYINDEX */
    luasofia_tags_create(L);

    luasofia_proxy_init(L);

    luaL_register(L, "luasofia", core_lib);
    return 1;
}

