/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_CONNECTION_PRIVATE_H__
#define __LUASOFIA_SDP_CONNECTION_PRIVATE_H__

#define SDP_CONNECTION_TABLE_NAME "luasofia_sdp_connection_t"

static const luasofia_proxy_info_t sdp_connection_info[] = {
{"c_size",     luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_size),     0},
{"c_next",     luasofia_proxy_get_pointer, offsetof(sdp_connection_t, c_next),     0},
{"c_nettype",  luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_nettype),  0},
{"c_addrtype", luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_addrtype), 0},
{"c_address",  luasofia_proxy_get_string,  offsetof(sdp_connection_t, c_address),  0},
// FIXME how to get unsigned  c_ttl : 8;   {"c_ttl",      luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_ttl),      0},
// FIXME how to get unsigned  c_mcast : 1; {"c_mcast",    luasofia_proxy_get_boolean, offsetof(sdp_connection_t, c_mcast),    0},
{"c_groups",   luasofia_proxy_get_int,     offsetof(sdp_connection_t, c_groups),   0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_connection(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_CONNECTION_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_CONNECTION_PRIVATE_H__ */

