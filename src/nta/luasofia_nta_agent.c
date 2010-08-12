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
#include "utils/luasofia_userdata_table.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_log.h"
#include "su/luasofia_su_root.h"

#define NTA_AGENT_MTABLE "luasofia_nta_agent_t"

typedef struct luasofia_nta_agent_s {
    nta_agent_t * agent;
    int callback_ref;
    lua_State *L;
} luasofia_nta_agent_t;

static int luasofia_nta_agent_destroy(lua_State* L)
{
    /* get and check first argument (should be a luasofia_nua_handle_t) */
    luasofia_nta_agent_t *agent = (luasofia_nta_agent_t*)luaL_checkudata(L, -1, NTA_AGENT_MTABLE);

    if (agent->agent) {
        /* remove userdata_table[nta_agent_lightudata] = nta_agent_fulludata */
        luasofia_userdata_table_remove(L, agent->agent);
        nta_agent_destroy(agent->agent); 	
        agent->agent = NULL;

        /* unref the lua callback function */
        luaL_unref(L, LUA_REGISTRYINDEX, agent->callback_ref);
    }

    return 0;
}

static const luaL_Reg nta_agent_meths[] = {
    {"__gc", luasofia_nta_agent_destroy },
    {NULL, NULL}
};

static int nta_agent_message_callback(nta_agent_magic_t *context,
                               nta_agent_t *agent,
                               msg_t *msg,
                               sip_t *sip)
{
    int error;
    luasofia_nta_agent_t* u_nta_agent = (luasofia_nta_agent_t*) context;
    lua_State *L = u_nta_agent->L;

    SU_DEBUG_9(("nta_agent_message_callback: context[%p] agent[%p] msg[%p] sip[%p]\n",
                context, agent, msg, sip));

    /* put nta_agent userdatum at stack and check if it is ok. */
    luasofia_userdata_table_get(L, agent);
    luaL_checkudata(L, -1, NTA_AGENT_MTABLE);

    /* put callback function at stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, u_nta_agent->callback_ref);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        SU_DEBUG_1(("nta_agent_message_callback: callback function not found!\n"));
        return -1; //error, lets not return 0 (should always return 0).
    }

    // Lets pass the nta_agent userdata as the first parameter of the callback.
    lua_pushvalue(L, -2);
    lua_pushlightuserdata(L, msg);
    lua_pushlightuserdata(L, sip);

    SU_DEBUG_9(("nta_agent_message_callback: calling lua callback\n"));
    if ((error = lua_pcall(L, 3, 0, 0)) != 0) {
        if (error == LUA_ERRMEM)
            SU_DEBUG_0(("nta_agent_message_callback: memory allocation error! error[%s]\n", lua_tostring(L, -1)));
        else
            SU_DEBUG_1(("nta_agent_message_callback: error on calling callback! error[%s]\n", lua_tostring(L, -1)));
        lua_pop(L, 1);
    }

    lua_pop(L, 1);
    return 0;
}

int luasofia_nta_agent_create(lua_State * L)
{
    luasofia_su_root_t *lroot = NULL;
    url_string_t * contact = NULL;
    luasofia_nta_agent_t* u_nta_agent = NULL;
    su_home_t *home = su_home_create();
    tagi_t *tags = NULL;

    /* get and check first argument (should be a root_t) */
    lroot = (luasofia_su_root_t*)luaL_checkudata(L, -4, SU_ROOT_MTABLE);

    if(lua_isuserdata (L, -3)) {
        //Since there is no metatable for url_t or url_string_t we cant perform a checkudata here.
        contact = (url_string_t *) lua_touserdata (L, -3);
    } else {
        contact = URL_STRING_MAKE(luaL_checkstring (L, -3));
    }

    /* check the callback function */
    if(!lua_isfunction(L, -2))
        luaL_error(L, "nta_agent_create failed!, expected a callback function !");

    /* check if there is tags */
    tags = luasofia_tags_table_to_taglist(L, -1, home);

    u_nta_agent           = (luasofia_nta_agent_t *) lua_newuserdata(L, sizeof(luasofia_nta_agent_t));
    u_nta_agent->L        = L;
    u_nta_agent->agent    = nta_agent_create (lroot->root,
                                              (url_string_t const *)contact,
                                              nta_agent_message_callback,
                                              (nta_agent_magic_t *)u_nta_agent,
                                              TAG_NEXT(tags));

    // lets hold the ref to the lua callback function.
    lua_pushvalue(L, -3);
    u_nta_agent->callback_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    if (!u_nta_agent->agent)
        luaL_error(L, "nta_agent_create failed!");

    /* set its metatable */
    luaL_getmetatable(L, NTA_AGENT_MTABLE);
    lua_setmetatable(L, -2);

    /* store nta_agent at luasofia userdata table 
       userdata_table[nta_agent_lightudata] = nta_agent_fulludata */
    luasofia_userdata_table_set(L, u_nta_agent->agent);

    su_home_unref(home);
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

