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

#ifndef __LUASOFIA_EXAMPLE_PRIVATE_H__
#define __LUASOFIA_EXAMPLE_PRIVATE_H__

/* The name of the info table of the structure, this name will be used to index 
   the info table inside the global proxy register system, it must be unique*/
#define EXAMPLE_TABLE_NAME "luasofia_example_unique_name_t"

/* Dummy structure */
typedef struct foo_s {
    char* name;
    int   size;
    double real_size;
    void*  raw_data;
    int    boolean;
}foo_t;

/* 
  This structure has 4 fields, it is a way of acessing the fields of a C structure inside lua.
  This is not the recomended way to do this, it is not safe, but copying the entire structure is
  not always possible. There is a series of already made functions that converts the adress of
  the field to a lua value and pushes it to the lua stack, you must basically define a structure
  for each field you want to acess on your structure, tou must the inform the name you want to use
  on lua to acess it, the bind function that will push the value to lua for you and the adress
  of that field, that can be calculated with the offsetof function. The fourth element is rarelly used,
  it is used to acess members on structures that have fixed size, like a char array[40], 
  this feature is not completely implemented yet.
  The proxy generated using this method will not be collected by the lua gc and there is no way
  to know how much time the proxy will be available on memory (Dependes on when sofia will free it).
  For further information about luasofia_proxy_info_t see the luasofia_proxy.h documentation
*/
static const luasofia_proxy_info_t example_info[] = {
{"name",      luasofia_proxy_get_string,  offsetof(foo_t, name),      0},
{"size",      luasofia_proxy_get_int,     offsetof(foo_t, size),      0},
{"real_size", luasofia_proxy_get_number,  offsetof(foo_t, real_size), 0},
{"raw_data",  luasofia_proxy_get_pointer, offsetof(foo_t, raw_data),  0},
{"boolean",   luasofia_proxy_get_boolean, offsetof(foo_t, boolean),   0},
{NULL, NULL, 0 }
};

/* The function that puts the proxy on the stack, luasofia_proxy already does all the job for you, just put the name of your proxy. */
static int luasofia_example_get_proxy(lua_State *L)
{
    return luasofia_proxy_create(L, EXAMPLE_TABLE_NAME);
}

#endif /* __LUASOFIA_EXAMPLE_PRIVATE_H__ */

