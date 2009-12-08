/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_KEY_PRIVATE_H__
#define __LUASOFIA_SDP_KEY_PRIVATE_H__

#define SDP_KEY_TABLE_NAME "luasofia_sdp_key_t"

static const luasofia_proxy_info_t sdp_key_info[] = {
{"k_size",       luasofia_proxy_get_int,     offsetof(sdp_key_t, k_size),        0},
{"k_method",     luasofia_proxy_get_int,     offsetof(sdp_key_t, k_method),      0},
{"k_method_name",luasofia_proxy_get_string,  offsetof(sdp_key_t, k_method_name), 0},
{"k_material",   luasofia_proxy_get_string,  offsetof(sdp_key_t, k_material),    0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_key(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_KEY_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_KEY_PRIVATE_H__ */
