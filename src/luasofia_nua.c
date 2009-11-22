/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_weak_table.h"
#include "luasofia_su_root.h"
#include "luasofia_nua.h"

#include <sofia-sip/nua.h>

struct lua_nua_handle_s {
    nua_handle_t *nh;
    lua_State *L;
};

struct lua_nua_s {
    nua_t *nua;
    lua_State *L;
};

static int lua_nua_handle_bind(lua_State *L)
{
    return 0;
}

static int lua_nua_handle_ref(lua_State *L)
{
    return 0;
}

static int lua_nua_handle_unref(lua_State *L)
{
    return 0;
}

static int lua_nua_handle_destroy(lua_State *L)
{
    return 0;
}

static int lua_nua_handle_create(lua_State *L)
{
    return 0;
}

static int lua_nua_destroy(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_t) */
    lua_nua_t *lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    if (lnua->nua) {
        nua_destroy(lnua->nua);
        lnua->nua = NULL;
    }

    /* remove lnua of the luasofia weak table */
    luasofia_weak_table_remove(L, lnua->nua);
    return 0;
}

static int lua_nua_shutdown(lua_State *L)
{
    /* get and check first argument (should be a lua_nua_t) */
    lua_nua_t *lnua = (lua_nua_t*)luaL_checkudata(L, 1, NUA_MTABLE);

    nua_shutdown(lnua->nua);
    return 0;
}

/* NUA event callback */
static void nua_event_callback(nua_event_t event,
                               int status, char const *phrase,
                               nua_t *nua, nua_magic_t *magic,
                               nua_handle_t *nh, nua_hmagic_t *hmagic,
                               sip_t const *sip,
                               tagi_t tags[])
{
    lua_nua_t *lnua = (lua_nua_t*)magic;
    lua_State *L = lnua->L;

    // put userdataum at stack and check if it is ok.
    luasofia_weak_table_get(L, lnua->nua);
    luaL_checkudata(L, -1, NUA_MTABLE);

    /* put callback table at stack */
    lua_getfenv(L, -1);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        return;
    }

    /* get callback */
    lua_getfield(L, -1, "event_handler");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 3);
        return;
    }

    lua_pushvalue(L, 1);
    lua_pushinteger(L, event);
    lua_pushinteger(L, status);
    lua_pushstring(L, phrase);
    lua_call(L, 3, 0);
    lua_pop(L, 2);
}

static int lua_nua_create(lua_State *L)
{
    lua_su_root_t *lroot = NULL;
    lua_nua_t *lnua = NULL;
    nua_t *nua = NULL;

    /* get and check first argument (should be a root_t) */
    lroot = (lua_su_root_t*)luaL_checkudata(L, 1, SU_ROOT_MTABLE);

    /* check the callback table */
    luaL_checktype(L, 2, LUA_TTABLE);

    /* create a nua object */
    lnua = (lua_nua_t*) lua_newuserdata(L, sizeof(lua_nua_t));

    /* create the nua_t */
    nua = nua_create(lroot->root, nua_event_callback, lnua, TAG_NULL());
    if (!nua)
        luaL_error(L, "nua_create failed!");

    /* set Lua state */
    lnua->L = L;
    lnua->nua = nua;

    /* set its metatable */
    luaL_getmetatable(L, NUA_MTABLE);
    lua_setmetatable(L, -2);

    /* store nua at luasofia weak table */
    luasofia_weak_table_set(L, nua);

    /* set callback table as environment for udata */
    lua_pushvalue(L, 1);
    lua_setfenv(L, -2);

    return 1;
}

static const luaL_Reg nua_handle_meths[] = {
    {"ref",     lua_nua_handle_ref },
    {"unref",   lua_nua_handle_unref },
    {"bind",    lua_nua_handle_bind },
    {"__gc",    lua_nua_handle_destroy },
    {NULL, NULL}
};

static const luaL_Reg nua_meths[] = {
    {"handle_create",  lua_nua_handle_create },
    {"shutdown", lua_nua_shutdown },
    {"__gc",     lua_nua_destroy },
    {NULL, NULL}
};

static const luaL_Reg nua_lib[] = {
    {"create", lua_nua_create },
    {NULL, NULL}
};

int luaopen_nua(lua_State *L)
{
    luaL_newmetatable(L, NUA_HANDLE_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_handle_meths);
    lua_pop(L, 1);

    luaL_newmetatable(L, NUA_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, nua_meths);
    lua_pop(L, 1);

    luaL_register(L, "nua", nua_lib);
    return 1;
}

