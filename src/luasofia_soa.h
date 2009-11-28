/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SOA_H__
#define __LUASOFIA_SOA_H__

typedef struct lua_soa_session_s lua_soa_session_t;

#define SOA_SESSION_MTABLE "lua_soa_session_t"

int luaopen_soa(lua_State *L);

#endif //__LUASOFIA_SOA_H__

