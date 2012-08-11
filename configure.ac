## Process this file with autoconf to produce a configure script.
AC_INIT([LuaSofia], [0.1.8], [luasofia-devel@lists.sourceforge.net], luasofia)

AC_CONFIG_MACRO_DIR([m4macros])

AC_CONFIG_AUX_DIR(build-aux)

AM_INIT_AUTOMAKE

LT_INIT([disable-static])

# Increment on interface addition. Reset on removal.
LUASOFIA_AGE=1

# Increment on interface add, remove, or change.
LUASOFIA_CURRENT=9

# Increment on source change. Reset when CURRENT changes.
LUASOFIA_REVISION=0

AC_SUBST(LUASOFIA_CURRENT)
AC_SUBST(LUASOFIA_REVISION)
AC_SUBST(LUASOFIA_AGE)

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
PKG_CHECK_MODULES(SOFIA_SIP_UA, sofia-sip-ua >= 1.12.11,
[
    SOFIA_SIP_UA_VERSION=`pkg-config sofia-sip-ua --modversion`
])
AC_SUBST(SOFIA_SIP_UA_LIBS)
AC_SUBST(SOFIA_SIP_UA_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_VERSION)

# lib: sofia-sip-ua-glib
# ----------------------------------------------------------------------------
PKG_CHECK_MODULES(SOFIA_SIP_UA_GLIB, sofia-sip-ua-glib >= 1.12.11)
AC_SUBST(SOFIA_SIP_UA_GLIB_LIBS)
AC_SUBST(SOFIA_SIP_UA_GLIB_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_GLIB_VERSION)

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

AC_SUBST(LUA_CFLAGS)
AC_SUBST(LUA_CMODULE)
AC_SUBST(LUA_VERSION)

# Create files
# ----------------------------------------------------------------------------
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT

