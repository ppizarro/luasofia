%module luasofia
%{

#define SU_ROOT_MAGIC_T void *

#include <sofia-sip/su_config.h>
#include <sofia-sip/su_types.h>
#include <sofia-sip/su_alloc.h>
#include <sofia-sip/su_localinfo.h>
#include <sofia-sip/su_log.h>
#include <sofia-sip/su_tag.h>
#include <sofia-sip/su_md5.h>
#include <sofia-sip/su_uniqueid.h>

#include <sofia-sip/htable.h>
#include <sofia-sip/rbtree.h>
#include <sofia-sip/su_strlst.h>
#include <sofia-sip/su_vector.h>

/* #include <sofia-sip/tstdef.h> */
%}

%include "su_socket.i"
%include "su_time.i"
%include "su_wait.i"

%include <sofia-sip/su_alloc.h>
%include <sofia-sip/su_localinfo.h>

%include <sofia-sip/su_log.h>
%include <sofia-sip/su_tag.h>
%include <sofia-sip/su_md5.h>
%include <sofia-sip/su_uniqueid.h>

%include <sofia-sip/htable.h>
%include <sofia-sip/rbtree.h>
%include <sofia-sip/su_strlst.h>
%include <sofia-sip/su_vector.h>

/* %include <sofia-sip/tstdef.h> */

