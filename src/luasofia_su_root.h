/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_ROOT_H__
#define __LUASOFIA_SU_ROOT_H__

#include <sofia-sip/su_wait.h>

typedef struct lua_su_root_s {
    su_root_t *root;
    lua_State *L;
} lua_su_root_t;

#define SU_ROOT_MTABLE "su_root_t"

int luaopen_su_root(lua_State *L);

int lua_su_root_create(lua_State *L);

#endif //__LUASOFIA_SU_ROOT_H_

