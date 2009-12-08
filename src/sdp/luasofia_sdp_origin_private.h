/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_ORIGIN_PRIVATE_H__
#define __LUASOFIA_SDP_ORIGIN_PRIVATE_H__

#define SDP_ORIGIN_TABLE_NAME "luasofia_sdp_origin_t"

static const luasofia_proxy_info_t sdp_origin_info[] = {
{"o_size",      luasofia_proxy_get_int,     offsetof(sdp_origin_t, o_size),     0},
{"o_username",  luasofia_proxy_get_string,  offsetof(sdp_origin_t, o_username), 0},
{"o_id",        luasofia_proxy_get_number,  offsetof(sdp_origin_t, o_id),       0},
{"o_version",   luasofia_proxy_get_number,  offsetof(sdp_origin_t, o_version),  0},
{"o_address",   luasofia_proxy_get_pointer, offsetof(sdp_origin_t, o_address),  0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_origin(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_ORIGIN_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_ORIGIN_PRIVATE_H__ */

