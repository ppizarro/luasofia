/* vim: set ts=8 et sw=4 sta ai cin: */
/*
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

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "utils/luasofia_weak_table.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"
#include "nta/luasofia_nta_agent.h"

#include <sofia-sip/nta_tag.h>


static const luaL_Reg nta_lib[] = {
    {"agent_create", luasofia_nta_agent_create},
    {NULL, NULL}
};

static const luasofia_tag_reg_t nta_tags[] = {
    { "NTATAG_ANY", ntatag_any },
    { "NTATAG_MCLASS", ntatag_mclass },
    { "NTATAG_BAD_REQ_MASK", ntatag_bad_req_mask },
    { "NTATAG_BAD_RESP_MASK", ntatag_bad_resp_mask },
    { "NTATAG_DEFAULT_PROXY", ntatag_default_proxy },
    { "NTATAG_CONTACT", ntatag_contact },
    { "NTATAG_TARGET", ntatag_target },
    { "NTATAG_ALIASES", ntatag_aliases },
    { "NTATAG_BRANCH_KEY", ntatag_branch_key },
    { "NTATAG_ACK_BRANCH", ntatag_ack_branch },
    { "NTATAG_COMP", ntatag_comp },
    { "NTATAG_MSG", ntatag_msg },
    { "NTATAG_TPORT", ntatag_tport },
    { "NTATAG_REMOTE_CSEQ", ntatag_remote_cseq },
    { "NTATAG_SMIME", ntatag_smime },
    { "NTATAG_MAXSIZE", ntatag_maxsize },
    { "NTATAG_UDP_MTU", ntatag_udp_mtu },
    { "NTATAG_MAX_PROCEEDING", ntatag_max_proceeding },
    { "NTATAG_MAX_FORWARDS", ntatag_max_forwards },
    { "NTATAG_SIP_T1", ntatag_sip_t1 },
    { "NTATAG_SIP_T1X64", ntatag_sip_t1x64 },
    { "NTATAG_SIP_T2", ntatag_sip_t2 },
    { "NTATAG_SIP_T4", ntatag_sip_t4 },
    { "NTATAG_PROGRESS", ntatag_progress },
    { "NTATAG_TIMER_C", ntatag_timer_c },
    { "NTATAG_GRAYLIST", ntatag_graylist },
    { "NTATAG_BLACKLIST", ntatag_blacklist },
    { "NTATAG_DEBUG_DROP_PROB", ntatag_debug_drop_prob },
    { "NTATAG_SIGCOMP_OPTIONS", ntatag_sigcomp_options },
    { "NTATAG_SIGCOMP_CLOSE", ntatag_sigcomp_close },
    { "NTATAG_SIGCOMP_AWARE", ntatag_sigcomp_aware },
    { "NTATAG_SIGCOMP_ALGORITHM", ntatag_sigcomp_algorithm },
    { "NTATAG_UA", ntatag_ua },
    { "NTATAG_STATELESS", ntatag_stateless },
    { "NTATAG_USER_VIA", ntatag_user_via },
    { "NTATAG_EXTRA_100", ntatag_extra_100 },
    { "NTATAG_PASS_100", ntatag_pass_100 },
    { "NTATAG_TIMEOUT_408", ntatag_timeout_408 },
    { "NTATAG_PASS_408", ntatag_pass_408 },
    { "NTATAG_NO_DIALOG", ntatag_no_dialog },
    { "NTATAG_MERGE_482", ntatag_merge_482 },
    { "NTATAG_CANCEL_2543", ntatag_cancel_2543 },
    { "NTATAG_CANCEL_408", ntatag_cancel_408 },
    { "NTATAG_TAG_3261", ntatag_tag_3261 },
    { "NTATAG_USE_TIMESTAMP", ntatag_use_timestamp },
    { "NTATAG_METHOD", ntatag_method },
    { "NTATAG_CANCEL_487", ntatag_cancel_487 },
    { "NTATAG_REL100", ntatag_rel100 },
    { "NTATAG_SIPFLAGS", ntatag_sipflags },
    { "NTATAG_CLIENT_RPORT", ntatag_client_rport },
    { "NTATAG_RPORT", ntatag_client_rport },
    { "NTATAG_SERVER_RPORT", ntatag_server_rport },
    { "NTATAG_TCP_RPORT", ntatag_tcp_rport },
    { "NTATAG_TLS_RPORT", ntatag_tls_rport },
    { "NTATAG_PRELOAD", ntatag_preload },
    { "NTATAG_USE_NAPTR", ntatag_use_naptr },
    { "NTATAG_USE_SRV", ntatag_use_srv },
    { "NTATAG_RSEQ", ntatag_rseq },
    { "NTATAG_S_IRQ_HASH", ntatag_s_irq_hash },
    { "NTATAG_S_ORQ_HASH", ntatag_s_orq_hash },
    { "NTATAG_S_LEG_HASH", ntatag_s_leg_hash },
    { "NTATAG_S_IRQ_HASH_USED", ntatag_s_irq_hash_used },
    { "NTATAG_S_ORQ_HASH_USED", ntatag_s_orq_hash_used },
    { "NTATAG_S_LEG_HASH_USED", ntatag_s_leg_hash_used },
    { "NTATAG_S_RECV_MSG", ntatag_s_recv_msg },
    { "NTATAG_S_RECV_REQUEST", ntatag_s_recv_request },
    { "NTATAG_S_RECV_RESPONSE", ntatag_s_recv_response },
    { "NTATAG_S_BAD_MESSAGE", ntatag_s_bad_message },
    { "NTATAG_S_BAD_REQUEST", ntatag_s_bad_request },
    { "NTATAG_S_BAD_RESPONSE", ntatag_s_bad_response },
    { "NTATAG_S_DROP_REQUEST", ntatag_s_drop_request },
    { "NTATAG_S_DROP_RESPONSE", ntatag_s_drop_response },
    { "NTATAG_S_CLIENT_TR", ntatag_s_client_tr },
    { "NTATAG_S_SERVER_TR", ntatag_s_server_tr },
    { "NTATAG_S_DIALOG_TR", ntatag_s_dialog_tr },
    { "NTATAG_S_ACKED_TR", ntatag_s_acked_tr },
    { "NTATAG_S_CANCELED_TR", ntatag_s_canceled_tr },
    { "NTATAG_S_TRLESS_REQUEST", ntatag_s_trless_request },
    { "NTATAG_S_TRLESS_TO_TR", ntatag_s_trless_to_tr },
    { "NTATAG_S_TRLESS_RESPONSE", ntatag_s_trless_response },
    { "NTATAG_S_TRLESS_200", ntatag_s_trless_200 },
    { "NTATAG_S_MERGED_REQUEST", ntatag_s_merged_request },
    { "NTATAG_S_SENT_MSG", ntatag_s_sent_msg },
    { "NTATAG_S_SENT_REQUEST", ntatag_s_sent_request },
    { "NTATAG_S_SENT_RESPONSE", ntatag_s_sent_response },
    { "NTATAG_S_RETRY_REQUEST", ntatag_s_retry_request },
    { "NTATAG_S_RETRY_RESPONSE", ntatag_s_retry_response },
    { "NTATAG_S_RECV_RETRY", ntatag_s_recv_retry },
    { "NTATAG_S_TOUT_REQUEST", ntatag_s_tout_request },
    { "NTATAG_S_TOUT_RESPONSE", ntatag_s_tout_response },
    { NULL, NULL}
};

static const luasofia_reg_const_t nta_constants[] = {
    {NULL, 0 }
};

int luaopen_sofia_nta(lua_State *L)
{
    luaopen_sofia(L);

    luasofia_tags_register_tags(L, nta_tags);
    luasofia_nta_agent_register_meta(L);

    /* sofia[nta] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "nta");
    luaL_register(L, NULL, nta_lib);

    luasofia_const_register_constants(L, nta_constants);

    return 1;
}

