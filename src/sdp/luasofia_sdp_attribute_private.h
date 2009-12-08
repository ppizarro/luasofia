/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_ATTRIBUTE_PRIVATE_H__
#define __LUASOFIA_SDP_ATTRIBUTE_PRIVATE_H__

#define SDP_ATTRIBUTE_TABLE_NAME "luasofia_sdp_attribute_t"

static const luasofia_proxy_info_t sdp_attribute_info[] = {
{"a_size",  luasofia_proxy_get_int,     offsetof(sdp_attribute_t, a_size), 0},
{"a_next",  luasofia_proxy_get_pointer, offsetof(sdp_attribute_t, a_next), 0},
{"a_name",  luasofia_proxy_get_string,  offsetof(sdp_attribute_t, a_name), 0},
{"a_value", luasofia_proxy_get_string,  offsetof(sdp_attribute_t, a_value),0},
{NULL, NULL}
};

static int luasofia_sdp_get_proxy_attribute(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_ATTRIBUTE_TABLE_NAME);
}


#endif /* __LUASOFIA_SDP_ATTRIBUTE_PRIVATE_H__ */
