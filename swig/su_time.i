%{

#include <sofia-sip/su_time.h>

static int native_su_nanotime(lua_State* L)
{
  int SWIG_arg = 0;
  su_nanotime_t result;
 
  SWIG_check_num_args("su_nanotime",0,0)
 
  result = (su_nanotime_t)su_nanotime(NULL);
  lua_pushnumber(L, (lua_Number) result); SWIG_arg++;
  return SWIG_arg;
 
fail:
  lua_error(L);
  return SWIG_arg;
}

static int native_su_monotime(lua_State* L)
{
  int SWIG_arg = 0;
  su_nanotime_t result;
 
  SWIG_check_num_args("su_monotime",0,0)
 
  result = (su_nanotime_t)su_monotime(NULL);
  lua_pushnumber(L, (lua_Number) result); SWIG_arg++;
  return SWIG_arg;
 
fail:
  lua_error(L);
  return SWIG_arg;
}

static int native_su_time_print(lua_State*L)
{
  int SWIG_arg = 0;
  int len = 32;
  char buf[len];
  su_time_t *t = NULL;
 
  SWIG_check_num_args("su_time_print",1,1)
  if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("su_time_print",1,"su_time_t const *");
 
  if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&t,SWIGTYPE_p_su_time_s,0))){
    SWIG_fail_ptr("su_time_print",3,SWIGTYPE_p_su_time_s);
  }
 
  su_time_print(buf, len, (struct su_time_s const *)t);

  lua_pushstring(L, buf);
  SWIG_arg++;
  return SWIG_arg;
  
fail:
  lua_error(L);
  return SWIG_arg;
}

%}

%native(su_nanotime) int native_su_nanotime(lua_State*L);
%native(su_monotime) int native_su_monotime(lua_State*L);
%native(su_time_print) int native_su_time_print(lua_State*L);

/*
%typemap(in,numinputs=0,noblock=1) (char *s, int len)
{
    int n = 32;
    char buf[n];
    $1 = buf;
    $2 = n;
}

%typemap(argout,noblock=1) (char *s, int len)
{
    lua_pushstring(L, $1);
    SWIG_arg++;
}
*/

%include <sofia-sip/su_time.h>

