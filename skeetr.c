/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2006 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: nabeel@php.net                                               |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1 2006/01/01 12:50:00 sniper Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_skeetr.h"

/* If you declare any globals in php_skeetr.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(skeetr)
*/

/* True global resources - no need for thread safety here */
static int le_skeetr;

/* {{{ skeetr_functions[]
 *
 * Every user visible function must have an entry in skeetr_functions[].
 */
zend_function_entry skeetr_functions[] = {
	PHP_FE(skeetr_override_function,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in skeetr_functions[] */
};
/* }}} */

/* {{{ skeetr_module_entry
 */
zend_module_entry skeetr_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"skeetr",
	skeetr_functions,
	PHP_MINIT(skeetr),
	PHP_MSHUTDOWN(skeetr),
	PHP_RINIT(skeetr),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(skeetr),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(skeetr),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SKEETR
ZEND_GET_MODULE(skeetr)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("skeetr.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_skeetr_globals, skeetr_globals)
    STD_PHP_INI_ENTRY("skeetr.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_skeetr_globals, skeetr_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_skeetr_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_skeetr_init_globals(zend_skeetr_globals *skeetr_globals)
{
	skeetr_globals->global_value = 0;
	skeetr_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(skeetr)
{
	/* If you have INI entries, uncomment these lines 
	ZEND_INIT_MODULE_GLOBALS(skeetr, php_skeetr_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(skeetr)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(skeetr)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(skeetr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(skeetr)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "skeetr support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

/* {{{ proto bool skeetr_override_function(string funcname, string arglist, string code[, bool return_reference = FALSE])
    Replaces the given built-in function*/
PHP_FUNCTION(skeetr_override_function)
{
    zend_bool return_ref = 0;
    int retval;

    char *code = NULL;
    int code_len = 0;

    char *args = NULL;
    int args_len = 0;

    char *name = NULL;
    int name_len = 0;

    char *eval = NULL, *eval_desc, *int_name = NULL;
    int eval_len = 0, int_name_len = 0;


    if (
        zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s|s|b", 
            &name, &name_len, &args, &args_len, &code, &code_len, &return_ref
        ) == FAILURE
    ) {
        RETURN_NULL();
    }

    if ( zend_hash_del(EG(function_table), name, name_len + 1) == FAILURE ) {
        zend_error(E_ERROR, "%s() function not present in global function_table", name);
        RETURN_FALSE;
    }


    eval_len = spprintf(&eval, 0, "function %s%s(%s){%s}", return_ref ? "&" : "", name, args, code);
    eval_desc = zend_make_compiled_string_description("runtime-created override function" TSRMLS_CC);
    
    retval = zend_eval_string(eval, NULL, eval_desc TSRMLS_CC);
    efree(eval_desc);
    efree(eval);

    RETURN_TRUE;
}
