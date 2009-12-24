lib_LTLIBRARIES = libluasofia.la

libluasofia_la_CFLAGS = -Wall -I@includedir@ $(SOFIA_SIP_UA_CFLAGS) $(LUA_CFLAGS)

libluasofia_la_LDFLAGS = -L@libdir@ $(SOFIA_SIP_UA_LIBS) $(LUA_LIBS)

libluasofia_la_SOURCES = luasofia.c \
	luasofia.h \
	nua/luasofia_nua.c \
	nua/luasofia_nua_handle.c \
	nua/luasofia_nua_handle.h \
	sdp/luasofia_sdp_attribute_private.h \
	sdp/luasofia_sdp_connection_private.h \
	sdp/luasofia_sdp_media_private.h \
	sdp/luasofia_sdp_parser.h \
	sdp/luasofia_sdp_session_private.h \
	sdp/luasofia_sdp_bandwidth_private.h \
	sdp/luasofia_sdp_key_private.h \
	sdp/luasofia_sdp_origin_private.h \
	sdp/luasofia_sdp_repeat_private.h \
	sdp/luasofia_sdp_time_private.h \
	sdp/luasofia_sdp.c \
	sdp/luasofia_sdp_list_private.h \
	sdp/luasofia_sdp_parser.c \
	sdp/luasofia_sdp_rtpmap_private.h \
        sip/luasofia_sip_addr_private.h \
	sip/luasofia_sip_contact_private.h \
	sip/luasofia_sip_private.h \
	sip/luasofia_sip_status_private.h \
	sip/luasofia_sip.c \
	sip/luasofia_sip_event_private.h \
	sip/luasofia_sip_request_private.h \
	sip/luasofia_sip_via_private.h \
	sip/luasofia_sip_accept_private.h \
	sip/luasofia_sip_allow_private.h \
	sip/luasofia_sip_call_id_private.h \
	sip/luasofia_sip_content_length_private.h \
	sip/luasofia_sip_content_type_private.h \
	soa/luasofia_soa.c \
	su/luasofia_su.c \
	su/luasofia_su_root.h \
	su/luasofia_su_tags.h \
	su/luasofia_su_task.h \
	su/luasofia_su_timer.h \
	su/luasofia_su_root.c \
	su/luasofia_su_tags.c \
	su/luasofia_su_task.c \
	su/luasofia_su_timer.c \
	url/luasofia_url.c \
	utils/luasofia_const.c \
	utils/luasofia_const.h \
	utils/luasofia_proxy.c \
	utils/luasofia_proxy.h \
	utils/luasofia_tags.c \
	utils/luasofia_tags.h \
	utils/luasofia_utils.c \
	utils/luasofia_utils.h \
	utils/luasofia_weak_table.c \
	utils/luasofia_weak_table.h

install-exec-hook:
	ln -s -f @libdir@/libluasofia.so @LUA_CMODULE@/luasofia.so

