/* vim: set ts=4 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su.h"
#include "luasofia_nua.h"

int luaopen_luasofia(lua_State *L)
{
    luaopen_su(L);
    luaopen_nua(L);

    return 1;
}

