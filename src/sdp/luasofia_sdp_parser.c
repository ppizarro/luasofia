#include <string.h>
#include <sofia-sip/sdp.h>
#include <sofia-sip/su_alloc.h>
#include "luasofia_sdp_parser.h"

#define SDP_PARSER_MTABLE "luasofia_sdp_parser_t"

typedef struct luasofia_sdp_parser_s {
    su_home_t *home;
    sdp_parser_t* parser;
} luasofia_sdp_parser_t; 


int luasofia_sdp_parser_parse(lua_State *L)
{
    su_home_t *home = su_home_create();
    luasofia_sdp_parser_t* l_parser = NULL;   
    /* get and check first argument (should be a string) */
    const char* msg = luaL_checkstring (L, 1);
    issize_t size   = (issize_t) strlen(msg);
    /* get and check second argument (should be a integer) */
    int flags = (int) luaL_checkinteger(L, 2);
    sdp_parser_t* parser = sdp_parse(home, msg, size, flags);
    
    lua_pop(L, 2);
    if(!parser)
        return 0;
    
    l_parser = (luasofia_sdp_parser_t*) lua_newuserdata(L, sizeof(luasofia_sdp_parser_t));
    l_parser->home = home;    
    l_parser->parser = parser;

    /* set its metatable */
    luaL_getmetatable(L, SDP_PARSER_MTABLE);
    lua_setmetatable(L, -2);   
        
    return 1;
}

static int luasofia_sdp_parse_get_session(lua_State *L)
{
return 0;
}

static int luasofia_sdp_parse_print(lua_State *L)
{
return 0;
}

static int luasofia_sdp_parse_destroy(lua_State *L)
{
return 0;
}

static const luaL_Reg sdp_parser_meths[] = {
    {"get_sdp_session", luasofia_sdp_parse_get_session},
    {"__tostring",      luasofia_sdp_parse_print },
    {"__gc",            luasofia_sdp_parse_destroy },
    {NULL, NULL}
};

int luasofia_sdp_parser_register_meta(lua_State *L)
{
    luaL_newmetatable(L, SDP_PARSER_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, sdp_parser_meths);
    lua_pop(L, 1);

    return 0;    
}
