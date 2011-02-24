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

build = {
   type = "command",
   build_command = "LUA_CMODULE=$(PREFIX)/lib ./configure --prefix=$(PREFIX) --libdir=$(PREFIX)/lib_version && make",
   install_command = "make install",
}
