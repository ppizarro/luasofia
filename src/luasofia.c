/* vim: set ts=4 et sw=4 sta ai cin: */
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

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "utils/luasofia_weak_table.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_proxy.h"

static const struct luaL_reg core_lib[] = {
  {NULL, NULL},
};

int luaopen_luasofia(lua_State *L)
{ 
    lua_getglobal(L, "luasofia");
    if(!lua_isnil(L, -1))
        return 1;

    /* create luasofia weak table at REGISTRYINDEX */
    luasofia_weak_table_create(L);

    /* create luasofia tag table at REGISTRYINDEX */
    luasofia_tags_create(L);

    luasofia_proxy_init(L);

    luaL_register(L, "luasofia", core_lib);
    return 1;
}

