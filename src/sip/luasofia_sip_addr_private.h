/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_ADDR_PRIVATE_H__
#define __LUASOFIA_SIP_ADDR_PRIVATE_H__

#define SIP_ADDR_TABLE_NAME    "luasofia_sip_addr_t" 

static const luasofia_proxy_info_t sip_addr_info[] = {
{"a_display", luasofia_proxy_get_string, offsetof(sip_addr_t, a_display), 0},
{"a_url",     luasofia_proxy_get_address, offsetof(sip_addr_t, a_url),   0},
{"a_params",  luasofia_proxy_get_pointer, offsetof(sip_addr_t, a_params), 0},
{"a_comment", luasofia_proxy_get_string, offsetof(sip_addr_t, a_comment), 0},
{"a_tag",     luasofia_proxy_get_string, offsetof(sip_addr_t, a_tag), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_addr(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_ADDR_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_ADDR_PRIVATE_H__
