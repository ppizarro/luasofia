/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_EVENT_PRIVATE_H__
#define __LUASOFIA_SIP_EVENT_PRIVATE_H__

#define SIP_EVENT_TABLE_NAME  "luasofia_sip_event_t"

const luasofia_proxy_info_t sip_event_info[] = {
{"o_type",  luasofia_proxy_get_string,  offsetof(sip_event_t, o_type),   0},
{"o_params",luasofia_proxy_get_pointer, offsetof(sip_event_t, o_params), 0},
{"o_id",    luasofia_proxy_get_string,  offsetof(sip_event_t, o_id),     0},
{NULL, NULL, 0 }
};

int luasofia_sip_get_proxy_event(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_EVENT_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_EVENT_PRIVATE_H__
