/* vim: set ts=8 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "luasofia_weak_table.h"
#include "luasofia_su_root.h"
//#include "luasofia_su_home.h"
#include "luasofia_su_timer.h"
#include "luasofia_su_task.h"

#include <sofia-sip/su.h>

static int luasofia_su_init(lua_State *L)
{
    su_init();
    return 0;
}

static int luasofia_su_deinit(lua_State *L)
{
    su_deinit();
    return 0;
}

static const luaL_Reg su_lib[] = {
    {"init",         luasofia_su_init },
    {"deinit",       luasofia_su_deinit },
    {"root_create",  luasofia_su_root_create },
    //{"home_new",     luasofia_su_home_new },
    {"timer_create", luasofia_su_timer_create },
    {"task_init",    luasofia_su_task_init },
    {NULL, NULL}
};

int luaopen_luasofia_su(lua_State *L)
{
    luasofia_su_root_register_meta(L);
    //luasofia_su_home_register_meta(L);
    luasofia_su_timer_register_meta(L);
    luasofia_su_task_register_meta(L);

    luaopen_luasofia(L);

    /* luasofia[su] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "su");
    luaL_register(L, NULL, su_lib);
    return 1;
}

