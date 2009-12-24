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

#ifndef __LUASOFIA_PROXY_H__
#define __LUASOFIA_PROXY_H__

/** 
    \file luasofia_proxy.h
    Module that defines the structure and functions used on the proxy system used on the luasofia.
*/

typedef int (*struct_func) (lua_State *L, void *v);

/** member info for get handlers */
typedef struct luasofia_proxy_info_s {
    const char *name;     /** member name */
    struct_func get_func; /** get function for type of member */
    size_t offset;        /** offset of member within struct */
    int lenght;           /** fixed array size. Example: int point[2]  */
} luasofia_proxy_info_t;

/**
    Initializes internal data, must be called only once on the luasofia main module open function. 
    @param L:
*/
void luasofia_proxy_init(lua_State *L);

/**
    Register at the internal proxy table a new entry for a new proxy, the name of 
    the proxy will be the key and the info_table will be the value mapped.
    @param L:           lua_State
    @param name:        The name of the proxy object registering his info table, must be unique.
    @param info_table:  The info_table holding the information about the proxy.
    @return:            Always zero, it only registers the info_table, wont change the stack.
*/
int luasofia_proxy_register_info_table(lua_State *L, const char* name, const luasofia_proxy_info_t *info_table);

/** 
    Creates a proxy for the lighuserdata already on the lua_State stack, defining wich fields are accessible on the proxy.
    @param L:    lua_State, on the top of the stack MUST be a lighuserdata.
    @param name: The proxy name, if the info_table of this name has not been registered an error will occur. 
                 If the name of the proxy is not compatible with the lighuserdata at the stack...nasty things will happen. 
    @return:     Always 1, indicating that the proxy full userdata has been pushed at the lua_State L stack.
*/
int luasofia_proxy_create(lua_State *L, const char* name);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the int that was been pointed by the address v (int i = *(int*)v), pushed on the stack. 
*/
int luasofia_proxy_get_int(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the boolean that was been pointed by the address v (int i = *(int*)v) as lua boolean, pushed on the stack. 
*/
int luasofia_proxy_get_boolean(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the number that was been pointed by the address v (lua_Number i = *(lua_Number*)v), pushed on the stack. 
*/
int luasofia_proxy_get_number(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the string that was been pointed by the address v (lua_string s = *(char**)v), pushed on the stack. 
*/
int luasofia_proxy_get_string(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the short that was been pointed by the address v (short i = *(short*)v), pushed on the stack. 
*/
int luasofia_proxy_get_short(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the char that was been pointed by the address v, it will be pushed as a number on the stack (lua_Number i = *(char*)v). 
*/
int luasofia_proxy_get_char(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the lightuserdata that was been pointed by the address v (lighuserdata l = *((void**)v)), pushed on the stack. 
*/
int luasofia_proxy_get_pointer(lua_State *L, void *v);

/**
    @param L: lua_State
    @param v: Address of the data.
    @return:  Always returns 1, indicating the address v as lightuserdata (lightuserdata l = v), pushed on the stack. 
*/
int luasofia_proxy_get_address (lua_State *L, void *v);

#endif //__LUASOFIA_PROXY_H__

