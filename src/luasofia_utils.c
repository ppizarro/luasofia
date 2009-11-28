/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_utils.h"

void luasofia_register_constants(lua_State *L, const luasofia_reg_const_t *consts)
{
    if (!consts) return;

    for (; consts->name; consts++) {
        lua_pushstring(L, consts->name);
        lua_pushnumber(L, consts->value);
        lua_rawset(L,-3);
    }
}

void stack_dump(lua_State *L)
{
    int i = 1;
    int top = lua_gettop(L);
    printf("stack(%d): ", top); 
    for (; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:
            printf("'%s'", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        default:
            printf("%s", lua_typename(L, t));
        }
        printf("  ");
    }
    printf("\n");
}

