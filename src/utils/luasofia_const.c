/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "utils/luasofia_const.h"

void luasofia_const_register_constants(lua_State *L, const luasofia_reg_const_t *consts)
{
    if (!consts) return;

    for (; consts->name; consts++) {
        lua_pushstring(L, consts->name);
        lua_pushnumber(L, consts->value);
        lua_rawset(L,-3);
    }
}

