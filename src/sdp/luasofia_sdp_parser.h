/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_PARSER_H__
#define __LUASOFIA_SDP_PARSER_H__
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

int luasofia_sdp_parser_parse(lua_State* L);

int luasofia_sdp_parser_register_meta(lua_State *L);

#endif /* __LUASOFIA_SDP_PARSER_H__ */
