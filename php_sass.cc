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
  | Note                                                                 |
  |   ZEND_MODULE_API_NO >= 20071006 required                            |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

/* PHP */
//#include "php.h"

/* libsass */
//#include "libsass/sass_interface.h"

/* Extesion */
#include "php_sass.h"

#ifdef COMPILE_DL_SASS
extern "C" {
ZEND_GET_MODULE(sass)
}
#endif

/* Declare SASS class entry */
ZEND_API zend_class_entry *sass_class;
static zend_object_handlers sass_class_handlers;

/* SASS module meta */
zend_module_entry sass_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	"sass", // module name
	NULL, // module's functions
	PHP_MINIT(sass), // module init callback
	NULL,  // module shutdown callback
	NULL,  // request init callback
	NULL, // request shutdown callback
	NULL, // module info callback
	"1.0", // module version
	STANDARD_MODULE_PROPERTIES
};

/* Define method's body */
PHP_METHOD(SASS, compile) {
	char* str, incs;
	int str_len, incs_len, res;
	long options = 0;
	//struct sass_context *ctx;

	if (zend_parse_parameters(ZEND_ARGS, "s|ls", &str, &str_len, &options, &incs, &incs_len) != SUCCESS) {
        RETURN_FALSE;
    }

    /*if(!str_len) {
        RETURN_EMPTY_STRING();
    }
	//php_printf("Cast %d, %d", sizeof(struct sass_context), sizeof(sass_new_context()));
	ctx = (struct sass_context*) emalloc(sizeof(struct sass_context));
	//ctx->options = (sass_context*) emalloc(sizeof(sass_context));
    //ctx = sass_new_context();
	ctx->input_string = str;
	ctx->options->output_style = (int)options;
	if(incs_len) {
		ctx->options->include_paths = incs;
	} else {
		ctx->options->include_paths = NULL;
	}
	res = sass_compile(ctx);
	php_printf("compiled: %d: %s: %d", res, ctx->output_string, ctx->error_status);
    //sass_free_context(ctx);
    efree(ctx);*/
}

PHP_METHOD(SASS, compileFile) {
	RETURN_LONG(2);
}

PHP_METHOD(SASS, compileFolder) {
	RETURN_LONG(3);
}

/* Define method's arguments */
ZEND_BEGIN_ARG_INFO_EX(arginfo_compile, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, include_paths)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_compile_file, 0, 0, 2)
	ZEND_ARG_INFO(0, input)
	ZEND_ARG_INFO(0, output)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_compile_folder, 0, 0,  2)
	ZEND_ARG_INFO(0, input)
	ZEND_ARG_INFO(0, output)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO();

/* Register methods */
static const zend_function_entry sass_methods[] = {
	ZEND_ME(SASS, compile, arginfo_compile, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	ZEND_ME(SASS, compileFile, arginfo_compile_file, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	ZEND_ME(SASS, compileFolder, arginfo_compile_folder, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

/* module init callback */
PHP_MINIT_FUNCTION(sass) {
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "SASS", sass_methods);
	sass_class = zend_register_internal_class(&ce TSRMLS_CC);
	// copy all std methods
	memcpy(&sass_class_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	SASS_CLASS_CONST_LONG("STYLE_NESTED", 0);
	SASS_CLASS_CONST_LONG("STYLE_EXPANDED", 1);
	SASS_CLASS_CONST_LONG("STYLE_COMPACT", 2);
	SASS_CLASS_CONST_LONG("STYLE_COMPRESSED", 3);
	return SUCCESS;
}
