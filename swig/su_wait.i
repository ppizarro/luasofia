%{

#include <sofia-sip/su_wait.h>

struct lua_clone_s {
   su_clone_r clone_r;
   int ref_clone;
   int ref_magic;
   int ref_init;
   int ref_deinit;
};

static int su_root_init_cb (su_root_t *root, su_root_magic_t *magic)
{
    printf("su_root_init_cb...\n");
    return 0;
}

static void su_root_deinit_cb (su_root_t *root, su_root_magic_t *magic)
{
    printf("su_root_deinit_cb...\n");
}

static int native_su_clone_start(lua_State*L)
{
  int SWIG_arg = 0;
  su_root_t *root = (su_root_t *) 0 ;
  struct lua_clone_s *clone = (struct lua_clone_s *) 0;
/*
  su_root_magic_t *arg3 = (su_root_magic_t *) 0 ;
  su_root_init_f arg4 = (su_root_init_f) 0 ;
  su_root_deinit_f arg5 = (su_root_deinit_f) 0 ;
*/
  int result;
  
  SWIG_check_num_args("su_clone_start",4,4)
  if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("su_clone_start",1,"su_root_t *");
  if(!SWIG_isptrtype(L,2)) SWIG_fail_arg("su_clone_start",2,"su_root_magic_t *");
  if(!lua_isfunction(L,3) && !lua_isnil(L,3)) SWIG_fail_arg("su_clone_start",3,"su_root_init_f");
  if(!lua_isfunction(L,4) && !lua_isnil(L,4)) SWIG_fail_arg("su_clone_start",4,"su_root_deinit_f");
  
  if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&root,SWIGTYPE_p_su_root_s,0))){
    SWIG_fail_ptr("su_clone_start",1,SWIGTYPE_p_su_root_s);
  }

  clone = (struct lua_clone_s *)lua_newuserdata(L, sizeof(struct lua_clone_s));
  luaL_getmetatable(L, "struct lua_clone_s");
  if(lua_isnil(L, -1))
    luaL_error(L, "Nao eh mesmo estado do lua");
  lua_setmetatable(L, -2);

  lua_pushvalue(L, 2);
  clone->ref_magic = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pushvalue(L, 3);
  clone->ref_init = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pushvalue(L, 4);
  clone->ref_deinit = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pushvalue(L, -1);
  clone->ref_clone = luaL_ref(L, LUA_REGISTRYINDEX);
/*
  arg3=(su_root_magic_t *)SWIG_MustGetPtr(L,2,0,0,2,"su_clone_start");
  
  if (!SWIG_IsOK(SWIG_ConvertPtr(L,4,(void**)&arg4,SWIGTYPE_p_f_p_struct_su_root_s_p_void__int,0))){
    SWIG_fail_ptr("su_clone_start",4,SWIGTYPE_p_f_p_struct_su_root_s_p_void__int);
  }
  
  if (!SWIG_IsOK(SWIG_ConvertPtr(L,5,(void**)&arg5,SWIGTYPE_p_f_p_struct_su_root_s_p_void__void,0))){
    SWIG_fail_ptr("su_clone_start",5,SWIGTYPE_p_f_p_struct_su_root_s_p_void__void);
  }
*/  
  result = (int)su_clone_start(root, clone->clone_r, clone, su_root_init_cb, su_root_deinit_cb);
  lua_pushnumber(L, (lua_Number) result); SWIG_arg++;
  return SWIG_arg;
  
fail:
  lua_error(L);
  return SWIG_arg;
}

%}

%ignore su_wsaevent_port_create;
%ignore su_wsaevent_clone_start;

%native(su_clone_start) int native_su_clone_start(lua_State*L);

%include <sofia-sip/su_wait.h>

