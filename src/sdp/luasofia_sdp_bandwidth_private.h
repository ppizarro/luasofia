/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__
#define __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__

#define SDP_BANDWIDTH_TABLE_NAME "luasofia_sdp_bandwidth_t"

static const luasofia_proxy_info_t sdp_bandwidth_info[] = {
{"b_size",         luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_size),     0},
{"b_next",         luasofia_proxy_get_pointer, offsetof(sdp_bandwidth_t, b_next),     0},
{"b_modifier",     luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_modifier), 0},
{"b_modifier_name",luasofia_proxy_get_string,  offsetof(sdp_bandwidth_t, b_modifier_name), 0},
{"b_value",        luasofia_proxy_get_int,     offsetof(sdp_bandwidth_t, b_value),0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_bandwidth(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_BANDWIDTH_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_BANDWIDTH_PRIVATE_H__ */

