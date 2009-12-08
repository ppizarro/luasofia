/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "luasofia_tags.h"
#include "luasofia_utils.h"
#include "luasofia_proxy.h"

#include <sofia-sip/sdp.h>
#include <sofia-sip/sdp_tag.h>

static const luaL_Reg sdp_lib[] = {
    {NULL, NULL}
};

static const luasofia_tag_reg_t sdp_tags[] = {
    { NULL, NULL}
};

static const luasofia_reg_const_t sdp_constants[] = {
    {NULL, 0 }
};

int luaopen_luasofia_sdp(lua_State *L)
{
    luaopen_luasofia(L);

    /* luasofia[sdp] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "sdp");
    luaL_register(L, NULL, sdp_lib);

    luasofia_tags_register(L, sdp_tags);

    //luasofia_proxy_register_info_table(L, SIP_TABLE_NAME, sdp_info);    
    
    luasofia_register_constants(L, sdp_constants);

    return 1;
}

