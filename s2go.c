/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "libs2go.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_s2go.h"


/* If you declare any globals in php_s2go.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(s2go)
*/

/* True global resources - no need for thread safety here */
static int le_s2go;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("s2go.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_s2go_globals, s2go_globals)
    STD_PHP_INI_ENTRY("s2go.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_s2go_globals, s2go_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto int s2go_cellid(double lat, double lng)
   Return a int */
PHP_FUNCTION(s2go_cellid)
{
	double lat;
	double lng;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &lat, &lng) == FAILURE) {
		return;
	}

	zend_long cellid = (zend_long)S2CellID(lat, lng);
    RETURN_LONG(cellid);
}
/* }}} */


/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string s2go_getcoving(double lat, double lng, double radius, int maxcell)
   Return a json string */
PHP_FUNCTION(s2go_getcoving)
{
    double lat;
    double lng;
    double radius;
    int maxcell;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddl", &lat, &lng, &radius, &maxcell) == FAILURE) {
        return;
    }

    const char *str = (const char *)S2GetCoving(lat, lng, radius, maxcell);

    RETURN_STRINGL(str, strlen(str));
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_s2go_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_s2go_init_globals(zend_s2go_globals *s2go_globals)
{
	s2go_globals->global_value = 0;
	s2go_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(s2go)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(s2go)
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
PHP_RINIT_FUNCTION(s2go)
{
#if defined(COMPILE_DL_S2GO) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(s2go)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(s2go)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "s2go support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ s2go_functions[]
 *
 * Every user visible function must have an entry in s2go_functions[].
 */
const zend_function_entry s2go_functions[] = {
	PHP_FE(s2go_cellid,	NULL)		/* For testing, remove later. */
	PHP_FE(s2go_getcoving,	NULL)
	PHP_FE_END	/* Must be the last line in s2go_functions[] */
};
/* }}} */

/* {{{ s2go_module_entry
 */
zend_module_entry s2go_module_entry = {
	STANDARD_MODULE_HEADER,
	"s2go",
	s2go_functions,
	PHP_MINIT(s2go),
	PHP_MSHUTDOWN(s2go),
	PHP_RINIT(s2go),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(s2go),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(s2go),
	PHP_S2GO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_S2GO
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(s2go)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
