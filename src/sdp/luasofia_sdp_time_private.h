/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_TIME_PRIVATE_H__
#define __LUASOFIA_SDP_TIME_PRIVATE_H__

#define SDP_TIME_TABLE_NAME "luasofia_sdp_time_t"

static const luasofia_proxy_info_t sdp_time_info[] = {
{"t_size",   luasofia_proxy_get_int,     offsetof(sdp_time_t, t_size),   0},
{"t_next",   luasofia_proxy_get_pointer, offsetof(sdp_time_t, t_next),   0},
{"t_start",  luasofia_proxy_get_int,     offsetof(sdp_time_t, t_start),  0},
{"t_stop",   luasofia_proxy_get_int,     offsetof(sdp_time_t, t_stop),   0},
{"t_repeat", luasofia_proxy_get_pointer, offsetof(sdp_time_t, t_repeat), 0},
{"t_zone",   luasofia_proxy_get_pointer, offsetof(sdp_time_t, t_zone),   0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_time(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_TIME_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_TIME_PRIVATE_H__ */
