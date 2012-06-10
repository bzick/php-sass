
PHP_ARG_WITH(sass, for libsass support,
[  --with-sass             Include SASS support])

if test "$PHP_SASS" != "no"; then
  PHP_ADD_INCLUDE(.)
  PHP_REQUIRE_CXX()
  PHP_SUBST(SASS_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, SASS_SHARED_LIBADD)
  PHP_NEW_EXTENSION(sass, libsass/context.cpp libsass/functions.cpp libsass/document.cpp \
	libsass/document_parser.cpp libsass/eval_apply.cpp libsass/node.cpp \
	libsass/node_factory.cpp libsass/node_emitters.cpp libsass/prelexer.cpp \
	libsass/sass_interface.cpp php_sass.cc, $ext_shared)
fi
