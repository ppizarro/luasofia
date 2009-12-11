/* vim: set ts=8 et sw=4 sta ai cin: */
#include <string.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "luasofia_tags.h"
#include "luasofia_const.h"
#include "luasofia_proxy.h"
#include "luasofia_su_home.h"

#include <sofia-sip/sdp.h>
#include <sofia-sip/sdp_tag.h>

#include "luasofia_sdp_session_private.h"
#include "luasofia_sdp_attribute_private.h"
#include "luasofia_sdp_bandwidth_private.h"
#include "luasofia_sdp_connection_private.h"
#include "luasofia_sdp_key_private.h"
#include "luasofia_sdp_media_private.h"
#include "luasofia_sdp_rtpmap_private.h"
#include "luasofia_sdp_list_private.h"
#include "luasofia_sdp_origin_private.h"
#include "luasofia_sdp_repeat_private.h"
#include "luasofia_sdp_time_private.h"


static int luasofia_sdp_parse(lua_State *L)
{
    /* get and check first argument (should be a luasofia_su_home_t userdata) */
    luasofia_su_home_t *home = (luasofia_su_home_t*) luaL_checkudata(L, 1, SU_HOME_MTABLE);
    /* get and check second argument (should be a string) */
    const char* msg = luaL_checkstring (L, 2);
    issize_t size   = (issize_t) strlen(msg);
    /* get and check third argument (should be a integer) */
    int flags = (int) luaL_checkinteger(L, 3);
    sdp_parser_t* parser = sdp_parse(home->home, msg, size, flags);  	
    
    lua_pop(L, 3);
    if(!parser)
        return 0;

   /* WTH is a sdp_parser_t ? Sofia just defines it as typedef struct sdp_parser_s sdp_parser_t.... 
      _|_ Sofia and its odd coding styles... returning it as lightuserdata... i wanted to return 
      the sdp_session lightuserdata and proxy it later. */
   lua_pushlightuserdata (L, parser);

   return 1; 
}


static const luaL_Reg sdp_lib[] = {
    {"parse"                , luasofia_sdp_parse},
    {"get_proxy_session"    , luasofia_sdp_get_proxy_session},
    {"get_proxy_attribute"  , luasofia_sdp_get_proxy_attribute},
    {"get_proxy_bandwidth"  , luasofia_sdp_get_proxy_bandwidth},
    {"get_proxy_connection" , luasofia_sdp_get_proxy_connection},
    {"get_proxy_key"        , luasofia_sdp_get_proxy_key},
    {"get_proxy_media"      , luasofia_sdp_get_proxy_media},
    {"get_proxy_rtpmap"     , luasofia_sdp_get_proxy_rtpmap},
    {"get_proxy_list"       , luasofia_sdp_get_proxy_list},
    {"get_proxy_origin"     , luasofia_sdp_get_proxy_origin},
    {"get_proxy_repeat"     , luasofia_sdp_get_proxy_repeat},
    {"get_proxy_time"       , luasofia_sdp_get_proxy_time},
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

    luasofia_tags_register_tags(L, sdp_tags);

    luasofia_proxy_register_info_table(L, SDP_SESSION_TABLE_NAME,   sdp_session_info);    
    luasofia_proxy_register_info_table(L, SDP_ATTRIBUTE_TABLE_NAME, sdp_attribute_info);    
    luasofia_proxy_register_info_table(L, SDP_BANDWIDTH_TABLE_NAME, sdp_bandwidth_info);
    luasofia_proxy_register_info_table(L, SDP_CONNECTION_TABLE_NAME,sdp_connection_info);
    luasofia_proxy_register_info_table(L, SDP_KEY_TABLE_NAME,       sdp_key_info);
    luasofia_proxy_register_info_table(L, SDP_MEDIA_TABLE_NAME,     sdp_media_info);
    luasofia_proxy_register_info_table(L, SDP_RTPMAP_TABLE_NAME,    sdp_rtpmap_info);
    luasofia_proxy_register_info_table(L, SDP_LIST_TABLE_NAME,      sdp_list_info);
    luasofia_proxy_register_info_table(L, SDP_REPEAT_TABLE_NAME,    sdp_repeat_info);
    luasofia_proxy_register_info_table(L, SDP_ORIGIN_TABLE_NAME,    sdp_origin_info);
    luasofia_proxy_register_info_table(L, SDP_TIME_TABLE_NAME,      sdp_time_info);

    luasofia_const_register_constants(L, sdp_constants);

    return 1;
}

