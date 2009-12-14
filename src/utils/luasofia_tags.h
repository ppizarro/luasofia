/* vim: set ts=8 et sw=4 sta ai cin: */
/*
 * Copyright (C) 2009 Digitro Corporation <www.digitro.com.br>
 *
 * @author Paulo Pizarro  <paulo.pizarro@gmail.com>
 * @author Tiago Katcipis <tiagokatcipis@gmail.com>
 *
 * This file is part of Luasofia.
 *
 * Luasofia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Luasofia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LUASOFIA_TAGS_H__
#define __LUASOFIA_TAGS_H__

#include <sofia-sip/su_tag.h>

typedef struct luasofia_tag_reg_s {
  const char *tag_name;
  tag_type_t t_tag;
} luasofia_tag_reg_t;

void luasofia_tags_create(lua_State *L);

void luasofia_tags_register_tags(lua_State *L, const luasofia_tag_reg_t *tags);

tagi_t* luasofia_tags_table_to_taglist(lua_State *L, int index, su_home_t *home);

tag_type_t luasofia_tags_find(lua_State *L);

#endif //__LUASOFIA_TAGS

