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

typedef struct luasofia_nta_agent_s {
    nta_agent_t *agent;
    lua_State *L;
} luasofia_nta_agent_t;


static const luaL_Reg nta_agent_meths[] = {
    //{"TODO", func},
    {NULL, NULL}
};

int luasofia_nta_agent_create(lua_State *L, nta_agent_t *nta_agent)
{
    luasofia_nta_agent_t* agent = (luasofia_nta_agent_t *) lua_newuserdata(L, sizeof(luasofia_nta_agent_t));

    /* set Lua state */
    agent->L = L;
    agent->agent = nta_agent;

    /* set its metatable */
    luaL_getmetatable(L, NTA_AGENT_MTABLE);
    lua_setmetatable(L, -2);

    return 1;
}

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

