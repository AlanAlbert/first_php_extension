/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hello.h"

/* If you declare any globals in php_hello.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(hello)
*/

/* True global resources - no need for thread safety here */
static int le_hello;

/* {{{ PHP_INI
 */
// Remove comments and fill if you need to have entries in php.ini
// 设置配置规则
PHP_INI_BEGIN()
//    STD_PHP_INI_ENTRY("hello.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_hello_globals, hello_globals)
//    STD_PHP_INI_ENTRY("hello.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_hello_globals, hello_globals)
PHP_INI_END()

/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_hello_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(hello_msg)
{
    char *name;
    size_t len;
	zend_string *msg;

    /**
     * 整型：l、L(范围更大)，解析到zend_long
     * 布尔型：b，解析到zend_bool
     * 浮点型：d，解析到double
     * 字符串型：s解析到char*，此时还需要一个size_t类型变量获取字符串长度；
     *         S解析到zend_string；
     *         当设置为"s!"、"S!"时，不需要使用zend_bool保存，如果为null，char*、zend_string为null；
     *         p、P主要用于解析路径
     * 数组：a和A解析到zval*；h、H解析到HashTable*
     * 对象：o、O解析到zval*
     * 资源：r解析到zval*
     * callable（函数或成员方法）：f解析到zend_fcall_info结构体
     * 任意类型：z
     * 其他：|表示后面的参数为可选参数；*表示可传任意数量参数；+表示至少需要一个参数，且只能接收到一个，多传无益
     *
     * 当标识为"l!"、"L!"、"b!"、"d!"时，需要再提供一个zend_bool变量的地址，通过这个值可以判断传入的参数是否为NULL，如果为NULL则将要解析到的zend_long值设置为0，同时zend_bool设置为1
     * 当标识为"s!"、"S!"、"p!"、"P!"、"a!"、"A!"、"h!"、"H!"、"o!"、"O!"、"r!"时，如果传入参数为null，则其值直接为null
     *
     */

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &name, &len) == FAILURE) {
		return;
	}

	msg = strpprintf(0, "Hello, %s", name);

	RETURN_STR(msg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_hello_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_hello_init_globals(zend_hello_globals *hello_globals)
{
	hello_globals->global_value = 0;
	hello_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 * PHP模块初始化
 * 通常情况下，此过程只会在SAPI启动过程中执行一次。在该阶段可以做：
 * 1 注册内部类
 * 2 注册扩展定义的常量
 * 3 在此阶段可以覆盖PHP编译、执行的两个函数指针：zend_compile_file、zend_execute_ex
     从而可以接管PHP的编译、执行，opcache的实现原理就是替换了zend_compile_file
     从而使得PHP编译时调用的是opcache自己定义的编译函数，对编译后的结果进行缓存
 */
PHP_MINIT_FUNCTION(hello)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 * PHP模块关闭，主要进行一些资源的清理
 */
PHP_MSHUTDOWN_FUNCTION(hello)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 * PHP请求初始化
 * 需要对每个请求进行操作，可以放在此函数中
 */
PHP_RINIT_FUNCTION(hello)
{
#if defined(COMPILE_DL_HELLO) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 * PHP请求结束
 * PHP请求结束之后还存在一个钩子函数post_deactivate_func，使用较少
 */
PHP_RSHUTDOWN_FUNCTION(hello)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 * phpinfo函数输出的扩展信息
 */
PHP_MINFO_FUNCTION(hello)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "hello support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ hello_functions[]
 *
 * Every user visible function must have an entry in hello_functions[].
 */
const zend_function_entry hello_functions[] = {
	PHP_FE(hello_msg,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in hello_functions[] */
};
/* }}} */

/* {{{ hello_module_entry
 */
zend_module_entry hello_module_entry = {
	STANDARD_MODULE_HEADER,
	"hello",
	hello_functions,
	PHP_MINIT(hello),
	PHP_MSHUTDOWN(hello),
	PHP_RINIT(hello),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(hello),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(hello),
	PHP_HELLO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HELLO
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(hello)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
