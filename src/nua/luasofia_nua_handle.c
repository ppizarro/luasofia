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
#include "nua/luasofia_nua_handle.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_weak_table.h"

typedef struct luasofia_nua_handle_s {
    nua_handle_t *nh;
    lua_State *L;
} luasofia_nua_handle_t;

/*
  ############################## 
  NUA_HANDLE METHODS DEFINITIONS
  ##############################
*/

static int luasofia_nua_handle_invite(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);
        nua_invite(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_destroy(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);

    if (lnh->nh) {
        /* remove lnh of the luasofia weak table */
        luasofia_weak_table_remove(L, lnh->nh);
        nua_handle_destroy(lnh->nh);
        lnh->nh = NULL;
    }
    return 0;
}

static int luasofia_nua_handle_register(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_register(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_unregister(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_unregister(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_ack(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_ack(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_prack(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_prack(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_options(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_options(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_publish(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_publish(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_unpublish(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_unpublish(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_message(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_message(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_chat(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_chat(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_info(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_info(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_subscribe(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_subscribe(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_unsubscribe(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_unsubscribe(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_notify(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_notify(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_notifier(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_notifier(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_terminate(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_terminate(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_refer(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_refer(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_update(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_update(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_bye(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_bye(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_cancel(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_cancel(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_authenticate(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_authenticate(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_authorize(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_authorize(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_method(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

        nua_method(lnh->nh, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}

static int luasofia_nua_handle_respond(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*) luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    if (lnh->nh) {
        su_home_t *home = su_home_create();
        /* get and check second argument (should be a int) */
        int status = luaL_checkinteger(L, 2);
        /* get and check third argument (should be a string) */
        char const* phrase = luaL_checkstring (L, 3);
        /* get and check fourth argument (should be a tag table) */
        tagi_t *tags = luasofia_tags_table_to_taglist(L, 4, home);

        nua_respond(lnh->nh, status, phrase, TAG_NEXT(tags));
        su_home_unref(home);
    }
    return 0;
}


/* 
   ################################
   NUA_HANDLE INITIALIZE - REGISTER
   ################################
*/

static const luaL_Reg nua_handle_meths[] = {
    {"invite",       luasofia_nua_handle_invite },
    {"register",     luasofia_nua_handle_register },
    {"unregister",   luasofia_nua_handle_unregister },
    {"ack",          luasofia_nua_handle_ack },
    {"prack",        luasofia_nua_handle_prack },
    {"options",      luasofia_nua_handle_options },
    {"publish",      luasofia_nua_handle_publish },
    {"unpublish",    luasofia_nua_handle_unpublish },
    {"message",      luasofia_nua_handle_message },
    {"chat",         luasofia_nua_handle_chat },
    {"info",         luasofia_nua_handle_info },
    {"subscribe",    luasofia_nua_handle_subscribe },
    {"unsubscribe",  luasofia_nua_handle_unsubscribe },
    {"notify",       luasofia_nua_handle_notify },
    {"notifier",     luasofia_nua_handle_notifier },
    {"terminate",    luasofia_nua_handle_terminate },
    {"refer",        luasofia_nua_handle_refer },
    {"update",       luasofia_nua_handle_update },
    {"bye",          luasofia_nua_handle_bye },
    {"cancel",       luasofia_nua_handle_cancel },
    {"authenticate", luasofia_nua_handle_authenticate},
    {"authorize",    luasofia_nua_handle_authorize },
    {"method",       luasofia_nua_handle_method },
    {"respond",      luasofia_nua_handle_respond },
    {"destroy",      luasofia_nua_handle_destroy },
    {"__gc",         luasofia_nua_handle_destroy },
    {NULL, NULL}
};

int luasofia_nua_handle_create_userdata(lua_State *L, nua_handle_t *nh)
{
    luasofia_nua_handle_t *lnh = NULL;

    if (!nh)
        luaL_error(L, "nua_handle is nil!");

    /* create a nua_handle object */
    lnh = (luasofia_nua_handle_t*)lua_newuserdata(L, sizeof(luasofia_nua_handle_t));

    /* set Lua state */
    lnh->L = L;
    lnh->nh = nh;

    /* set its metatable */
    luaL_getmetatable(L, NUA_HANDLE_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua handle at luasofia weak table */
    luasofia_weak_table_set(L, nh);
    return 1;
}

int luasofia_nua_handle_create(lua_State *L, nua_t *nua)
{
    luasofia_nua_handle_t *lnh = NULL;
    nua_handle_t *nh = NULL;
    su_home_t *home = su_home_create();
    tagi_t *tags = luasofia_tags_table_to_taglist(L, 2, home);

    /* create a nua_handle object */
    lnh = (luasofia_nua_handle_t*)lua_newuserdata(L, sizeof(luasofia_nua_handle_t));

    /* create the nua_handle_t */
    nh = nua_handle(nua, lnh, TAG_NEXT(tags));
    if (!nh)
        luaL_error(L, "nua_handle failed!");

    /* set Lua state */
    lnh->L = L;
    lnh->nh = nh;

    /* set its metatable */
    luaL_getmetatable(L, NUA_HANDLE_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua handle at luasofia weak table */
    luasofia_weak_table_set(L, nh);

    su_home_unref(home);
    return 1;
}


int luasofia_nua_handle_register_meta(lua_State* L)
{
    luaL_newmetatable(L, NUA_HANDLE_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_handle_meths);
    lua_pop(L, 1);

    return 0;
}

