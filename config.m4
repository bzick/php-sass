
PHP_ARG_WITH(sass, for libsass support,
[  --with-sass             Include SASS support])

if test "$PHP_SASS" != "no"; then
  PHP_ADD_INCLUDE(.)
  AC_CONFIG_SRCDIR([libsass/sass_interface.h])
  PHP_ADD_BUILD_DIR(libsass)
  PHP_ADD_LIBRARY_WITH_PATH(libsass, libsass, LIBSASS_SHARED_LIBADD)
  PHP_SUBST(SASS_SHARED_LIBADD)
  sass_src="php_sass.c"
  PHP_NEW_EXTENSION(sass, $sass_src, $ext_shared)
fi
