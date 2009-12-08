/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_LIST_PRIVATE_H__
#define __LUASOFIA_SDP_LIST_PRIVATE_H__

#define SDP_LIST_TABLE_NAME "luasofia_sdp_list_t"

static const luasofia_proxy_info_t sdp_list_info[] = {
{"l_size", luasofia_proxy_get_int,     offsetof(sdp_list_t, l_size), 0},
{"l_next", luasofia_proxy_get_pointer, offsetof(sdp_list_t, l_next), 0},
{"l_text", luasofia_proxy_get_string,  offsetof(sdp_list_t, l_text), 0},
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_list(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_LIST_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_LIST_PRIVATE_H__ */


