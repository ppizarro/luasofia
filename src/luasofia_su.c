/* vim: set ts=8 et sw=4 sta ai cin: */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_weak_table.h"
#include "luasofia_su_root.h"
//#include "luasofia_su_home.h"
#include "luasofia_su_timer.h"
#include "luasofia_su_task.h"

#include <sofia-sip/su.h>

static int lua_su_init(lua_State *L)
{
    su_init();
    return 0;
}

static int lua_su_deinit(lua_State *L)
{
    su_deinit();
    return 0;
}

static const luaL_Reg su_lib[] = {
    {"init",         lua_su_init },
    {"deinit",       lua_su_deinit },
    {"root_create",  lua_su_root_create },
    //{"home_new",     lua_su_home_new },
    {"timer_create", lua_su_timer_create },
    {"task_init",    lua_su_task_init },
    {NULL, NULL}
};

int luaopen_luasofia_su(lua_State *L)
{
    luasofia_register_root_meta(L);
    //luasofia_register_home_meta(L);
    luasofia_register_timer_meta(L);
    luasofia_register_task_meta(L);

    lua_getglobal(L, "luasofia");
    if(lua_isnil(L, -1)) {
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, "luasofia");
    }
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "su");
    luaL_register(L, NULL, su_lib);
    return 1;
}

