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

#include "luasofia.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"

#include <sofia-sip/msg_header.h>

static int luasofia_msg_params_find(lua_State *L)
{
    /* get and check first argument (should be a msg_param_t const **) */
    msg_param_t const *params = (msg_param_t const *) lua_touserdata (L, -1);
    /* get and check second argument (should be a string) */
    char const *name = lua_tostring(L, -2);
    msg_param_t ret = 0;

    if (!params) {
        luaL_error(L, "luasofia_msg_params_find failed to get msg_param_t!!");
    }

    if (!name) {
        luaL_error(L, "luasofia_msg_params_find failed to get name !!");
    }

    ret = msg_params_find(params, name);
    if (ret) {
        lua_pushstring (L, (const char *) ret);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static const luaL_Reg msg_lib[] = {
    {"params_find" , luasofia_msg_params_find},
    {NULL, NULL}
};

static const luasofia_tag_reg_t msg_tags[] = {
    { NULL, NULL}
};

static const luasofia_reg_const_t msg_constants[] = {
    {NULL, 0 }
};

int luaopen_sofia_msg(lua_State *L)
{
    luaopen_sofia(L);

    /* sofia[msg] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "msg");
    luaL_register(L, NULL, msg_lib);

    luasofia_tags_register_tags(L, msg_tags);
    luasofia_const_register_constants(L, msg_constants);
    return 1;
}

