/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_ROOT_H__
#define __LUASOFIA_SU_ROOT_H__

#include <sofia-sip/su_wait.h>

#define SU_ROOT_MTABLE "su_root_t"

typedef struct su_root_userdata_s {
    su_root_t *root;
    lua_State *L;
} su_root_userdata;

int luaopen_su_root(lua_State *L);

#endif //__LUASOFIA_SU_ROOT_H_

