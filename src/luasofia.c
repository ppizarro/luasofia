/* vim: set ts=4 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_weak_table.h"
#include "luasofia_tags.h"
#include "luasofia_struct.h"

int luaopen_luasofia(lua_State *L)
{
    /* create luasofia weak table at REGISTRYINDEX */
    luasofia_weak_table_create(L);

    /* create luasofia tag table at REGISTRYINDEX */
    luasofia_tags_create(L);

    /* create luasofia meta struct at REGISTRYINDEX */
    luasofia_register_struct_meta(L);

    return 1;
}

