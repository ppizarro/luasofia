/*
 * Copyright (C) 2009 Digitro Corporation <www.digitro.com.br>
 *
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

#define NUA_HANDLE_MTABLE "luasofia_nua_handle_t"

typedef struct luasofia_nua_handle_s {
    nua_handle_t *nh;
    lua_State *L;
} luasofia_nua_handle_t;


static int luasofia_nua_handle_invite(lua_State *L)
{
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);

    tags = luasofia_tags_table_to_taglist(L, 2, home);
    //tl_print(stdout, "lua_nua_invite:\n", tags);
    nua_invite(lnh->nh, TAG_NEXT(tags));
    su_home_unref(home);
    return 0;
}

static int luasofia_nua_handle_ref(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    nua_handle_ref(lnh->nh);
    return 0;
}

static int luasofia_nua_handle_unref(lua_State *L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nua_handle_t *lnh = (luasofia_nua_handle_t*)luaL_checkudata(L, 1, NUA_HANDLE_MTABLE);
    nua_handle_unref(lnh->nh);
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

static const luaL_Reg nua_handle_meths[] = {
    {"ref",    luasofia_nua_handle_ref },
    {"unref",  luasofia_nua_handle_unref },
    {"invite", luasofia_nua_handle_invite },
    {"__gc",   luasofia_nua_handle_destroy },
    {NULL, NULL}
};

int luasofia_nua_handle_create(lua_State *L, nua_t *nua)
{
    luasofia_nua_handle_t *lnh = NULL;
    nua_handle_t *nh = NULL;
    tagi_t *tags = NULL;
    su_home_t *home = su_home_create();

    tags = luasofia_tags_table_to_taglist(L, 2, home);

    /* create a nua_handle object */
    lnh = (luasofia_nua_handle_t*) lua_newuserdata(L, sizeof(luasofia_nua_handle_t));

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

