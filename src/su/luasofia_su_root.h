/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_ROOT_H__
#define __LUASOFIA_SU_ROOT_H__

#include <sofia-sip/su_wait.h>

typedef struct luasofia_su_root_s {
    su_root_t *root;
    lua_State *L;
} luasofia_su_root_t;

#define SU_ROOT_MTABLE "su_root_t"

int luasofia_su_root_register_meta(lua_State *L);

int luasofia_su_root_create(lua_State *L);

#endif //__LUASOFIA_SU_ROOT_H_
