/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_SDP_RTPMAP_PRIVATE_H__
#define __LUASOFIA_SDP_RTPMAP_PRIVATE_H__

#define SDP_RTPMAP_TABLE_NAME "luasofia_sdp_rtpmap_t"

static const luasofia_proxy_info_t sdp_rtpmap_info[] = {
{"rm_size",      luasofia_proxy_get_int,     offsetof(sdp_rtpmap_t, rm_size),     0},
{"rm_next",      luasofia_proxy_get_pointer, offsetof(sdp_rtpmap_t, rm_next),     0},
{"rm_encoding",  luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_encoding), 0},
{"rm_rate",      luasofia_proxy_get_int,     offsetof(sdp_rtpmap_t, rm_rate),     0},
{"rm_params",    luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_params),   0},
{"rm_fmtp",      luasofia_proxy_get_string,  offsetof(sdp_rtpmap_t, rm_fmtp),     0},
//FIXME how to acess unsigned rm_predef: 1, rm_pt: 7, rm_any: 1 ?
{NULL, NULL, 0 }
};

static int luasofia_sdp_get_proxy_rtpmap(lua_State *L)
{
    return luasofia_proxy_create(L, SDP_RTPMAP_TABLE_NAME);
}

#endif /* __LUASOFIA_SDP_RTPMAP_PRIVATE_H__ */
