package="LuaSofia"
version="0.1.7-1"
source = {
   url = "http://downloads.sourceforge.net/project/luasofia/luasofia-0.1.7.tar.gz",
   md5 = "d40806ee567dfed35a21226569e6ced2",
}
description = {
   summary  = "LuaSofia is a Lua binding of Sofia-Sip library",
   detailed = 
              [[ 
                  Sofia-SIP is an open-source SIP User-Agent library, compliant with the IETF RFC3261 specification. 
                  It can be used as a building block for SIP client software for uses such as VoIP, IM, and many other 
                  real-time and person-to-person communication services. The primary target platform for LuaSofia is GNU/Linux.
              ]],
   homepage = "http://wiki.github.com/ppizarro/luasofia",
   license  = "GNU LGPL"
}
dependencies = {
   "lua >= 5.1"
}

external_dependencies = {
   LIBSOFIASIP = {
      -- This is a hint to help luarocks finding the include dir.
      header = "sofia-sip/sip.h"
   }
}


build = {
   type = "builtin",

   modules = {
       -- C modules can span multiple files.
       sofia             = {"src/luasofia.c", "src/utils/luasofia_userdata_table.c",
                            "src/utils/luasofia_tags.c", "src/utils/luasofia_proxy.c", 
                            "src/utils/luasofia_log.c",  "src/utils/luasofia_const.c",
                            libraries = {"sofia-sip-ua"},
                            incdirs = {"$(LIBSOFIASIP_INCDIR)"},
                            libdirs = {"$(LIBSOFIASIP_LIBDIR)"}
                           },

       ["sofia.sdp"]     = {"src/sdp/luasofia_sdp.c", "src/sdp/luasofia_sdp_parser.c"},

       ["sofia.nta"]     = {"src/nta/luasofia_nta.c", "src/nta/luasofia_nta_agent.c"},

       ["sofia.nua"]     = {"src/nua/luasofia_nua_handle.c", "src/nua/luasofia_nua.c"},

       ["sofia.msg"]     = "src/msg/luasofia_msg.c",

       ["sofia.sip"]     = "src/sip/luasofia_sip.c",

       ["sofia.soa"]     = "src/soa/luasofia_soa.c",

       ["sofia.su"]      = { "src/su/luasofia_su_timer.c", "src/su/luasofia_su_task.c", 
                             "src/su/luasofia_su_tags.c", "src/su/luasofia_su_root.c",
                             "src/su/luasofia_su.c" },

       ["sofia.su_glib"] = { "src/su_glib/luasofia_su_glib_root.c", "src/su_glib/luasofia_su_glib.c"},

       ["sofia.tport"]   = "src/tport/luasofia_tport.c",

       ["sofia.url"]     = "src/url/luasofia_url.c"
    }
}

