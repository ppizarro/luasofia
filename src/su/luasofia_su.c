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
#include "utils/luasofia_weak_table.h"
#include "su/luasofia_su_root.h"
#include "su/luasofia_su_timer.h"
#include "su/luasofia_su_task.h"
#include "su/luasofia_su_tags.h"

#include <sofia-sip/su.h>

static int luasofia_su_init(lua_State *L)
{
    lua_pushinteger(L, su_init());
    return 1;
}

static int luasofia_su_deinit(lua_State *L)
{
    su_deinit();
    return 0;
}

static const luaL_Reg su_lib[] = {
    {"init",         luasofia_su_init },
    {"deinit",       luasofia_su_deinit },
    {"root_create",  luasofia_su_root_create },
    {"timer_create", luasofia_su_timer_create },
    {"task_create",    luasofia_su_task_create },
    {"get_proxy_tags", luasofia_su_tags_get_proxy },
    {NULL, NULL}
};

int luaopen_luasofia_su(lua_State *L)
{
    luaopen_luasofia(L);

    luasofia_su_root_register_meta(L);
    luasofia_su_timer_register_meta(L);
    luasofia_su_task_register_meta(L);
    luasofia_su_tags_register_meta(L);

    /* luasofia[su] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "su");
    luaL_register(L, NULL, su_lib);
    return 1;
}

