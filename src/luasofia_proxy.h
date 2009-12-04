/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_PROXY_H__
#define __LUASOFIA_PROXY_H__

typedef int (*struct_func) (lua_State *L, void *v);

/* member info for get and set handlers */
typedef struct luasofia_proxy_info_s {
    const char *name;  /* member name */
    struct_func get_func;  /* get function for type of member */
    size_t offset;     /* offset of member within struct */
    int lenght;        /* fixed array size. Example: int point[2]  */
} luasofia_proxy_info_t;

int luasofia_proxy_create_info_table(lua_State *L, const luasofia_proxy_info_t *l);

int luasofia_proxy_create(lua_State *L);

int luasofia_proxy_register_meta(lua_State *L);

int luasofia_proxy_get_int(lua_State *L, void *v);

int luasofia_proxy_get_number(lua_State *L, void *v);

int luasofia_proxy_get_string(lua_State *L, void *v);

int luasofia_proxy_get_short(lua_State *L, void *v);

int luasofia_proxy_get_char(lua_State *L, void *v);

int luasofia_proxy_get_pointer(lua_State *L, void *v);

int luasofia_proxy_get_address (lua_State *L, void *v);

#endif //__LUASOFIA_PROXY_H__

