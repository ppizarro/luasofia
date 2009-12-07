/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_REQUEST_PRIVATE_H__
#define __LUASOFIA_SIP_REQUEST_PRIVATE_H__

#define SIP_REQUEST_TABLE_NAME "luasofia_sip_request_t"

const luasofia_proxy_info_t sip_request_info[] = {
{"rq_method",      luasofia_proxy_get_address, offsetof(sip_request_t, rq_method),     0},
{"rq_method_name", luasofia_proxy_get_string,  offsetof(sip_request_t, rq_method_name),0},
{"rq_url",         luasofia_proxy_get_address, offsetof(sip_request_t, rq_url),        0},
{"rq_version",     luasofia_proxy_get_string,  offsetof(sip_request_t, rq_version), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_request(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_REQUEST_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_REQUEST_PRIVATE_H__
