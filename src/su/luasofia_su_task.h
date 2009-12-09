/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SU_TASK_H__
#define __LUASOFIA_SU_TASK_H__

#include <sofia-sip/su_wait.h>

typedef struct luasofia_su_task_s {
    su_task_r task;
    _su_task_r ptask;
    lua_State *L;
} luasofia_su_task_t;

#define SU_TASK_MTABLE "su_task_t"

int luasofia_su_task_register_meta(lua_State *L);

int luasofia_su_task_init(lua_State *L);

int luasofia_su_task_create(lua_State *L, _su_task_r ptask);

#endif //__LUASOFIA_SU_TASK_H_

