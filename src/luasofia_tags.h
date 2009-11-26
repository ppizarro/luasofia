/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_TAGS_H__
#define __LUASOFIA_TAGS_H__

#include <sofia-sip/su_tag.h>

typedef struct luasofia_tag_reg_s {
  const char *tag_name;
  tag_type_t tag;
} luasofia_tag_reg_t;

void luasofia_tags_register(lua_State *L, const luasofia_tag_reg_t *tags);

#endif //__LUASOFIA_TAGS

