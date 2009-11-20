/* vim: set ts=8 et sw=4 sta ai cin: */
#include <sofia-sip/su_wait.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_su_root.h"
#include "luasofia_su_home.h"

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

static int lua_su_root_create(lua_State *L)
{
    su_root_t *root = NULL;
    su_root_userdata *userdata = NULL;
    int argc = lua_gettop(L); 

    if (argc > 0)
        luaL_checktype(L, 1, LUA_TTABLE);

    /* create the su_root */
    root = su_root_create(NULL);
    if (!root)
        luaL_error(L, "su_root_create failed!");

    su_root_threading(root, 0);

    /* create a su_root object */
    userdata = (su_root_userdata*) lua_newuserdata(L, sizeof(su_root_userdata));
    /* set Lua state */
    userdata->L = L;
    userdata->root = root;

    /* set its metatable */
    luaL_getmetatable(L, SU_ROOT_MTABLE);
    lua_setmetatable(L, -2);

    // FIXME guardamos a table no registry e setamos o magic com o ref ou
    // guardamos a table no environment do userdata e setamos o magic como NULL?
    if (argc > 0) {
        /* set callback table as environment for udata */
        lua_pushvalue(L, 1);
        lua_setfenv(L, -2);
    }

    return 1;
}

static int lua_su_home_new(lua_State *L)
{
    su_home_t *home = NULL;
    su_home_userdata *userdata = NULL;
    int size = luaL_optint(L, 1, sizeof(su_home_t));

    /* create the su_home */
    home = su_home_new(size);
    if (!home)
        luaL_error(L, "su_home_new failed!");

    /* create a su_home object */
    userdata = (su_home_userdata*) lua_newuserdata(L, sizeof(su_home_userdata));
    /* set Lua state */
    userdata->L = L;
    userdata->home = home;

    /* set its metatable */
    luaL_getmetatable(L, SU_HOME_MTABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static const luaL_Reg su_lib[] = {
    {"init", lua_su_init },
    {"deinit", lua_su_deinit },
    {"root_create", lua_su_root_create },
    {"home_new", lua_su_home_new },
    {NULL, NULL}
};

int luaopen_su(lua_State *L)
{
    luaopen_su_root(L);
    luaopen_su_home(L);

    luaL_register(L, "su", su_lib);

    return 1;
}

