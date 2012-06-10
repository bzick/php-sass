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

/* libsass */
#include "libsass/sass_interface.h"
#include <string>
#include <iostream>


/* Extesion header */
#include "php_sass.h"

#ifdef COMPILE_DL_SASS
extern "C" {
ZEND_GET_MODULE(sass)
}
#endif

/* 'Fetch' internal Exception class */
#define ce_std_Exception zend_exception_get_default(TSRMLS_C)

/* Declare SASS class entry */
ZEND_API zend_class_entry *sass_class;
ZEND_API zend_class_entry *sass_CompileErrorException;
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
    PHP_SASS_VERSION, // module version
    STANDARD_MODULE_PROPERTIES
};

/* Define method's body */

/* public static SASS::compile($string, $options = SASS::STYLE_NESTED, $include_path = ""):string */
PHP_METHOD(SASS, compile) {
    char *str, *incs;
    int str_len, incs_len;
    long options = SASS_STYLE_NESTED;
    struct sass_context *ctx;

    if (zend_parse_parameters(ZEND_ARGS, "s|ls", &str, &str_len, &options, &incs, &incs_len) != SUCCESS) {
        RETURN_FALSE;
    }

    if(!str_len) {
        RETURN_EMPTY_STRING();
    }

    if(SASS_STYLE_NESTED != options) {
        zend_throw_exception(sass_CompileErrorException, "Given option not implemented (use SASS::STYLE_NESTED)", -2 TSRMLS_CC);
        return;
    }

    ctx = sass_new_context();
    ctx->source_string = str;
    
    ctx->options.output_style = (int)options;
    if(incs_len) {
        //ctx->options.include_paths = incs;
        ctx->options.include_paths = NULL;
    } else {
        ctx->options.include_paths = NULL;
    }

    sass_compile(ctx);

    if(ctx->error_status) {
        zend_throw_exception(sass_CompileErrorException, ctx->error_message, ctx->error_status TSRMLS_CC);
    } else {
        RETVAL_STRING(ctx->output_string, 1);
    }
    
    sass_free_context(ctx);
}

/* public static SASS::compileFile($input, $options = self::STYLE_NESTED, $include_paths = null):string */
PHP_METHOD(SASS, compileFile) {
    char *filename, *incs;
    int filename_len, incs_len, result;
    long options = SASS_STYLE_NESTED;
    struct sass_file_context *ctx; 
    
    if (zend_parse_parameters(ZEND_ARGS, "s|ls", &filename, &filename_len, &options, &incs, &incs_len) != SUCCESS) {
        RETURN_FALSE;
    }
    
    if(!filename_len) {
        zend_throw_exception(sass_CompileErrorException, "Empty input filename", -1 TSRMLS_CC);
        return;
    }
    
    if(SASS_STYLE_NESTED != options) {
        zend_throw_exception(sass_CompileErrorException, "Given option not implemented (use SASS::STYLE_NESTED)", -2 TSRMLS_CC);
        return;
    }
    
    ctx = sass_new_file_context();
    ctx->input_path = filename;
    
    ctx->options.output_style = (int)options;
    ctx->options.include_paths = NULL;
    
    // https://github.com/hcatlin/libsass/issues/2
    try {
        sass_compile_file(ctx);
    } catch(std::string& s) {
        zend_throw_exception_ex(sass_CompileErrorException, 1, "File %s not found", (char*)s.c_str() TSRMLS_CC);
        sass_free_file_context(ctx);
        return;
    }

    if(ctx->error_status) {
        zend_throw_exception(sass_CompileErrorException, ctx->error_message, ctx->error_status TSRMLS_CC);
    } else {
        RETVAL_STRING(ctx->output_string, 1);
    }
    
    sass_free_file_context(ctx);
}

/* public static SASS::compileFolder($input, $output, $options = self::STYLE_NESTED, $include_paths = null):string */
PHP_METHOD(SASS, compileFolder) {
    char *input, *output, *incs;
    int input_len, output_len, incs_len;
    long options = SASS_STYLE_NESTED;
    struct sass_folder_context *ctx; 
    
    if (zend_parse_parameters(ZEND_ARGS, "ss|ls", &input, &input_len, &output, &output_len, &options, &incs, &incs_len) != SUCCESS) {
        RETURN_FALSE;
    }
    
    // because sass_compile_folder do not work yet
    zend_throw_exception(sass_CompileErrorException, "Compile folder not implemented", -2 TSRMLS_CC);
    return;
    
    if(!input_len) {
        zend_throw_exception(sass_CompileErrorException, "Empty input folder path", -1 TSRMLS_CC);
        return;
    }
    
    if(!output_len) {
        zend_throw_exception(sass_CompileErrorException, "Empty input folder path", -1 TSRMLS_CC);
        return;
    }
    
    if(SASS_STYLE_NESTED != options) {
        zend_throw_exception(sass_CompileErrorException, "Given option not implemented (use SASS::STYLE_NESTED)", -2 TSRMLS_CC);
        return;
    }
    
    ctx = sass_new_folder_context();
    ctx->search_path = input;
    ctx->output_path = output;
    
    ctx->options.output_style = (int)options;
    ctx->options.include_paths = NULL;
     
    if(sass_compile_folder(ctx)) {
        zend_throw_exception(sass_CompileErrorException, ctx->error_message, ctx->error_status TSRMLS_CC);
    } 

    sass_free_folder_context(ctx);
}

/* Define method's arguments */
ZEND_BEGIN_ARG_INFO_EX(arginfo_compile, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
    ZEND_ARG_INFO(0, options)
    ZEND_ARG_INFO(0, include_paths)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_compile_file, 0, 0, 2)
    ZEND_ARG_INFO(0, input)
    ZEND_ARG_INFO(0, options)
    ZEND_ARG_INFO(0, include_paths)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_compile_folder, 0, 0,  2)
    ZEND_ARG_INFO(0, input)
    ZEND_ARG_INFO(0, output)
    ZEND_ARG_INFO(0, options)
    ZEND_ARG_INFO(0, include_paths)
ZEND_END_ARG_INFO();

/* Register methods */
static const zend_function_entry sass_methods[] = {
    ZEND_ME(SASS, compile, arginfo_compile,                 ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(SASS, compileFile, arginfo_compile_file,         ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_ME(SASS, compileFolder, arginfo_compile_folder,     ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

/* Init module callback */
PHP_MINIT_FUNCTION(sass) {
    zend_class_entry ce_sass, ce_exc;
    
    INIT_CLASS_ENTRY(ce_sass, "SASS", sass_methods);
    sass_class = zend_register_internal_class(&ce_sass TSRMLS_CC);
    // copy all std methods
    memcpy(&sass_class_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    SASS_CLASS_CONST_LONG("VERSION_NUMBER",        PHP_SASS_VERSION);
    SASS_CLASS_CONST_LONG("STYLE_NESTED",         SASS_STYLE_NESTED);
    SASS_CLASS_CONST_LONG("STYLE_EXPANDED",     SASS_STYLE_EXPANDED);
    SASS_CLASS_CONST_LONG("STYLE_COMPACT",         SASS_STYLE_COMPACT);
    SASS_CLASS_CONST_LONG("STYLE_COMPRESSED",     SASS_STYLE_COMPRESSED);
    
    INIT_NS_CLASS_ENTRY(ce_exc, "SASS", "CompileErrorException", NULL);
    sass_CompileErrorException = zend_register_internal_class_ex(&ce_exc, ce_std_Exception, NULL TSRMLS_CC);
    sass_CompileErrorException->create_object = ce_std_Exception->create_object;
    return SUCCESS;
}
