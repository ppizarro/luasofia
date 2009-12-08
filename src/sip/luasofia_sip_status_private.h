/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_STATUS_PRIVATE_H__
#define __LUASOFIA_SIP_STATUS_PRIVATE_H__

#define SIP_STATUS_TABLE_NAME  "luasofia_sip_status_t"

static const luasofia_proxy_info_t sip_status_info[] = {
{"st_version", luasofia_proxy_get_string, offsetof(sip_status_t, st_version),0},
{"st_status",  luasofia_proxy_get_int,    offsetof(sip_status_t, st_status), 0},
{"st_phrase",  luasofia_proxy_get_string, offsetof(sip_status_t, st_phrase), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy_status(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_STATUS_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_STATUS_PRIVATE_H__
