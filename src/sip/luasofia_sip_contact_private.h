/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SIP_CONTACT_PRIVATE_H__
#define __LUASOFIA_SIP_CONTACT_PRIVATE_H__

#define SIP_CONTACT_TABLE_NAME "luasofia_sip_contact_t" 

const luasofia_proxy_info_t sip_contact_info[] = {
{"m_next",    luasofia_proxy_get_pointer, offsetof(sip_contact_t, m_next), 0},
{"m_display", luasofia_proxy_get_string, offsetof(sip_contact_t, m_display), 0},
{"m_url",     luasofia_proxy_get_address, offsetof(sip_contact_t, m_url),   0},
{"m_params",  luasofia_proxy_get_pointer, offsetof(sip_contact_t, m_params), 0},
{"m_comment", luasofia_proxy_get_string, offsetof(sip_contact_t, m_comment), 0},
{"m_q",       luasofia_proxy_get_string, offsetof(sip_contact_t, m_q), 0},
{"m_expires", luasofia_proxy_get_string, offsetof(sip_contact_t, m_expires), 0},
{NULL, NULL, 0 }
};

int luasofia_sip_get_proxy_contact(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_CONTACT_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_CONTACT_PRIVATE_H__
