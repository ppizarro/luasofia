/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <sofia-sip/su_tag_io.h>
#include <sofia-sip/su_alloc.h>
#include <sofia-sip/nua_tag.h>

#include <string.h>

#include "luasofia_tags.h"

#define TAGS_LIST_SIZE 32

static int tag_table_ref = LUA_REFNIL;

void luasofia_tags_create(lua_State *L)
{
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
        luaL_error(L, "Failed to get tag table!");

    for (; tags->tag_name; tags++) {
        lua_pushstring(L, tags->tag_name);
        lua_pushlightuserdata(L, (void*)tags->t_tag);
        lua_rawset(L,-3);
    }
    lua_pop(L, 1);
}

tagi_t* luasofia_tags_table_to_taglist(lua_State *L, int index, su_home_t *home)
{
    int i = 0;
    int maxtags = TAGS_LIST_SIZE;
    tagi_t* tags = su_zalloc(home, sizeof(tagi_t) * maxtags);

    if(!lua_istable(L, index))
        return tags;

    /* put the tag table at the stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, tag_table_ref);
    if (lua_isnil(L, -1))
        luaL_error(L, "Failed to get tag table!");

    if (index < 0)
        index--;

    /* primeira chave */
    lua_pushnil(L);
    while(lua_next(L, index) != 0) {
        /* usa 'key' (no índice -2) e 'value' (no índice -1) */
        tag_type_t t_tag = NULL;
        tag_value_t return_value;
        char const *s = lua_tostring(L, -1);

        // Procura chave na tabela de tags
        // e retorna o tag_type_t equivalente
        lua_pushvalue(L, -2);
        lua_rawget(L, -4);
        t_tag = lua_touserdata(L, -1);
        lua_pop(L, 1);

        if(t_scan(t_tag, home, s, &return_value) < 0) {
            /* remove 'value'; guarda 'key'  para a próxima iteração */
            lua_pop(L, 1);
            continue;
        }

        tags[i].t_tag = t_tag;
        tags[i++].t_value = return_value;

        if(i == maxtags - 1) {
            maxtags *= 2;
            tags = su_realloc(home, tags, sizeof(tagi_t) * maxtags);
        }

        /* remove 'value'; guarda 'key'  para a próxima iteração */
        lua_pop(L, 1);
    }
    /* remove tag table from stack */
    lua_pop(L, 1);

    tags[i].t_tag = NULL;
    tags[i].t_value = 0;
    return tags;
}

void luasofia_tags_taglist_to_table(lua_State *L, tagi_t tags[])
{
    char buffer[4096];
    size_t size = sizeof(buffer);
    int i = 0;
    tagi_t* tag = NULL;
 
    if(!tags) return;
 
    lua_newtable(L);
    while(tags[i].t_tag) {
        tag = &tags[i];
        if (tag->t_tag && tag->t_tag->tt_name && tag->t_tag->tt_class && tag->t_tag->tt_class->tc_snprintf) {
            lua_pushfstring(L, "%s_%s", tag->t_tag->tt_ns, tag->t_tag->tt_name);
            //lua_pushlightuserdata(L, (void*)(tags[i++].t_tag));
            tag->t_tag->tt_class->tc_snprintf(tag, buffer, size);
            lua_pushstring(L, buffer);
            lua_rawset(L,-3);
        }
        i++;
    }
}

