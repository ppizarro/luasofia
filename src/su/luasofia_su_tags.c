/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <sofia-sip/su_tag_io.h>
#include <sofia-sip/su_tag_class.h>

#include "luasofia_su_tags.h"
#include "luasofia_tags.h"

#define LUASOFIA_TAGS_META "luasofia_tags"

int luasofia_su_tags_get_proxy(lua_State *L)
{
    void **ust = NULL;
    void *p = lua_touserdata(L, -1);
    luaL_argcheck(L, p != NULL, -1, "lightuserdata expected");

    /* create a userdata struct */
    ust = (void**)lua_newuserdata(L, sizeof(void*));
    *ust = p;

    /* set the proxy_metatable as the metatable for the userdata */
    luaL_getmetatable(L, LUASOFIA_TAGS_META);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_tags_index(lua_State *L)
{
    tag_type_t t_tag = NULL;
    tagi_t *tags = NULL;

    /* stack has userdata, index */
    void** ust = luaL_checkudata(L, 1, LUASOFIA_TAGS_META);
    tags = *ust;

    if(!tags)
        luaL_error(L, "Tag list is NULL!");

    t_tag = luasofia_tags_find(L);

    /* find the tag in the tag list */
    while(tags->t_tag) {
        if (tags->t_tag == t_tag)
            break;
        tags++;
    }

    if(!tags->t_tag) {
        /* TAG not found */
        lua_pushnil(L);
        return 1;
    }

    if(!t_tag->tt_class) {
        /* TAG has no class tag */
        lua_pushnil(L);
        return 1;
    }

    if(t_tag->tt_class == int_tag_class)
        lua_pushinteger(L, (int)tags->t_value);
    else if(t_tag->tt_class == uint_tag_class)
        lua_pushnumber(L, (lua_Number)tags->t_value);
    else if(t_tag->tt_class == usize_tag_class)
        lua_pushnumber(L, (lua_Number)tags->t_value);
    else if(t_tag->tt_class == size_tag_class)
        lua_pushnumber(L, (lua_Number)tags->t_value);
    else if(t_tag->tt_class == bool_tag_class)
        lua_pushboolean(L, (int)tags->t_value);
    else if(t_tag->tt_class == ptr_tag_class)
        lua_pushlightuserdata(L, (void*)tags->t_value);
    else if(t_tag->tt_class == socket_tag_class)
        lua_pushlightuserdata(L, (void*)tags->t_value);
    else if(t_tag->tt_class == cstr_tag_class)
        lua_pushfstring(L, "%s", (char*)tags->t_value);
    else if(t_tag->tt_class == str_tag_class)
        lua_pushfstring(L, "%s", (char*)tags->t_value);
    else
        lua_pushlightuserdata(L, (void*)tags->t_value);
    return 1;
}

int luasofia_su_tags_register_meta(lua_State *L)
{
    luaL_newmetatable(L, LUASOFIA_TAGS_META);

    lua_pushliteral(L, "__index");
    lua_pushcfunction(L, luasofia_su_tags_index);
    lua_settable(L, -3);

    lua_pop(L, 1);
    return 0;
}

