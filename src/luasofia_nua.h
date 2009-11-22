/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_NUA_H__
#define __LUASOFIA_NUA_H__

#include <sofia-sip/nua.h>

typedef struct lua_nua_handle_s {
    nua_handle_t *nh;
    lua_State *L;
} lua_nua_handle_t;

#define NUA_HANDLE_MTABLE "lua_nua_handle_t"

typedef struct lua_nua_s {
    nua_t *nua;
    lua_State *L;
} lua_nua_t;

#define NUA_MTABLE "lua_nua_t"

int luaopen_nua(lua_State *L);

#endif //__LUASOFIA_NUA_H__

