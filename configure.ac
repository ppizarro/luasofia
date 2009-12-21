AC_INIT(Luasofia, 0.1 ,luasofia-devel@lists.sourceforge.net)
AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_CONFIG_HEADERS(config.h)

PKG_CHECK_MODULES(SOFIA, sofia-sip-ua)
PKG_CHECK_MODULES(LUA, lua5.1)

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

