/* vim: set ts=4 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su.h"
#include "luasofia_nua.h"
#include "luasofia_weak_table.h"

int luaopen_luasofia(lua_State *L)
{
    /* create luasofia weak table at REGISTRYINDEX */
    luasofia_weak_table_create(L);

    luaopen_su(L);
    luaopen_nua(L);

    return 1;
}

