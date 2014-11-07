/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 * @author Guilherme Silveira <xguiga@gmail.com>
 *
 * This file is part of Luasofia.
 *
 * Luasofia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Luasofia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"
#include "utils/luasofia_proxy.h"

#include <sofia-sip/sip.h>
#include <sofia-sip/sip_tag.h>
#include <sofia-sip/sip_status.h>

#include "luasofia_sip_addr_private.h"
#include "luasofia_sip_contact_private.h"
#include "luasofia_sip_request_private.h"
#include "luasofia_sip_via_private.h"
#include "luasofia_sip_private.h"
#include "luasofia_sip_status_private.h"
#include "luasofia_sip_event_private.h"
#include "luasofia_sip_content_type_private.h"
#include "luasofia_sip_content_length_private.h"
#include "luasofia_sip_content_disposition_private.h"
#include "luasofia_sip_accept_private.h"
#include "luasofia_sip_allow_private.h"
#include "luasofia_sip_call_id_private.h"
#include "luasofia_sip_authenticate_private.h"
#include "luasofia_sip_subscription_state_private.h"
#include "luasofia_sip_msg_payload_private.h"

static int luasofia_sip_status_phrase(lua_State *L)
{
    int status = lua_tointeger(L, -1);
    char const *phrase = sip_status_phrase(status);
    lua_pushstring(L, phrase);
    return 1;
}

static const luaL_Reg sip_lib[] = {
    {"get_proxy",                    luasofia_sip_get_proxy },
    {"get_proxy_addr",               luasofia_sip_get_proxy_addr },
    {"get_proxy_contact",            luasofia_sip_get_proxy_contact },
    {"get_proxy_request",            luasofia_sip_get_proxy_request },
    {"get_proxy_via",                luasofia_sip_get_proxy_via },
    {"get_proxy_status",             luasofia_sip_get_proxy_status },
    {"get_proxy_event",              luasofia_sip_get_proxy_event },
    {"get_proxy_content_type",       luasofia_sip_get_proxy_content_type },
    {"get_proxy_content_length",     luasofia_sip_get_proxy_content_length },
    {"get_proxy_content_disposition",luasofia_sip_get_proxy_content_disposition },
    {"get_proxy_accept",             luasofia_sip_get_proxy_accept },
    {"get_proxy_allow",              luasofia_sip_get_proxy_allow },
    {"get_proxy_call_id",            luasofia_sip_get_proxy_call_id },
    {"get_proxy_authenticate",       luasofia_sip_get_proxy_authenticate },
    {"get_proxy_subscription_state", luasofia_sip_get_proxy_subscription_state },
    {"get_proxy_msg_payload",        luasofia_sip_get_proxy_msg_payload },
    {"status_phrase",                luasofia_sip_status_phrase },
    {NULL, NULL}
};

static const luasofia_tag_reg_t sip_tags[] = {
    { "SIPTAG_ANY", siptag_any },
    { "SIPTAG_END", siptag_end },
    { "SIPTAG_SIP", siptag_sip },
    { "SIPTAG_HEADER", siptag_header },
    { "SIPTAG_HEADER_STR", siptag_header_str },
    { "SIPTAG_REQUEST", siptag_request },
    { "SIPTAG_REQUEST_STR", siptag_request_str },
    { "SIPTAG_STATUS", siptag_status },
    { "SIPTAG_STATUS_STR", siptag_status_str },
    { "SIPTAG_VIA", siptag_via },
    { "SIPTAG_VIA_STR", siptag_via_str },
    { "SIPTAG_ROUTE", siptag_route },
    { "SIPTAG_ROUTE_STR", siptag_route_str },
    { "SIPTAG_RECORD_ROUTE", siptag_record_route },
    { "SIPTAG_RECORD_ROUTE_STR", siptag_record_route_str },
    { "SIPTAG_MAX_FORWARDS", siptag_max_forwards },
    { "SIPTAG_MAX_FORWARDS_STR", siptag_max_forwards_str },
    { "SIPTAG_PROXY_REQUIRE", siptag_proxy_require },
    { "SIPTAG_PROXY_REQUIRE_STR", siptag_proxy_require_str },
    { "SIPTAG_FROM", siptag_from },
    { "SIPTAG_FROM_STR", siptag_from_str },
    { "SIPTAG_TO", siptag_to },
    { "SIPTAG_TO_STR", siptag_to_str },
    { "SIPTAG_CALL_ID", siptag_call_id },
    { "SIPTAG_CALL_ID_STR", siptag_call_id_str },
    { "SIPTAG_CSEQ", siptag_cseq },
    { "SIPTAG_CSEQ_STR", siptag_cseq_str },
    { "SIPTAG_CONTACT", siptag_contact },
    { "SIPTAG_CONTACT_STR", siptag_contact_str },
    { "SIPTAG_RSEQ", siptag_rseq },
    { "SIPTAG_RSEQ_STR", siptag_rseq_str },
    { "SIPTAG_RACK", siptag_rack },
    { "SIPTAG_RACK_STR", siptag_rack_str },
    { "SIPTAG_REQUEST_DISPOSITION", siptag_request_disposition },
    { "SIPTAG_REQUEST_DISPOSITION_STR", siptag_request_disposition_str },
    { "SIPTAG_ACCEPT_CONTACT", siptag_accept_contact },
    { "SIPTAG_ACCEPT_CONTACT_STR", siptag_accept_contact_str  },
    { "SIPTAG_REJECT_CONTACT", siptag_reject_contact },
    { "SIPTAG_REJECT_CONTACT_STR", siptag_reject_contact_str },
    { "SIPTAG_EXPIRES", siptag_expires },
    { "SIPTAG_EXPIRES_STR", siptag_expires_str },
    { "SIPTAG_DATE", siptag_date },
    { "SIPTAG_DATE_STR", siptag_date_str },
    { "SIPTAG_RETRY_AFTER", siptag_retry_after },
    { "SIPTAG_RETRY_AFTER_STR", siptag_retry_after_str },
    { "SIPTAG_TIMESTAMP", siptag_timestamp },
    { "SIPTAG_TIMESTAMP_STR", siptag_timestamp_str },
    { "SIPTAG_MIN_EXPIRES", siptag_min_expires },
    { "SIPTAG_MIN_EXPIRES_STR", siptag_min_expires_str },
    { "SIPTAG_SUBJECT", siptag_subject },
    { "SIPTAG_SUBJECT_STR", siptag_subject_str },
    { "SIPTAG_PRIORITY", siptag_priority_ref },
    { "SIPTAG_PRIORITY_STR", siptag_priority_str },
    { "SIPTAG_CALL_INFO", siptag_call_info },
    { "SIPTAG_CALL_INFO_STR", siptag_call_info_str },
    { "SIPTAG_ORGANIZATION", siptag_organization },
    { "SIPTAG_ORGANIZATION_STR", siptag_organization_str },
    { "SIPTAG_SERVER", siptag_server },
    { "SIPTAG_SERVER_STR", siptag_server_str },
    { "SIPTAG_USER_AGENT", siptag_user_agent },
    { "SIPTAG_USER_AGENT_STR", siptag_user_agent_str },
    { "SIPTAG_IN_REPLY_TO", siptag_in_reply_to },
    { "SIPTAG_IN_REPLY_TO_STR", siptag_in_reply_to_str },
    { "SIPTAG_ACCEPT", siptag_accept },
    { "SIPTAG_ACCEPT_STR", siptag_accept_str },
    { "SIPTAG_ACCEPT_ENCODING", siptag_accept_encoding },
    { "SIPTAG_ACCEPT_ENCODING_STR", siptag_accept_encoding_str },
    { "SIPTAG_ACCEPT_LANGUAGE", siptag_accept_language },
    { "SIPTAG_ACCEPT_LANGUAGE_STR", siptag_accept_language_str },
    { "SIPTAG_ALLOW", siptag_allow },
    { "SIPTAG_ALLOW_STR", siptag_allow_str },
    { "SIPTAG_REQUIRE", siptag_require },
    { "SIPTAG_REQUIRE_STR", siptag_require_str },
    { "SIPTAG_SUPPORTED", siptag_supported },
    { "SIPTAG_SUPPORTED_STR", siptag_supported_str },
    { "SIPTAG_UNSUPPORTED", siptag_unsupported },
    { "SIPTAG_UNSUPPORTED_STR", siptag_unsupported_str },
    { "SIPTAG_EVENT", siptag_event },
    { "SIPTAG_EVENT_STR", siptag_event_str },
    { "SIPTAG_ALLOW_EVENTS", siptag_allow_events },
    { "SIPTAG_ALLOW_EVENTS_STR", siptag_allow_events_str },
    { "SIPTAG_SUBSCRIPTION_STATE", siptag_subscription_state },
    { "SIPTAG_SUBSCRIPTION_STATE_STR", siptag_subscription_state_str },
    { "SIPTAG_PROXY_AUTHENTICATE", siptag_proxy_authenticate },
    { "SIPTAG_PROXY_AUTHENTICATE_STR", siptag_proxy_authenticate_str },
    { "SIPTAG_PROXY_AUTHENTICATION_INFO", siptag_proxy_authentication_info },
    { "SIPTAG_PROXY_AUTHENTICATION_INFO_STR", siptag_proxy_authentication_info_str },
    { "SIPTAG_PROXY_AUTHORIZATION", siptag_proxy_authorization },
    { "SIPTAG_PROXY_AUTHORIZATION_STR", siptag_proxy_authorization_str },
    { "SIPTAG_AUTHORIZATION", siptag_authorization },
    { "SIPTAG_AUTHORIZATION_STR", siptag_authorization_str },
    { "SIPTAG_WWW_AUTHENTICATE", siptag_www_authenticate },
    { "SIPTAG_WWW_AUTHENTICATE_STR", siptag_www_authenticate_str },
    { "SIPTAG_AUTHENTICATION_INFO", siptag_authentication_info },
    { "SIPTAG_AUTHENTICATION_INFO_STR", siptag_authentication_info_str },
    { "SIPTAG_ERROR_INFO", siptag_error_info },
    { "SIPTAG_ERROR_INFO_STR", siptag_error_info_str },
    { "SIPTAG_WARNING", siptag_warning },
    { "SIPTAG_WARNING_STR", siptag_warning_str },
    { "SIPTAG_REFER_TO", siptag_refer_to },
    { "SIPTAG_REFER_TO_STR", siptag_refer_to_str },
    { "SIPTAG_REFERRED_BY", siptag_referred_by },
    { "SIPTAG_REFERRED_BY_STR", siptag_referred_by_str },
    { "SIPTAG_REPLACES", siptag_replaces },
    { "SIPTAG_REPLACES_STR", siptag_replaces_str },
    { "SIPTAG_SESSION_EXPIRES", siptag_session_expires },
    { "SIPTAG_SESSION_EXPIRES_STR", siptag_session_expires_str },
    { "SIPTAG_MIN_SE", siptag_min_se },
    { "SIPTAG_MIN_SE_STR", siptag_min_se_str },
    { "SIPTAG_PATH", siptag_path },
    { "SIPTAG_PATH_STR", siptag_path_str },
    { "SIPTAG_SERVICE_ROUTE", siptag_service_route },
    { "SIPTAG_SERVICE_ROUTE_STR", siptag_service_route_str },
    { "SIPTAG_REASON", siptag_reason },
    { "SIPTAG_REASON_STR", siptag_reason_str },
    { "SIPTAG_SECURITY_CLIENT", siptag_security_client },
    { "SIPTAG_SECURITY_CLIENT_STR", siptag_security_client_str },
    { "SIPTAG_SECURITY_SERVER", siptag_security_server },
    { "SIPTAG_SECURITY_SERVER_STR", siptag_security_server_str },
    { "SIPTAG_SECURITY_VERIFY", siptag_security_verify },
    { "SIPTAG_SECURITY_VERIFY_STR", siptag_security_verify_str },
    { "SIPTAG_PRIVACY", siptag_privacy },
    { "SIPTAG_PRIVACY_STR", siptag_privacy_str },
    { "SIPTAG_ETAG", siptag_etag },
    { "SIPTAG_ETAG_STR", siptag_etag_str },
    { "SIPTAG_IF_MATCH", siptag_if_match },
    { "SIPTAG_IF_MATCH_STR", siptag_if_match_str },
    { "SIPTAG_MIME_VERSION", siptag_mime_version },
    { "SIPTAG_MIME_VERSION_STR", siptag_mime_version_str },
    { "SIPTAG_CONTENT_TYPE", siptag_content_type },
    { "SIPTAG_CONTENT_TYPE_STR", siptag_content_type_str },
    { "SIPTAG_CONTENT_ENCODING", siptag_content_encoding },
    { "SIPTAG_CONTENT_ENCODING_STR", siptag_content_encoding_str },
    { "SIPTAG_CONTENT_LANGUAGE", siptag_content_language },
    { "SIPTAG_CONTENT_LANGUAGE_STR", siptag_content_language_str },
    { "SIPTAG_CONTENT_DISPOSITION", siptag_content_disposition },
    { "SIPTAG_CONTENT_DISPOSITION_STR", siptag_content_disposition_str },
    { "SIPTAG_CONTENT_LENGTH", siptag_content_length },
    { "SIPTAG_CONTENT_LENGTH_STR", siptag_content_length_str },
    { "SIPTAG_UNKNOWN", siptag_unknown },
    { "SIPTAG_UNKNOWN_STR", siptag_unknown_str },
    { "SIPTAG_ERROR", siptag_error },
    { "SIPTAG_ERROR_STR", siptag_error_str },
    { "SIPTAG_SEPARATOR", siptag_separator },
    { "SIPTAG_SEPARATOR_STR", siptag_separator_str },
    { "SIPTAG_PAYLOAD", siptag_payload },
    { "SIPTAG_PAYLOAD_STR", siptag_payload_str },
    { NULL, NULL}
};

static const luasofia_reg_const_t sip_constants[] = {
    {NULL, 0 }
};

int luaopen_sofia_sip(lua_State *L)
{
    luaopen_sofia(L);

    /* sofia[sip] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "sip");
    luaL_register(L, NULL, sip_lib);

    luasofia_tags_register_tags(L, sip_tags);

    luasofia_proxy_register_info_table(L, SIP_TABLE_NAME, sip_info);    
    luasofia_proxy_register_info_table(L, SIP_ADDR_TABLE_NAME, sip_addr_info);    
    luasofia_proxy_register_info_table(L, SIP_CONTACT_TABLE_NAME, sip_contact_info);    
    luasofia_proxy_register_info_table(L, SIP_REQUEST_TABLE_NAME, sip_request_info);
    luasofia_proxy_register_info_table(L, SIP_VIA_TABLE_NAME, sip_via_info);
    luasofia_proxy_register_info_table(L, SIP_STATUS_TABLE_NAME, sip_status_info);
    luasofia_proxy_register_info_table(L, SIP_EVENT_TABLE_NAME, sip_event_info);
    luasofia_proxy_register_info_table(L, SIP_CONTENT_TYPE_TABLE_NAME, sip_content_type_info);    
    luasofia_proxy_register_info_table(L, SIP_CONTENT_LENGTH_TABLE_NAME, sip_content_length_info);    
    luasofia_proxy_register_info_table(L, SIP_CONTENT_DISPOSITION_TABLE_NAME, sip_content_disposition_info);    
    luasofia_proxy_register_info_table(L, SIP_ACCEPT_TABLE_NAME, sip_accept_info);
    luasofia_proxy_register_info_table(L, SIP_ALLOW_TABLE_NAME, sip_allow_info);
    luasofia_proxy_register_info_table(L, SIP_CALL_ID_TABLE_NAME, sip_call_id_info);
    luasofia_proxy_register_info_table(L, SIP_AUTHENTICATE_TABLE_NAME, sip_authenticate_info);
    luasofia_proxy_register_info_table(L, SIP_SUBSCRIPTION_STATE_TABLE_NAME, sip_subscription_state_info);
    luasofia_proxy_register_info_table(L, SIP_MSG_PAYLOAD_TABLE_NAME, sip_msg_payload_info);

    luasofia_const_register_constants(L, sip_constants);

    return 1;
}

