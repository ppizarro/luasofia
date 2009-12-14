/* vim: set ts=8 et sw=4 sta ai cin: */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia.h"
#include "utils/luasofia_tags.h"   /* Needed by the tags system used on the bind */
#include "utils/luasofia_const.h"  /* Needed by the enum system used on the bind */
#include "utils/luasofia_proxy.h"  /* Needed by the proxy pattern used on the bind. See: http://en.wikipedia.org/wiki/Proxy_pattern */

#include "luasofia_example_proxy_private.h" /* The proxy example, it is good practice to make it as a private data, it should only be used on the module it is registered */
/* 
   This is an example of how to build a new module on luasofia, it tries to describe how to use every facility that
   luasofia offers to anyone who wants to extend luasofia, binding more Sofia code. It explains:
   - how to register enumerators to use on lua code. 
   - how to register the Sofia Tags, so it can be used on lua code.
   - how to build proxy to Sofia objects that cant be completely copied to lua as full userdata.
   - how to build full userdata that has its own methods and its own __gc method.
   
   We used the ideas given on the book Programming in Lua, chapters 24-29, on how to bind C code to Lua. Reading this chapters is recommended.
   But because of some features and designs of Sofia, some tweaks had to be made on the glue code (the proxy for example).
   
   This code is not intended to compile as it is, it will need some small modifications, but is a good place to start (probably only some names and includes will generate erros). 
*/

/* Module function, all the functions must have this same signature. See lua documentation for details. */
static int luasofia_example_func(lua_State* L)
{
    // Does nothing
    return 0;
}

/* This structure defines the functions that will exist on the module, using lua standard mecanism. */
static const luaL_Reg example_lib[] = {
    {"example_func"      , luasofia_example_func},      // usually is defined inside the own module
    {"get_proxy_example" , luasofia_example_get_proxy}, // usually is defined on the header of the proxy, see the luasofia_example_proxy_private.h
    {NULL, NULL}
};

/* This structure defines the Sofia tags that will be registered to be used on lua code, here we 
   will not see in details how to use the tags on lua code, only the registering system.
   It is composed of name/Sofia tag class pairs */
static const luasofia_tag_reg_t example_tags[] = {
    // {"NUTAG_ADDRESS", nutag_address } - Maps the name NUTAG_ADDRESS with the Sofia class that represents the tags, The name is recommended to be the same used on the Sofia Tag macros.
    { NULL, NULL}
};

/* This structure defines the enums that will be registered to be used on lua code.
   It is composed of name/enum pairs */
static const luasofia_reg_const_t example_constants[] = {
    // {"sdp_net_x",  sdp_net_x} -  here we are mapping the lua name example.sdp_net_x to sofia enum sdp_net_x.
    {NULL,NULL}
};

/* 
  The open function, this function is called when a require "luasofia.example" is called on lua code.
  It must do all the initialization work
*/
int luaopen_luasofia_example(lua_State *L)
{
    luaopen_luasofia(L);

    /* luasofia[example] = table */
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "example");
    luaL_register(L, NULL, example_lib);

    /* Register the tags on the luasofia tag system */
    luasofia_tags_register_tags(L, example_tags);

    /* Register the info table of the given proxy. The name of the proxy must be unique, 
       duplicated names will generate unexpected behaviour, including segmentation fault */
    luasofia_proxy_register_info_table(L, EXAMPLE_TABLE_NAME, example_info);

    /* Register the constants on the luasofia constants system */
    luasofia_const_register_constants(L, example_constants);
    
    /* The main module must register all the full userdata that is part of this module, so every
       full userdata must have its own register_meta function, that must be called here */
    luasofia_example_obj_register_meta(L);

    return 1;
}

