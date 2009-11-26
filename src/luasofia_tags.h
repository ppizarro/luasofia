/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_TAGS_H__
#define __LUASOFIA_TAGS_H__

#include <sofia-sip/su_tag.h>

typedef struct luasofia_tag_reg_s {
  const char *tag_name;
  tag_type_t t_tag;
} luasofia_tag_reg_t;

void luasofia_tags_create(lua_State *L);

void luasofia_tags_register(lua_State *L, const luasofia_tag_reg_t *tags);

void luasofia_tags_table_to_taglist(lua_State *L, int index, tagi_t tags[], int maxtags);

#endif //__LUASOFIA_TAGS

