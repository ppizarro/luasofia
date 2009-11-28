/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_H__
#define __LUASOFIA_SIP_H__

typedef struct lua_sip_s lua_sip_t;

#define SIP_MTABLE "lua_sip_t"

int luaopen_sip(lua_State *L);

#endif //__LUASOFIA_SIP_H__

