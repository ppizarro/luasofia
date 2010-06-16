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

#include <sofia-sip/su_glib.h>

#include "su_glib/luasofia_su_glib_root.h"
#include "su/luasofia_su_root.h"

int luasofia_su_glib_root_create(lua_State *L)
{
    su_root_t *root = NULL;
    luasofia_su_root_t *lroot = NULL;

    /* create the su_root */
    root = su_glib_root_create(NULL);
    if (!root)
        luaL_error(L, "su_root_create failed!");

    su_root_threading(root, 0);

    /* create a su_root object */
    lroot = (luasofia_su_root_t*) lua_newuserdata(L, sizeof(luasofia_su_root_t));
    /* set Lua state */
    lroot->L = L;
    lroot->root = root;

    /* set its metatable */
    luaL_getmetatable(L, SU_ROOT_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static int luasofia_su_glib_root_gsource(lua_State *L)
{
    luasofia_su_root_t *lroot = NULL;

    /* get and check first argument (should be a glib root) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, 1, SU_ROOT_MTABLE);

    if (!lroot->root) 
        luaL_error(L, "su_glib_root_gsource failed !, NULL su_root_t");

    lua_pushlightuserdata(L, su_glib_root_gsource(lroot->root));
    return 1;
}


static const luaL_Reg su_glib_root_meths[] = {
    {"gsource", luasofia_su_glib_root_gsource },
    {NULL, NULL}
};

int luasofia_su_glib_root_register_meta(lua_State *L)
{
    luaL_getmetatable(L, SU_ROOT_MTABLE);
    luaL_register(L, NULL, su_glib_root_meths);
    lua_pop(L, 1);
    return 0;
}

