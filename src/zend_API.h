/*
  +----------------------------------------------------------------------+
  | Compatibility macros for different PHP versions                      |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Adam Harvey <aharvey@php.net>                                |
  +----------------------------------------------------------------------+
*/

#ifndef _COMPAT_ZEND_API_H
#define _COMPAT_ZEND_API_H

#ifdef PHP_7
/*============================================================================*/

#else
/*== PHP 5 ===================================================================*/

/*
 * Many string-related macros used to take duplicate parameters, which
 * specified whether the string should be duplicated or not. In practice,
 * almost all code used 1, so PHP 7 always duplicates.
 *
 * This header redefines the relevant macros to match PHP 7.
 */

#undef ZVAL_STRING
#define ZVAL_STRING(z, s) do { \
		const char *__s = (s); \
		zval *__z = (z); \
		Z_STRLEN_P(__z) = strlen(__s); \
		Z_STRVAL_P(__z) = estrndup(__s, Z_STRLEN_P(__z)); \
		Z_TYPE_P(__z) = IS_STRING; \
	} while (0)

#undef ZVAL_STRINGL
#define ZVAL_STRINGL(z, s, l) do { \
		const char *__s = (s); \
		int __l = (l); \
		zval *__z = (z); \
		Z_STRLEN_P(__z) = __l; \
		Z_STRVAL_P(__z) = estrndup(__s, __l); \
		Z_TYPE_P(__z) = IS_STRING; \
	} while (0)

#undef RETVAL_STRING
#define RETVAL_STRING(s)     ZVAL_STRING(return_value, (s))

#undef RETVAL_STRINGL
#define RETVAL_STRINGL(s, l) ZVAL_STRINGL(return_value, (s), (l))

#undef RETURN_STRING
#define RETURN_STRING(s)     { RETVAL_STRING(s); return; }

#undef RETURN_STRINGL
#define RETURN_STRINGL(s, l) { RETVAL_STRINGL(s, l); return; }

#undef add_assoc_string
#define add_assoc_string(__arg, __key, __str) add_assoc_string_ex(__arg, __key, strlen(__key)+1, __str, 1)

#undef add_assoc_stringl
#define add_assoc_stringl(__arg, __key, __str, __len) add_assoc_stringl_ex(__arg, __key, strlen(__key)+1, __str, __len, 1)

#endif /* PHP_7 */
/*============================================================================*/

#endif /* _COMPAT_ZEND_API_H */
