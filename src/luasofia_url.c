/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "luasofia_tags.h"
#include "luasofia_utils.h"
#include "luasofia_struct.h"

#include <sofia-sip/url.h>
#include <sofia-sip/url_tag.h>

typedef struct lua_url_s lua_url_t;

#define URL_MTABLE "lua_url_t"

struct lua_url_s {
    url_t *url;
    lua_State *L;
};

static const luasofia_struct_info_t url_info[] = {
{"pad",      luasofia_struct_get_char,   offsetof(url_t, url_pad),      offsetof(url_t, url_type)},
{"type",     luasofia_struct_get_char,   offsetof(url_t, url_type),     0},
{"root",     luasofia_struct_get_char,   offsetof(url_t, url_root),     0},
{"scheme",   luasofia_struct_get_string, offsetof(url_t, url_scheme),   0},
{"user",     luasofia_struct_get_string, offsetof(url_t, url_user),     0},
{"password", luasofia_struct_get_string, offsetof(url_t, url_password), 0},
{"host",     luasofia_struct_get_string, offsetof(url_t, url_host),     0},
{"port",     luasofia_struct_get_string, offsetof(url_t, url_port),     0},
{"path",     luasofia_struct_get_string, offsetof(url_t, url_path),     0},
{"params",   luasofia_struct_get_string, offsetof(url_t, url_params),   0},
{"headers",  luasofia_struct_get_string, offsetof(url_t, url_headers),  0},
{"fragment", luasofia_struct_get_string, offsetof(url_t, url_fragment), 0},
{NULL, NULL, 0 }
};

int luasofia_url_get_proxy(lua_State *L)
{
    /* Push struct info table at stack */
    luasofia_struct_create_info_table(L, url_info);    
    /* Create struct with info table */
    return luasofia_struct_create(L);
}

static const luaL_Reg url_meths[] = {
    {NULL, NULL}
};

static const luaL_Reg url_lib[] = {
    {"get_proxy",  luasofia_url_get_proxy },
    {NULL, NULL}
};

static const luasofia_tag_reg_t url_tags[] = {
    { "URLTAG_ANY", urltag_any },
    { "URLTAG_URL", urltag_url },
    { "URLTAG_URL_REF", urltag_url_ref },
    { NULL, NULL}
};

static const luasofia_reg_const_t url_constants[] = {
    {NULL, 0 }
};

int luaopen_luasofia_url(lua_State *L)
{
    luaL_newmetatable(L, URL_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, url_meths);
    lua_pop(L, 1);

    luasofia_tags_register(L, url_tags);

    luaopen_luasofia(L);

    /* luasofia[url] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "url");
    luaL_register(L, NULL, url_lib);

    luasofia_register_constants(L, url_constants);

    return 1;
}

