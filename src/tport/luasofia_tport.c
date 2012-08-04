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

#include <sofia-sip/tport.h>
#include <sofia-sip/tport_tag.h>

typedef struct lua_tport_s lua_tport_t;

#define TPORT_MTABLE "lua_tport_t"

struct lua_tport_s {
    tport_t *tport;
    lua_State *L;
};

static const luaL_Reg tport_meths[] = {
    {NULL, NULL}
};

static const luaL_Reg tport_lib[] = {
    {NULL, NULL}
};

static const luasofia_tag_reg_t lua_tport_tags[] = {
    { "TPTAG_ANY", tptag_any },
    { "TPTAG_IDENT", tptag_ident },
    { "TPTAG_REUSE", tptag_reuse },
    { "TPTAG_FRESH", tptag_fresh },
    { "TPTAG_SERVER", tptag_server },
    { "TPTAG_PUBLIC", tptag_public },
    { "TPTAG_MTU", tptag_mtu },
    { "TPTAG_CONNECT", tptag_connect },
    { "TPTAG_QUEUESIZE", tptag_queuesize },
    { "TPTAG_SDWN_ERROR", tptag_sdwn_error },
    { "TPTAG_SDWN_AFTER", tptag_sdwn_after },
    { "TPTAG_CLOSE_AFTER", tptag_close_after },
    { "TPTAG_IDLE", tptag_idle },
    { "TPTAG_TIMEOUT", tptag_timeout },
    { "TPTAG_KEEPALIVE", tptag_keepalive },
    { "TPTAG_PINGPONG", tptag_pingpong },
    { "TPTAG_PONG2PING", tptag_pong2ping },
    { "TPTAG_SIGCOMP_LIFETIME", tptag_sigcomp_lifetime },
    { "TPTAG_COMPARTMENT", tptag_compartment },
    { "TPTAG_CERTIFICATE", tptag_certificate },
    { "TPTAG_TLS_VERSION", tptag_tls_version },
    { "TPTAG_TLS_VERIFY_PEER", tptag_tls_verify_peer },
    { "TPTAG_TLS_VERIFY_POLICY", tptag_tls_verify_policy },
    { "TPTAG_TLS_VERIFY_DEPTH", tptag_tls_verify_depth },
    { "TPTAG_TLS_VERIFY_DATE", tptag_tls_verify_date },
    { "TPTAG_TLS_VERIFY_SUBJECTS", tptag_tls_verify_subjects },
    { "TPTAG_DEBUG_DROP", tptag_debug_drop },
    { "TPTAG_UDP_RMEM", tptag_udp_rmem },
    { "TPTAG_UDP_WMEM", tptag_udp_wmem },
    { "TPTAG_THRPSIZE", tptag_thrpsize },
    { "TPTAG_THRPRQSIZE", tptag_thrprqsize },
    { "TPTAG_HTTP_CONNECT", tptag_http_connect },
    { "TPTAG_STUN_SERVER", tptag_stun_server },
    { "TPTAG_TOS", tptag_tos },
    { "TPTAG_LOG", tptag_log },
    { "TPTAG_DUMP", tptag_dump },
    { NULL, NULL}
};

static const luasofia_reg_const_t tport_constants[] = {
    {NULL, 0 }
};

int luaopen_sofia_tport(lua_State *L)
{
    luaopen_sofia(L);

    luaL_newmetatable(L, TPORT_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, tport_meths);
    lua_pop(L, 1);

    luasofia_tags_register_tags(L, lua_tport_tags);

    /* sofia[tport] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "tport");
    luaL_register(L, NULL, tport_lib);

    luasofia_const_register_constants(L, tport_constants);

    return 1;
}

