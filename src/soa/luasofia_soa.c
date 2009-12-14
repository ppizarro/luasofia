/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "utils/luasofia_tags.h"
#include "utils/luasofia_const.h"

#include <sofia-sip/soa.h>
#include <sofia-sip/soa_tag.h>

typedef struct lua_soa_session_s lua_soa_session_t;

#define SOA_SESSION_MTABLE "lua_soa_session_t"

struct lua_soa_session_s {
    soa_session_t *soa;
    lua_State *L;
};

static const luaL_Reg soa_session_meths[] = {
    {NULL, NULL}
};

static const luaL_Reg soa_lib[] = {
    {NULL, NULL}
};

static const luasofia_tag_reg_t soa_tags[] = {
    { "SOATAG_ANY", soatag_any },
    { "SOATAG_LOCAL_SDP", soatag_local_sdp },
    { "SOATAG_LOCAL_SDP_REF", soatag_local_sdp_ref },
    { "SOATAG_LOCAL_SDP_STR", soatag_local_sdp_str },
    { "SOATAG_LOCAL_SDP_STR_REF", soatag_local_sdp_str_ref },
    { "SOATAG_USER_SDP", soatag_user_sdp },
    { "SOATAG_USER_SDP_REF", soatag_user_sdp_ref },
    { "SOATAG_USER_SDP_STR", soatag_user_sdp_str },
    { "SOATAG_USER_SDP_STR_REF", soatag_user_sdp_str_ref },
    { "SOATAG_CAPS_SDP", soatag_caps_sdp },
    { "SOATAG_CAPS_SDP_REF", soatag_caps_sdp_ref },
    { "SOATAG_CAPS_SDP_STR", soatag_caps_sdp_str },
    { "SOATAG_CAPS_SDP_STR_REF", soatag_caps_sdp_str_ref },
    { "SOATAG_REMOTE_SDP", soatag_remote_sdp },
    { "SOATAG_REMOTE_SDP_REF", soatag_remote_sdp_ref },
    { "SOATAG_REMOTE_SDP_STR", soatag_remote_sdp_str },
    { "SOATAG_REMOTE_SDP_STR_REF", soatag_remote_sdp_str_ref },
    { "SOATAG_LOCAL_SDP", soatag_local_sdp },
    { "SOATAG_LOCAL_SDP_REF", soatag_local_sdp_ref },
    { "SOATAG_LOCAL_SDP_STR", soatag_local_sdp_str },
    { "SOATAG_LOCAL_SDP_STR_REF", soatag_local_sdp_str_ref },
    { "SOATAG_AF_REF", soatag_af_ref },
    { "SOATAG_ADDRESS", soatag_address },
    { "SOATAG_ADDRESS_REF", soatag_address_ref },
    { "SOATAG_RTP_SELECT", soatag_rtp_select },
    { "SOATAG_RTP_SELECT_REF", soatag_rtp_select_ref },
    { "SOATAG_AUDIO_AUX", soatag_audio_aux },
    { "SOATAG_AUDIO_AUX_REF", soatag_audio_aux_ref },
    { "SOATAG_RTP_SORT", soatag_rtp_sort },
    { "SOATAG_RTP_SORT_REF", soatag_rtp_sort_ref },
    { "SOATAG_RTP_MISMATCH", soatag_rtp_mismatch },
    { "SOATAG_RTP_MISMATCH_REF", soatag_rtp_mismatch_ref },
    { "SOATAG_ACTIVE_AUDIO", soatag_active_audio },
    { "SOATAG_ACTIVE_AUDIO_REF", soatag_active_audio_ref },
    { "SOATAG_ACTIVE_VIDEO", soatag_active_video },
    { "SOATAG_ACTIVE_VIDEO_REF", soatag_active_video_ref },
    { "SOATAG_ACTIVE_IMAGE", soatag_active_image },
    { "SOATAG_ACTIVE_IMAGE_REF", soatag_active_image_ref },
    { "SOATAG_ACTIVE_CHAT", soatag_active_chat },
    { "SOATAG_ACTIVE_CHAT_REF", soatag_active_chat_ref },
    { "SOATAG_SRTP_ENABLE", soatag_srtp_enable },
    { "SOATAG_SRTP_ENABLE_REF", soatag_srtp_enable_ref },
    { "SOATAG_SRTP_CONFIDENTIALITY", soatag_srtp_confidentiality },
    { "SOATAG_SRTP_CONFIDENTIALITY_REF", soatag_srtp_confidentiality_ref },
    { "SOATAG_SRTP_INTEGRITY", soatag_srtp_integrity },
    { "SOATAG_SRTP_INTEGRITY_REF", soatag_srtp_integrity_ref },
    { "SOATAG_HOLD", soatag_hold },
    { "SOATAG_HOLD_REF", soatag_hold_ref },
    { "SOATAG_ORDERED_USER", soatag_ordered_user },
    { "SOATAG_ORDERED_USER_REF", soatag_ordered_user_ref },
    { "SOATAG_REUSE_REJECTED", soatag_reuse_rejected },
    { "SOATAG_REUSE_REJECTED_REF", soatag_reuse_rejected_ref },
    { NULL, NULL}
};

static const luasofia_reg_const_t soa_constants[] = {
    {NULL, 0 }
};

int luaopen_luasofia_soa(lua_State *L)
{
    luaL_newmetatable(L, SOA_SESSION_MTABLE);
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, soa_session_meths);
    lua_pop(L, 1);

    luasofia_tags_register_tags(L, soa_tags);

    luaopen_luasofia(L);

    /* luasofia[soa] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "soa");
    luaL_register(L, NULL, soa_lib);

    luasofia_const_register_constants(L, soa_constants);

    return 1;
}

