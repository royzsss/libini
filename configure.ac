#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([libini.so], [0.1], [royzsss@163.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([ini-def.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lini':
AC_CHECK_LIB([ini], [main])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset strchr])

AC_CONFIG_FILES([Makefile
                 test/Makefile])
AC_OUTPUT
