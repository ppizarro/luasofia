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
#include "nta/luasofia_nta_agent.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_weak_table.h"

static const luaL_Reg nta_agent_meths[] = {
    //TODO Release the lua callback function reference {"__gc__", gc_func},
    {NULL, NULL}
};

int luasofia_nta_agent_register_meta(lua_State* L)
{
    luaL_newmetatable(L, NTA_AGENT_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nta_agent_meths);
    lua_pop(L, 1);

    return 0;
}

