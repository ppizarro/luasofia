/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 *
 * This file is part of Luasofia.
 *
 * Luasofia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Luasofia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"
#include "utils/luasofia_proxy.h"

#include <sofia-sip/url.h>
#include <sofia-sip/url_tag.h>

static const luasofia_proxy_info_t url_info[] = {
{"pad",      luasofia_proxy_get_char,   offsetof(url_t, url_pad),      offsetof(url_t, url_type)},
{"type",     luasofia_proxy_get_char,   offsetof(url_t, url_type),     0},
{"root",     luasofia_proxy_get_char,   offsetof(url_t, url_root),     0},
{"scheme",   luasofia_proxy_get_string, offsetof(url_t, url_scheme),   0},
{"user",     luasofia_proxy_get_string, offsetof(url_t, url_user),     0},
{"password", luasofia_proxy_get_string, offsetof(url_t, url_password), 0},
{"host",     luasofia_proxy_get_string, offsetof(url_t, url_host),     0},
{"port",     luasofia_proxy_get_string, offsetof(url_t, url_port),     0},
{"path",     luasofia_proxy_get_string, offsetof(url_t, url_path),     0},
{"params",   luasofia_proxy_get_string, offsetof(url_t, url_params),   0},
{"headers",  luasofia_proxy_get_string, offsetof(url_t, url_headers),  0},
{"fragment", luasofia_proxy_get_string, offsetof(url_t, url_fragment), 0},
{NULL, NULL, 0, 0 }
};

static int luasofia_url_get_proxy(lua_State *L)
{
    return luasofia_proxy_create(L, "luasofia_url_t");
}

static const luaL_Reg url_lib[] = {
    {"get_proxy",  luasofia_url_get_proxy },
    {NULL, NULL}
};

static const luasofia_tag_reg_t url_tags[] = {
    { "URLTAG_ANY", urltag_any },
    { "URLTAG_URL", urltag_url },
    { NULL, NULL}
};

static const luasofia_reg_const_t url_constants[] = {
    {NULL, 0 }
};

int luaopen_sofia_url(lua_State *L)
{
    luaopen_sofia(L);

    /* sofia[url] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "url");
    luaL_register(L, NULL, url_lib);

    luasofia_tags_register_tags(L, url_tags);

    luasofia_proxy_register_info_table(L, "luasofia_url_t", url_info);

    luasofia_const_register_constants(L, url_constants);

    return 1;
}

