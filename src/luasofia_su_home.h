/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_HOME_H__
#define __LUASOFIA_SU_HOME_H__

#include <sofia-sip/su_alloc.h>

typedef struct lua_su_home_s {
    su_home_t *home;
    lua_State *L;
} lua_su_home_t;

#define SU_HOME_MTABLE "su_home_t"

int luaopen_su_home(lua_State *L);

int lua_su_home_new(lua_State *L);

#endif //__LUASOFIA_SU_HOME_H_

