/* vim: set ts=8 et sw=4 sta ai cin: */
/*
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

/** 
    Create the Luasofia Tags table, must be called ONLY once, it is already called by Luasofia main module, never use this.
    @param L - The Lua state.
*/
void luasofia_tags_create(lua_State *L);

/** 
    Register an array of tags on Luasofia Tags table.
    @param L     - The Lua state.
    @param tags  - NULL terminated array of tags to be registered on Luasofia Tags table.
*/
void luasofia_tags_register_tags(lua_State *L, const luasofia_tag_reg_t *tags);

/** 
    Converts a Luasofia Tags table to a Sofia-SIP tag list.
    @param L      - The Lua state.
    @param index  - The position of the Tags table on the stack.
    @param home   - Sofia su_home_t.
    @return         The Sofia-SIP tag list, or an error if something goes wrong.
*/
tagi_t* luasofia_tags_table_to_taglist(lua_State *L, int index, su_home_t *home);

/** 
    Given a tag (on the top of the stack) gets it type, if the tag is found on the Tags table.
    @param   L - Lua state.
    @return      The type of the given tag or an error if it unable to find it on the Tags table.
*/
tag_type_t luasofia_tags_find(lua_State *L);

#endif //__LUASOFIA_TAGS

