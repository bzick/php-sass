/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Ivan Shalganov <a.cobest@gmail.com>                          |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SASS_H
#define PHP_SASS_H

#ifdef ZTS
#  include "TSRM.h"
#endif

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif 


extern "C" {
#include "php.h"
#include "zend_exceptions.h"
}

extern zend_module_entry sass_module_entry;
#define phpext_sass_ptr &sass_module_entry

#define PHP_SASS_VERSION_NUMBER 10
#define PHP_SASS_VERSION "0.1"

extern ZEND_API zend_class_entry *sass_class;

#define SASS_CLASS_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(sass_class, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);

#define ZEND_ARGS \
	ZEND_NUM_ARGS() TSRMLS_CC

PHP_METHOD(SASS, compile);
PHP_METHOD(SASS, compileFile);
PHP_METHOD(SASS, compileFolder);

PHP_MINIT_FUNCTION(sass);


#endif	/* PHP_SASS_H */
