/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_tags.h"

void luasofia_tags_register(lua_State *L, const luasofia_tag_reg_t *tags)
{
    if (!tags)
        return;

    for (; tags->tag_name; tags++) {
        lua_pushstring(L, tags->tag_name);
        lua_pushlightuserdata(L, (void*)tags->tag);
        lua_rawset(L,-3);
    }
}

