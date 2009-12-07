/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_VIA_PRIVATE_H__
#define __LUASOFIA_SIP_VIA_PRIVATE_H__

#define SIP_VIA_TABLE_NAME     "luasofia_sip_via_t"

static const luasofia_proxy_info_t sip_via_info[] = {
{"v_next",     luasofia_proxy_get_pointer, offsetof(sip_via_t, v_next),    0},
{"v_protocol", luasofia_proxy_get_string,  offsetof(sip_via_t, v_protocol),0},
{"v_host",     luasofia_proxy_get_string,  offsetof(sip_via_t, v_host),    0},
{"v_port",     luasofia_proxy_get_string,  offsetof(sip_via_t, v_port),    0},
{"v_params",   luasofia_proxy_get_pointer, offsetof(sip_via_t, v_params),  0},
{"v_comment",  luasofia_proxy_get_string,  offsetof(sip_via_t, v_comment), 0},
{"v_ttl",      luasofia_proxy_get_string,  offsetof(sip_via_t, v_ttl),     0},
{"v_maddr",    luasofia_proxy_get_string,  offsetof(sip_via_t, v_maddr),   0},
{"v_received", luasofia_proxy_get_string,  offsetof(sip_via_t, v_received),0},
{"v_branch",   luasofia_proxy_get_string,  offsetof(sip_via_t, v_branch),  0},
{"v_rport",    luasofia_proxy_get_string,  offsetof(sip_via_t, v_rport),   0},
{"v_comp",     luasofia_proxy_get_string,  offsetof(sip_via_t, v_comp),    0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_via(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_VIA_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_VIA_PRIVATE_H__
