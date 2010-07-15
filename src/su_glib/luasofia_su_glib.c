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

#include "luasofia.h"

#include "su_glib/luasofia_su_glib_root.h"

static int luasofia_su_glib_prefer_gsource(lua_State *L)
{
    su_glib_prefer_gsource ();
    return 0;
}

static const luaL_Reg luasofia_glib_lib[] = {
    {"root_create",    luasofia_su_glib_root_create },
    {"prefer_gsource", luasofia_su_glib_prefer_gsource },
    {NULL, NULL}
};

int luaopen_sofia_glib(lua_State *L)
{
    luaopen_sofia(L);

    luasofia_su_glib_root_register_meta(L);

    /* sofia[glib] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "glib");
    luaL_register(L, NULL, luasofia_glib_lib);
    return 1;
}

