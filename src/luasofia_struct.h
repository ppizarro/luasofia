/* vim: set ts=8 et sw=4 sta ai cin: */
#ifndef __LUASOFIA_STRUCT_H__
#define __LUASOFIA_STRUCT_H__

typedef int (*struct_func) (lua_State *L, void *v);

/* member info for get and set handlers */
typedef struct luasofia_struct_info_s {
    const char *name;  /* member name */
    struct_func get_func;  /* get function for type of member */
    size_t offset;     /* offset of member within struct */
    int lenght;        /* fixed array size. Example: int point[2]  */
} luasofia_struct_info_t;

int luasofia_struct_create_info_table(lua_State *L, const luasofia_struct_info_t *l);

int luasofia_struct_create(lua_State *L);

int luasofia_register_struct_meta(lua_State *L);

int luasofia_struct_get_int(lua_State *L, void *v);

int luasofia_struct_get_number(lua_State *L, void *v);

int luasofia_struct_get_string(lua_State *L, void *v);

int luasofia_struct_get_short(lua_State *L, void *v);

int luasofia_struct_get_char(lua_State *L, void *v);

int luasofia_struct_get_pointer(lua_State *L, void *v);

int luasofia_struct_get_address (lua_State *L, void *v);

#endif //__LUASOFIA_STRUCT_H__

