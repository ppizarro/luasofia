## Process this file with autoconf to produce a configure script.
AC_INIT([Luasofia], [0.1], [luasofia-devel@lists.sourceforge.net])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_AUX_DIR(build-aux)

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/luasofia.c])

# Checks for programs
# ----------------------------------------------------------------------------
AC_LANG([C])
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# lib: sofia-sip
# ----------------------------------------------------------------------------
PKG_CHECK_MODULES(SOFIA_SIP_UA, sofia-sip-ua >= 1.12.10)
AC_SUBST(SOFIA_SIP_UA_LIBS)
AC_SUBST(SOFIA_SIP_UA_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_VERSION)

PKG_CHECK_MODULES(LUA, lua5.1)
AC_SUBST(LUA_LIBS)
AC_SUBST(LUA_CFLAGS)

# Create files
# ----------------------------------------------------------------------------
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT
	
