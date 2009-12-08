/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_REPEAT_PRIVATE_H__
#define __LUASOFIA_SDP_REPEAT_PRIVATE_H__

#define SDP_REPEAT_TABLE_NAME "luasofia_sdp_repeat_t"

static const luasofia_proxy_info_t sdp_repeat_info[] = {
{"r_size",              luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_size),              0},
{"r_number_of_offsets", luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_number_of_offsets), 0},
{"r_interval",          luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_interval),          0},
{"r_duration",          luasofia_proxy_get_int, offsetof(sdp_repeat_t, r_duration),          0},
// FIXME {"r_offsets",         luasofia_proxy_get_int,  offsetof(sdp_repeat_t, r_offsets),          0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_repeat(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_REPEAT_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_REPEAT_PRIVATE_H__ */

