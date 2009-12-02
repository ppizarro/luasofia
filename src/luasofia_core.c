/* vim: set ts=4 et sw=4 sta ai cin: */

#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "luasofia_weak_table.h"
#include "luasofia_tags.h"
#include "luasofia_struct.h"

#define LUASOFIA_BUFFER_META "luasofia_buffer"

typedef enum {
  AT_SHORT,
  AT_USHORT,
  AT_INT,
  AT_UINT,
  AT_LONG,
  AT_ULONG,
  AT_VOID,
  AT_FLOAT,
  AT_DOUBLE,
  AT_CHAR,
  AT_BYTE,
  AT_STRING,
  AT_PTR,
  AT_REFINT,
  AT_REFUINT,
  AT_REFCHAR,
  AT_REFDOUBLE,
  //AT_CALLBACK
} luasofia_Type;

/* Information to compute strucuture access */

typedef struct { char c; char x; } s_char;
typedef struct { char c; short x; } s_short;
typedef struct { char c; int x; } s_int;
typedef struct { char c; long x; } s_long;
typedef struct { char c; float x; } s_float;
typedef struct { char c; double x; } s_double;
typedef struct { char c; char *x; } s_char_p;
typedef struct { char c; void *x; } s_void_p;

#define AT_CHAR_ALIGN (sizeof(s_char) - sizeof(char))
#define AT_SHORT_ALIGN (sizeof(s_short) - sizeof(short))
#define AT_INT_ALIGN (sizeof(s_int) - sizeof(int))
#define AT_LONG_ALIGN (sizeof(s_long) - sizeof(long))
#define AT_FLOAT_ALIGN (sizeof(s_float) - sizeof(float))
#define AT_DOUBLE_ALIGN (sizeof(s_double) - sizeof(double))
#define AT_CHAR_P_ALIGN (sizeof(s_char_p) - sizeof(char*))
#define AT_VOID_P_ALIGN (sizeof(s_void_p) - sizeof(void*))

static int luasofia_sizeof(lua_State *L) {
  static const int sizes[] = {sizeof(int), sizeof(double), sizeof(unsigned char), sizeof(char*),
                              sizeof(unsigned int), sizeof(unsigned short), sizeof(unsigned long), sizeof(unsigned int*),
                              sizeof(void*), sizeof(char),
                              sizeof(short), sizeof(long), sizeof(float),
                              //sizeof(void*), sizeof(char*), sizeof(int*),
                              sizeof(char*), sizeof(int*),
                              sizeof(double*)};
  static const char *const typenames[] = {"int", "double", "char", "string",
                                          "uint", "ushort", "ulong", "ref uint",
                                          "pointer", "byte", "short", "long",
                                          //"float", "callback", "ref char",
                                          "float", "ref char",
                                          "ref int", "ref double", NULL};
  lua_pushnumber(L, sizes[luaL_checkoption(L, 1, "int", typenames)]);
  return 1;
}

static int luasofia_align(lua_State *L) {
  static const int aligns[] = {AT_INT_ALIGN, AT_DOUBLE_ALIGN, AT_CHAR_ALIGN, AT_CHAR_P_ALIGN,
                               AT_INT_ALIGN, AT_SHORT_ALIGN, AT_LONG_ALIGN, AT_VOID_P_ALIGN,
                               AT_VOID_P_ALIGN, AT_CHAR_ALIGN,
                               AT_SHORT_ALIGN, AT_LONG_ALIGN, AT_FLOAT_ALIGN,
                               //AT_VOID_P_ALIGN, AT_CHAR_P_ALIGN, AT_VOID_P_ALIGN,
                               AT_CHAR_P_ALIGN, AT_VOID_P_ALIGN,
                               AT_VOID_P_ALIGN};
  static const char *const typenames[] = {"int", "double", "char", "string",
                                          "uint", "ushort", "ulong", "ref uint",
                                          "pointer", "byte", "short", "long",
                                          //"float", "callback", "ref char",
                                          "float", "ref char",
                                          "ref int", "ref double", NULL};
  lua_pushnumber(L, aligns[luaL_checkoption(L, 1, "char", typenames)]);
  return 1;
}

static void *luasofia_checkudata(lua_State *L, int ud, const char *tname) {
  void *p = lua_touserdata(L, ud);
  if(p == NULL) return NULL;
  if(!lua_getmetatable(L, ud)) return NULL;
  lua_getfield(L, LUA_REGISTRYINDEX, tname);
  if(!lua_rawequal(L, -1, -2)) {
    lua_pop(L, 2);
    return NULL;
  } else {
    lua_pop(L, 2);
    return p;
  }
}

static char *luasofia_checkbuffer(lua_State *L, int index) {
  void *ud = luasofia_checkudata(L, index, LUASOFIA_BUFFER_META);
  luaL_argcheck(L, ud != NULL, index, "luasofia buffer expected");
  return (char *)ud;
}

static int luasofia_buffer_new(lua_State *L) {
  const char *s; char *b;
  size_t size;
  if(lua_type(L, 1) == LUA_TSTRING) {
    s = lua_tolstring(L, 1, &size);
    size++;
  } else if(lua_type(L, 1) == LUA_TLIGHTUSERDATA) {
    luaL_getmetatable(L, LUASOFIA_BUFFER_META);
    lua_setmetatable(L, -2);
    return 1;
  } else {
    s = NULL;
    size = luaL_optint(L, 1, BUFSIZ);
  }
  b = (char *)lua_newuserdata(L, size);
  if(b) {
    if(s) {
      memcpy(b, s, size - 1);
      b[size - 1] = '\0';
    }
    lua_newtable(L);
    lua_pushnumber(L, size);
    lua_setfield(L, -2, "size");
    lua_setfenv(L, -2);
    luaL_getmetatable(L, LUASOFIA_BUFFER_META);
    lua_setmetatable(L, -2);
    return 1;
  } else {
    luaL_error(L, "cannot allocate buffer");
  }
  return 0;
}

static int luasofia_buffer_tostring(lua_State *L) {
  char *b;
  int size, offset;
  b = luasofia_checkbuffer(L, 1);
  if(lua_gettop(L) < 2 || lua_isnil(L, 2)) {
    size = strlen(b);
    offset = 0;
  } else {
    size = luaL_checkinteger(L, 2);
    offset = luaL_optint(L, 3, 1) - 1;
  }
  lua_pushlstring(L, b + offset, size);
  return 1;
}

static int luasofia_buffer_len(lua_State *L) {
  char *b = luasofia_checkbuffer(L, 1);
  lua_pushinteger(L, strlen(b));
  return 1;
}

static int luasofia_buffer_topointer(lua_State *L) {
  char *b = luasofia_checkbuffer(L, 1);
  int offset = luaL_optint(L, 2, 1) - 1;
  lua_pushlightuserdata(L, b + offset);
  return 1;
}

static int luasofia_buffer_put(lua_State *L);

static int luasofia_buffer_get(lua_State *L) {
  static const void* funcs[] = {&luasofia_buffer_tostring,
                                &luasofia_buffer_topointer,
                                &luasofia_buffer_len,
                                &luasofia_buffer_get,
                                &luasofia_buffer_put};
  static const char *const funcnames[] = { "tostring", "topointer", "len", "get", "set", NULL };
  static const int types[] = {AT_VOID, AT_INT, AT_DOUBLE, AT_CHAR, AT_STRING, AT_PTR, AT_REFINT,
                              AT_UINT, AT_USHORT, AT_ULONG, AT_REFUINT,
                              //AT_REFDOUBLE, AT_REFCHAR, AT_CALLBACK, AT_SHORT, AT_BYTE, AT_LONG,
                              AT_REFDOUBLE, AT_REFCHAR, AT_SHORT, AT_BYTE, AT_LONG,
                              AT_FLOAT};
  static const char *const typenames[] =
    {"void", "int", "double", "char", "string", "pointer",
     "ref int", "uint", "ushort", "ulong", "ref uint", "ref double", "ref char", //"callback",
     "short", "byte", "long", "float", NULL};
  char *b = luasofia_checkbuffer(L, 1);
  if(lua_type(L, 2) == LUA_TSTRING) {
    lua_getfenv(L, 1);
    if(!lua_isnil(L, -1))
      lua_getfield(L, -1, lua_tostring(L, 2));
    if(lua_isnil(L, -1))
      lua_pushcfunction(L,
                        (lua_CFunction)funcs[luaL_checkoption(L, 2, "tostring", funcnames)]);
  } else {
    void *p;
    int offset = luaL_checkinteger(L, 2) - 1;
    int type = types[luaL_checkoption(L, 3, "char", typenames)];
    switch(type) {
    case AT_SHORT: lua_pushnumber(L, *((short*)(&b[offset]))); break;
    case AT_INT: lua_pushnumber(L, *((int*)(&b[offset]))); break;
    case AT_LONG: lua_pushnumber(L, *((long*)(&b[offset]))); break;
    case AT_USHORT: lua_pushnumber(L, *((unsigned short*)(&b[offset]))); break;
    case AT_UINT: lua_pushnumber(L, *((unsigned int*)(&b[offset]))); break;
    case AT_ULONG: lua_pushnumber(L, *((unsigned long*)(&b[offset]))); break;
    case AT_BYTE: lua_pushnumber(L, (signed char)b[offset]); break;
    case AT_CHAR: lua_pushnumber(L, b[offset]); break;
    case AT_FLOAT: lua_pushnumber(L, *((float*)(&b[offset]))); break;
    case AT_DOUBLE: lua_pushnumber(L, *((double*)(&b[offset]))); break;
    case AT_STRING:
      p = *((void**)&b[offset]);
      p ? lua_pushstring(L, (char*)p) : lua_pushnil(L);
      break;
/* TODO
    case AT_CALLBACK:
      p = *((void**)&b[offset]);
      p ? luasofia_makefunction(L, NULL, p, NULL) : lua_pushnil(L);
      break;
*/
    case AT_PTR:
      p = *((void**)&b[offset]);
      p ? lua_pushlightuserdata(L, p) : lua_pushnil(L);
      break;
    default:
      luaL_error(L, "luasofia: unknown type in buffer:get");
    }
  }
  return 1;
}

static int luasofia_buffer_put(lua_State *L) {
  static const int types[] = {AT_VOID, AT_INT, AT_DOUBLE, AT_CHAR, AT_STRING, AT_PTR, AT_REFINT,
                              AT_UINT, AT_USHORT, AT_ULONG, AT_REFUINT,
                              //AT_REFDOUBLE, AT_REFCHAR, AT_CALLBACK, AT_SHORT, AT_BYTE, AT_LONG,
                              AT_REFDOUBLE, AT_REFCHAR, AT_SHORT, AT_BYTE, AT_LONG,
                              AT_FLOAT};
  static const char *const typenames[] =
    {"void", "int", "double", "char", "string", "pointer",
     "ref int", "uint", "ushort", "ulong", "ref uint", "ref double", "ref char", //"callback",
     "short", "byte", "long", "float", NULL};
  char *b = luasofia_checkbuffer(L, 1);
  int offset = luaL_checkinteger(L, 2) - 1;
  int type = types[luaL_checkoption(L, 4, "char", typenames)];
  switch(type) {
  case AT_SHORT: *((short*)(&b[offset])) = (short)lua_tonumber(L, 3); break;
  case AT_INT: *((int*)(&b[offset])) = (int)lua_tonumber(L, 3); break;
  case AT_LONG: *((long*)(&b[offset])) = (long)lua_tonumber(L, 3); break;
  case AT_USHORT: *((unsigned short*)(&b[offset])) = (unsigned short)lua_tonumber(L, 3); break;
  case AT_UINT: *((unsigned int*)(&b[offset])) = (unsigned int)lua_tonumber(L, 3); break;
  case AT_ULONG: *((unsigned long*)(&b[offset])) = (unsigned long)lua_tonumber(L, 3); break;
  case AT_BYTE: b[offset] = (signed char)lua_tointeger(L, 3); break;
  case AT_CHAR: b[offset] = (char)lua_tointeger(L, 3); break;
  case AT_FLOAT: *((float*)(&b[offset])) = (float)lua_tonumber(L, 3); break;
  case AT_DOUBLE: *((double*)(&b[offset])) = (double)lua_tonumber(L, 3); break;
  case AT_STRING: *((char**)(&b[offset])) =
      (lua_isnil(L, 3) ? NULL : (char*)lua_tostring(L, 3)); break;
  // TODO case AT_CALLBACK: *((void**)(&b[offset])) = luasofia_tocallback(L, 3); break;
  case AT_PTR: *((void**)(&b[offset])) =
      (lua_isnil(L, 3) ? NULL : (lua_isuserdata(L, 3) ? lua_touserdata(L, 3) :
                                 (void*)lua_tostring(L, 3))); break;
  default:
    luaL_error(L, "luasofia: unknown type in buffer:put");
  }
  return 0;
}

static int luasofia_register_buffer_meta(lua_State *L) {
  luaL_newmetatable(L, LUASOFIA_BUFFER_META);
  lua_pushliteral(L, "__index");
  lua_pushcfunction(L, luasofia_buffer_get);
  lua_settable(L, -3);
  lua_pushliteral(L, "__newindex");
  lua_pushcfunction(L, luasofia_buffer_put);
  lua_settable(L, -3);
  lua_pushliteral(L, "__tostring");
  lua_pushcfunction(L, luasofia_buffer_tostring);
  lua_settable(L, -3);
  lua_pop(L, 1);
  return 0;
}

static const struct luaL_reg core_lib[] = {
  {"align", luasofia_align},
  {"sizeof", luasofia_sizeof},
  {"buffer", luasofia_buffer_new},
  {NULL, NULL},
};

int luaopen_luasofia_core(lua_State *L)
{
    /* create luasofia weak table at REGISTRYINDEX */
    luasofia_weak_table_create(L);

    /* create luasofia tag table at REGISTRYINDEX */
    luasofia_tags_create(L);

    luasofia_register_struct_meta(L);

    luasofia_register_buffer_meta(L);

    lua_getglobal(L, "luasofia");
    if(lua_isnil(L, -1)) {
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, "luasofia");
    }
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "core");
    luaL_register(L, NULL, core_lib);
    return 1;
}

