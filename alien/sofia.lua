require "luarocks.require"
require "alien"

sofia = alien.load("/usr/local/lib/libsofia-sip-ua.so.0")

-- su

sofia.su_init:types("int")
sofia.su_deinit:types("void")

-- su_time

su_time_t = alien.defstruct{
  { "tv_sec",  "ulong" },
  { "tv_usec", "ulong" },
}

sofia.su_time:types("void","pointer")
sofia.su_time_print:types("int","string","int","pointer")

-- su_root

sofia.su_root_create:types("pointer","pointer")      
sofia.su_root_name:types("string","pointer")      

