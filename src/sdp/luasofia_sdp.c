/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "luasofia_tags.h"
#include "luasofia_utils.h"
#include "luasofia_proxy.h"

#include <sofia-sip/sdp.h>
#include <sofia-sip/sdp_tag.h>

#include "luasofia_sdp_session_private.h"
#include "luasofia_sdp_attribute_private.h"
#include "luasofia_sdp_bandwidth_private.h"
#include "luasofia_sdp_connection_private.h"

static const luaL_Reg sdp_lib[] = {
    {"get_proxy_session",    luasofia_sdp_get_proxy_session},
    {"get_proxy_attribute" , luasofia_sdp_get_proxy_attribute},
    {"get_proxy_bandwidth" , luasofia_sdp_get_proxy_bandwidth},
    {"get_proxy_connection" ,luasofia_sdp_get_proxy_connection},
    {NULL, NULL}
};

static const luasofia_tag_reg_t sdp_tags[] = {
    { NULL, NULL}
};

static const luasofia_reg_const_t sdp_constants[] = {
    {"sdp_net_x",  sdp_net_x},
    {"sdp_net_in", sdp_net_in},
    {"sdp_addr_x", sdp_addr_x},
    {"sdp_addr_ip4", sdp_addr_ip4},
    {"sdp_addr_ip6", sdp_addr_ip6},
    {"sdp_bw_x", sdp_bw_x},
    {"sdp_bw_ct", sdp_bw_ct},
    {"sdp_bw_as", sdp_bw_as},
    {"sdp_media_x", sdp_media_x},
    {"sdp_media_any", sdp_media_any},
    {"sdp_media_audio", sdp_media_audio},
    {"sdp_media_video", sdp_media_video},
    {"sdp_media_application", sdp_media_application},
    {"sdp_media_data", sdp_media_data},
    {"sdp_media_control", sdp_media_control},
    {"sdp_media_message", sdp_media_message},
    {"sdp_media_image", sdp_media_image},
    {"sdp_media_red", sdp_media_red},
    {"sdp_proto_x", sdp_proto_x},
    {"sdp_proto_tcp", sdp_proto_tcp},
    {"sdp_proto_udp", sdp_proto_udp},
    {"sdp_proto_rtp", sdp_proto_rtp},
    {"sdp_proto_srtp", sdp_proto_srtp},
    {"sdp_proto_udptl", sdp_proto_udptl},
    {"sdp_proto_tls", sdp_proto_tls},
    {"sdp_proto_any", sdp_proto_any},
    {"sdp_inactive", sdp_inactive},
    {"sdp_sendonly", sdp_sendonly},
    {"sdp_recvonly", sdp_recvonly},
    {"sdp_sendrecv", sdp_sendrecv},
    {"sdp_f_strict", sdp_f_strict},
    {"sdp_f_anynet", sdp_f_anynet},
    {"sdp_f_realloc",sdp_f_realloc},
    {"sdp_f_all_rtpmaps", sdp_f_all_rtpmaps},
    {"sdp_f_print_prefix",sdp_f_print_prefix},
    {"sdp_f_mode_0000", sdp_f_mode_0000},
    {"sdp_f_insane", sdp_f_insane},
    {"sdp_f_c_missing", sdp_f_c_missing},
    {"sdp_f_config", sdp_f_config},
    {"sdp_f_mode_manual", sdp_f_mode_manual},
    {"sdp_f_mode_always", sdp_f_mode_always},
    {NULL, 0 }
};

int luaopen_luasofia_sdp(lua_State *L)
{
    luaopen_luasofia(L);

    /* luasofia[sdp] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "sdp");
    luaL_register(L, NULL, sdp_lib);

    luasofia_tags_register(L, sdp_tags);

    luasofia_proxy_register_info_table(L, SDP_SESSION_TABLE_NAME,   sdp_session_info);    
    luasofia_proxy_register_info_table(L, SDP_ATTRIBUTE_TABLE_NAME, sdp_attribute_info);    
    luasofia_proxy_register_info_table(L, SDP_BANDWIDTH_TABLE_NAME, sdp_bandwidth_info);
    luasofia_proxy_register_info_table(L, SDP_CONNECTION_TABLE_NAME,sdp_connection_info);

    luasofia_register_constants(L, sdp_constants);

    return 1;
}

