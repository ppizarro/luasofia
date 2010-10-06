## Process this file with autoconf to produce a configure script.
AC_INIT([LuaSofia], [0.1.7devel], [luasofia-devel@lists.sourceforge.net], luasofia)

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_AUX_DIR(build-aux)

AM_INIT_AUTOMAKE

LT_INIT([disable-static])

# Before making a release, the LT_VERSION string should be modified.
# The string is of the form C:R:A.
# - If interfaces have been changed or added, but binary compatibility has
#   been preserved, change to C+1:0:A+1
# - If binary compatibility has been broken (eg removed or changed interfaces)
#   change to C+1:0:0
# - If the interface is the same as the previous version, change to C:R+1:A

LT_VERSION=7:0:0
AC_SUBST(LT_VERSION)

AC_CONFIG_SRCDIR([src/luasofia.c])

# Checks for programs
# ----------------------------------------------------------------------------
AC_LANG([C])
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

# lib: sofia-sip-ua
# ----------------------------------------------------------------------------
PKG_CHECK_MODULES(SOFIA_SIP_UA, sofia-sip-ua >= 1.12.10,
[
    SOFIA_SIP_UA_VERSION=`pkg-config sofia-sip-ua --modversion`
])
AC_SUBST(SOFIA_SIP_UA_LIBS)
AC_SUBST(SOFIA_SIP_UA_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_VERSION)

# lib: sofia-sip-ua-glib
# ----------------------------------------------------------------------------
PKG_CHECK_MODULES(SOFIA_SIP_UA_GLIB, sofia-sip-ua-glib >= 1.12.10)
AC_SUBST(SOFIA_SIP_UA_GLIB_LIBS)
AC_SUBST(SOFIA_SIP_UA_GLIB_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_GLIB_VERSION)

AC_ARG_ENABLE(sofia_devel,
[  --enable-sofia-devel          enable sofia devel support [[disabled]]],
 , enable_sofia_devel=no)

if test x$enable_sofia_devel = xyes ; then
  AC_DEFINE([HAVE_SOFIA_DEVEL], 1, [Define to 1 if we use sofia devel library])
fi
AM_CONDITIONAL([TEST_SOFIA_DEVEL], [test "x$enable_sofia_devel" = xyes])

# lib: lua
# ----------------------------------------------------------------------------

PKG_CHECK_MODULES(LUA, lua5.1 >= 5.1,
[
    if test "x$LUA_CMODULE" = x; then
        LUA_CMODULE=`$PKG_CONFIG lua5.1 --variable=INSTALL_CMOD`
    fi
    LUA_VERSION="5.1"
], 
[
    PKG_CHECK_MODULES(LUA, lua5.2 >= 5.2,
    [
        if test "x$LUA_CMODULE" = x; then
            LUA_CMODULE=`$PKG_CONFIG lua5.2 --variable=INSTALL_CMOD`
        fi
        LUA_VERSION="5.2"
    ],
    [
        PKG_CHECK_MODULES(LUA, lua >= 5.1,
        [
            if test "x$LUA_CMODULE" = x; then
                LUA_CMODULE=`$PKG_CONFIG lua --variable=INSTALL_CMOD`
            fi
            LUA_VERSION=`$PKG_CONFIG lua --variable=major_version`
        ])
    ])
])

if test "x$LUA_VERSION" = x; then
    LUA_VERSION="5.1"
fi

if test "x$LUA_CMODULE" = x; then
    LUA_CMODULE="$libdir/lua/$LUA_VERSION"
fi

AC_SUBST(LUA_LIBS)
AC_SUBST(LUA_CFLAGS)
AC_SUBST(LUA_CMODULE)
AC_SUBST(LUA_VERSION)

# Create files
# ----------------------------------------------------------------------------
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT

