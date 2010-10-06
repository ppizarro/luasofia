/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 *
 * This file is part of Luasofia.
 *
 * Luasofia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Luasofia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <sofia-sip/su_tag_io.h>
#include <sofia-sip/su_alloc.h>
#include <sofia-sip/nua_tag.h>

#include <string.h>

#include "utils/luasofia_tags.h"
#include "utils/luasofia_log.h"

#define TAGS_LIST_SIZE 32

static int tag_table_ref = LUA_REFNIL;

void luasofia_tags_create(lua_State *L)
{
    if(tag_table_ref != LUA_REFNIL)
        return;

    /* create userdata table */
    lua_newtable(L);
   
    /* now lets store the tag table at the LUA_REGISTRYINDEX, */
    tag_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

void luasofia_tags_register_tags(lua_State *L, const luasofia_tag_reg_t *tags)
{
    if (!tags)
        return;

    /* put the tag table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, tag_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "luasofia_tags_register_tags: Failed to get tag table !, "
                      "Probably luasofia_tags_create has not been called yet or "
                      "something went terribly wrong");

    for (; tags->tag_name; tags++) {
        lua_pushstring(L, tags->tag_name);
        lua_pushlightuserdata(L, (void*)tags->t_tag);
        lua_rawset(L,-3);
    }
    lua_pop(L, 1);
}

int luasofia_tags_taglist_to_table(lua_State *L, tagi_t* tags)
{
    int i = 0;
    tag_type_t t_tag = NULL;
    tag_value_t value;

    t_tag = tags[i].t_tag;
    lua_createtable(L, TAGS_LIST_SIZE, 0);
    while(t_tag != NULL) {
        /* FIXME: name and value */
        value = tags[i++].t_value;
        lua_pushstring(L, t_tag->tt_name);
        lua_pushlightuserdata(L, (void*)value);
        lua_rawset(L,-3);
        t_tag = tags[i].t_tag;
    }
    return 1;
}

tagi_t* luasofia_tags_table_to_taglist(lua_State *L, int index, su_home_t *home)
{
    int i = 0;
    int maxtags = TAGS_LIST_SIZE;
    tagi_t* tags = su_zalloc(home, sizeof(tagi_t) * maxtags);

    if(!lua_istable(L, index)) {
        tags[0].t_tag = NULL;
        tags[0].t_value = 0;
        return tags;
    }

    /* put the tag table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, tag_table_ref);
    if (lua_isnil(L, -1)) {
        su_free(home, tags);
        luaL_error(L, "Failed to get tag table!");
    }

    if (index < 0)
        index--;

    /* first key */
    lua_pushnil(L);
    while(lua_next(L, index) != 0) {
        /* 'key' at index -2 and 'value' at index -1 */
        tag_type_t t_tag = NULL;
        tag_value_t return_value;
        char const *s = NULL;

        /* if 'value' is nil not use this tag */
        if(lua_isnil(L, -1)) {
            /* remove 'value' and 'key' is used on the next iteration */
            lua_pop(L, 1);
            continue;
        }
        s = lua_tostring(L, -1);

        /* lookup key in the tag table and push tag_type_t */
        lua_pushvalue(L, -2);
        lua_rawget(L, -4);
        t_tag = lua_touserdata(L, -1);
        lua_pop(L, 1);

        if(t_scan(t_tag, home, s, &return_value) == -1) {
            su_free(home, tags);
            luaL_error(L, "Tag '%s' doesn't exist!", lua_tostring(L, -2));
        }

        tags[i].t_tag = t_tag;
        tags[i++].t_value = return_value;

        if(i == maxtags - 1) {
            maxtags *= 2;
            tags = su_realloc(home, tags, sizeof(tagi_t) * maxtags);
        }

        /* remove 'value' and 'key' is used on the next iteration */
        lua_pop(L, 1);
    }
    /* remove tag table from stack */
    lua_pop(L, 1);

    tags[i].t_tag = NULL;
    tags[i].t_value = 0;
    return tags;
}

tag_type_t luasofia_tags_find(lua_State *L)
{
    tag_type_t t_tag = NULL;

    /* put the tag table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, tag_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get tag table!");

    lua_pushvalue(L, -2);

    /* lookup key on the tag table */
    lua_rawget(L, -2);

    if (!lua_islightuserdata(L, -1))
        luaL_error(L, "Failed to get tag object '%s'", lua_tostring(L, -3));

    t_tag = (tag_type_t)lua_touserdata(L, -1);
    lua_pop(L, 2);
    return t_tag;
}

