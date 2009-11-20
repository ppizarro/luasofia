/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_HOME_H__
#define __LUASOFIA_SU_HOME_H__

#include <sofia-sip/su_alloc.h>

#define SU_HOME_MTABLE "su_home_t"

typedef struct su_home_userdata_s {
    su_home_t *home;
    lua_State *L;
} su_home_userdata;

int luaopen_su_home(lua_State *L);

#endif //__LUASOFIA_SU_HOME_H_

