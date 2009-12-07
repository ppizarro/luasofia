/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_TIMER_H__
#define __LUASOFIA_SU_TIMER_H__

#include <sofia-sip/su_wait.h>

typedef struct luasofia_su_timer_s {
    su_timer_t *timer;
    lua_State *L;
} luasofia_su_timer_t;

#define SU_TIMER_MTABLE "su_timer_t"

int luasofia_su_timer_register_meta(lua_State *L);

int luasofia_su_timer_create(lua_State *L);

#endif //__LUASOFIA_SU_TIMER_H_

