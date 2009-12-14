/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * Copyright (C) 2009 Digitro Corporation <www.digitro.com.br>
 *
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
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

#ifndef __LUASOFIA_SIP_PRIVATE_H__
#define __LUASOFIA_SIP_PRIVATE_H__

#define SIP_TABLE_NAME "luasofia_sip_t"

static const luasofia_proxy_info_t sip_info[] = {
{"sip_user", luasofia_proxy_get_pointer, offsetof(sip_t, sip_user), 0},
{"sip_size", luasofia_proxy_get_int, offsetof(sip_t, sip_size), 0},
{"sip_flags", luasofia_proxy_get_int, offsetof(sip_t, sip_flags), 0},
{"sip_error", luasofia_proxy_get_pointer, offsetof(sip_t, sip_error), 0},
{"sip_request", luasofia_proxy_get_pointer, offsetof(sip_t, sip_request), 0},
{"sip_status", luasofia_proxy_get_pointer, offsetof(sip_t, sip_status), 0},
{"sip_via", luasofia_proxy_get_pointer, offsetof(sip_t, sip_via), 0},
{"sip_route", luasofia_proxy_get_pointer, offsetof(sip_t, sip_route), 0},
{"sip_record_route", luasofia_proxy_get_pointer, offsetof(sip_t, sip_record_route), 0},
{"sip_max_forwards", luasofia_proxy_get_pointer, offsetof(sip_t, sip_max_forwards), 0},
{"sip_proxy_require", luasofia_proxy_get_pointer, offsetof(sip_t, sip_proxy_require), 0},
{"sip_from", luasofia_proxy_get_pointer, offsetof(sip_t, sip_from), 0},
{"sip_to", luasofia_proxy_get_pointer, offsetof(sip_t, sip_to), 0},
{"sip_call_id", luasofia_proxy_get_pointer, offsetof(sip_t, sip_call_id), 0},
{"sip_cseq", luasofia_proxy_get_pointer, offsetof(sip_t, sip_cseq), 0},
{"sip_contact", luasofia_proxy_get_pointer, offsetof(sip_t, sip_contact), 0},
{"sip_rseq", luasofia_proxy_get_pointer, offsetof(sip_t, sip_rseq), 0},
{"sip_rack", luasofia_proxy_get_pointer, offsetof(sip_t, sip_rack), 0},
{"sip_request_disposition", luasofia_proxy_get_pointer, offsetof(sip_t, sip_request_disposition), 0},
{"sip_accept_contact", luasofia_proxy_get_pointer, offsetof(sip_t, sip_accept_contact), 0},
{"sip_reject_contact", luasofia_proxy_get_pointer, offsetof(sip_t, sip_reject_contact), 0},
{"sip_expires", luasofia_proxy_get_pointer, offsetof(sip_t, sip_expires), 0},
{"sip_date", luasofia_proxy_get_pointer, offsetof(sip_t, sip_date), 0},
{"sip_retry_after", luasofia_proxy_get_pointer, offsetof(sip_t, sip_retry_after), 0},
{"sip_timestamp", luasofia_proxy_get_pointer, offsetof(sip_t, sip_timestamp), 0},
{"sip_min_expires", luasofia_proxy_get_pointer, offsetof(sip_t, sip_min_expires), 0},
{"sip_subject", luasofia_proxy_get_pointer, offsetof(sip_t, sip_subject), 0},
{"sip_priority", luasofia_proxy_get_pointer, offsetof(sip_t, sip_priority), 0},
{"sip_call_info", luasofia_proxy_get_pointer, offsetof(sip_t, sip_call_info), 0},
{"sip_organization", luasofia_proxy_get_pointer, offsetof(sip_t, sip_organization), 0},
{"sip_server", luasofia_proxy_get_pointer, offsetof(sip_t, sip_server), 0},
{"sip_user_agent", luasofia_proxy_get_pointer, offsetof(sip_t, sip_user_agent), 0},
{"sip_in_reply_to", luasofia_proxy_get_pointer, offsetof(sip_t, sip_in_reply_to), 0},
{"sip_accept", luasofia_proxy_get_pointer, offsetof(sip_t, sip_accept), 0},
{"sip_accept_encoding", luasofia_proxy_get_pointer, offsetof(sip_t, sip_accept_encoding), 0},
{"sip_accept_language", luasofia_proxy_get_pointer, offsetof(sip_t, sip_accept_language), 0},
{"sip_allow", luasofia_proxy_get_pointer, offsetof(sip_t, sip_allow), 0},
{"sip_require", luasofia_proxy_get_pointer, offsetof(sip_t, sip_require), 0},
{"sip_supported", luasofia_proxy_get_pointer, offsetof(sip_t, sip_supported), 0},
{"sip_unsupported", luasofia_proxy_get_pointer, offsetof(sip_t, sip_unsupported), 0},
{"sip_event", luasofia_proxy_get_pointer, offsetof(sip_t, sip_event), 0},
{"sip_allow_events", luasofia_proxy_get_pointer, offsetof(sip_t, sip_allow_events), 0},
{"sip_subscription_state", luasofia_proxy_get_pointer, offsetof(sip_t, sip_subscription_state), 0},
{"sip_proxy_authenticate", luasofia_proxy_get_pointer, offsetof(sip_t, sip_proxy_authenticate), 0},
{"sip_proxy_authentication_info", luasofia_proxy_get_pointer, offsetof(sip_t, sip_proxy_authentication_info), 0},
{"sip_proxy_authorization", luasofia_proxy_get_pointer, offsetof(sip_t, sip_proxy_authorization), 0},
{"sip_authorization", luasofia_proxy_get_pointer, offsetof(sip_t, sip_authorization), 0},
{"sip_www_authenticate", luasofia_proxy_get_pointer, offsetof(sip_t, sip_www_authenticate), 0},
{"sip_authentication_info", luasofia_proxy_get_pointer, offsetof(sip_t, sip_authentication_info), 0},
{"sip_error_info", luasofia_proxy_get_pointer, offsetof(sip_t, sip_error_info), 0},
{"sip_warning", luasofia_proxy_get_pointer, offsetof(sip_t, sip_warning), 0},
{"sip_refer_to", luasofia_proxy_get_pointer, offsetof(sip_t, sip_refer_to), 0},
{"sip_referred_by", luasofia_proxy_get_pointer, offsetof(sip_t, sip_referred_by), 0},
{"sip_replaces", luasofia_proxy_get_pointer, offsetof(sip_t, sip_replaces), 0},
{"sip_session_expires", luasofia_proxy_get_pointer, offsetof(sip_t, sip_session_expires), 0},
{"sip_min_se", luasofia_proxy_get_pointer, offsetof(sip_t, sip_min_se), 0},
{"sip_path", luasofia_proxy_get_pointer, offsetof(sip_t, sip_path), 0},
{"sip_service_route", luasofia_proxy_get_pointer, offsetof(sip_t, sip_service_route), 0},
{"sip_reason", luasofia_proxy_get_pointer, offsetof(sip_t, sip_reason), 0},
{"sip_security_client", luasofia_proxy_get_pointer, offsetof(sip_t, sip_security_client), 0},
{"sip_security_server", luasofia_proxy_get_pointer, offsetof(sip_t, sip_security_server), 0},
{"sip_security_verify", luasofia_proxy_get_pointer, offsetof(sip_t, sip_security_verify), 0},
{"sip_privacy", luasofia_proxy_get_pointer, offsetof(sip_t, sip_privacy), 0},
{"sip_etag", luasofia_proxy_get_pointer, offsetof(sip_t, sip_etag), 0},
{"sip_if_match", luasofia_proxy_get_pointer, offsetof(sip_t, sip_if_match), 0},
{"sip_mime_version", luasofia_proxy_get_pointer, offsetof(sip_t, sip_mime_version), 0},
{"sip_content_type", luasofia_proxy_get_pointer, offsetof(sip_t, sip_content_type), 0},
{"sip_content_encoding", luasofia_proxy_get_pointer, offsetof(sip_t, sip_content_encoding), 0},
{"sip_content_language", luasofia_proxy_get_pointer, offsetof(sip_t, sip_content_language), 0},
{"sip_content_disposition", luasofia_proxy_get_pointer, offsetof(sip_t, sip_content_disposition), 0},
{"sip_content_length", luasofia_proxy_get_pointer, offsetof(sip_t, sip_content_length), 0},
{"sip_unknown", luasofia_proxy_get_pointer, offsetof(sip_t, sip_unknown), 0},
{"sip_separator", luasofia_proxy_get_pointer, offsetof(sip_t, sip_separator), 0},
{"sip_payload", luasofia_proxy_get_pointer, offsetof(sip_t, sip_payload), 0},
{"sip_multipart", luasofia_proxy_get_pointer, offsetof(sip_t, sip_multipart), 0},
{NULL, NULL, 0 }
};

static int luasofia_sip_get_proxy(lua_State *L)
{
    return luasofia_proxy_create(L, SIP_TABLE_NAME);
}

#endif //__LUASOFIA_SIP_PRIVATE_H__
