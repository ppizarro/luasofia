

lib_LTLIBRARIES = liblua@LUA_VERSION@-sofia.la liblua@LUA_VERSION@-sofia-glib.la

liblua@LUA_VERSION@_sofia_la_CFLAGS = -Werror -Wall $(SOFIA_SIP_UA_CFLAGS) $(LUA_CFLAGS) -I@includedir@

liblua@LUA_VERSION@_sofia_la_LDFLAGS = -L@libdir@ $(SOFIA_SIP_UA_LIBS) -version-info @LT_VERSION@

liblua@LUA_VERSION@_sofia_la_SOURCES = luasofia.c \
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
	sip/luasofia_sip_authenticate_private.h \
	sip/luasofia_sip_subscription_state_private.h \
	sip/luasofia_sip_msg_payload_private.h \
	soa/luasofia_soa.c \
	tport/luasofia_tport.c \
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
	nta/luasofia_nta.c \
	nta/luasofia_nta_agent.c\
	nta/luasofia_nta_agent.h\
	msg/luasofia_msg.c \
	utils/luasofia_const.c \
	utils/luasofia_const.h \
	utils/luasofia_proxy.c \
	utils/luasofia_proxy.h \
	utils/luasofia_tags.c \
	utils/luasofia_tags.h \
	utils/luasofia_log.c \
	utils/luasofia_log.h \
	utils/luasofia_userdata_table.c \
	utils/luasofia_userdata_table.h


liblua@LUA_VERSION@_sofia_glib_la_CFLAGS = -Wall $(SOFIA_SIP_UA_GLIB_CFLAGS) $(LUA_CFLAGS) -I@includedir@

liblua@LUA_VERSION@_sofia_glib_la_LDFLAGS = -L@libdir@ $(SOFIA_SIP_UA_GLIB_LIBS) -version-info @LT_VERSION@

liblua@LUA_VERSION@_sofia_glib_la_LIBADD = liblua@LUA_VERSION@-sofia.la

liblua@LUA_VERSION@_sofia_glib_la_SOURCES = su_glib/luasofia_su_glib.c \
        su_glib/luasofia_su_glib_root.h \
        su_glib/luasofia_su_glib_root.c

install-exec-hook:
	mkdir -p @LUA_CMODULE@/sofia
	ln -s -f @libdir@/liblua@LUA_VERSION@-sofia.so @LUA_CMODULE@/sofia.so
	ln -s -f @libdir@/liblua@LUA_VERSION@-sofia-glib.so @LUA_CMODULE@/sofia/glib.so

uninstall-hook:
	rm -f @LUA_CMODULE@/sofia.so
	rm -rf @LUA_CMODULE@/sofia

