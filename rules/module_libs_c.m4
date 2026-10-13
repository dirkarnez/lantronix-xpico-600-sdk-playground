
`#include "'THIS_MODULE_NAME`_module_libs.h"'
dnl ************************ EXTERNAL FUNCTION SHIM SECTION ************************
`
/* External function shims: */'
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `define_external_function___scan_param',
    `ifelse(`$1',`',,``
    $1'ifelse(`$2',`',,`,')define_external_function___scan_param(shift($@))')dnl
')dnl
dnl ************************
define(
    `define_external_function_with_shim___scan_param',
    `ifelse(`$1',`',,``
            'ifelse(`$1',`...',`args',regexp(`$1',`\([_a-zA-Z0-9]+\)$',`\1'))`'ifelse(
        `$2',`',,`,')define_external_function_with_shim___scan_param(shift($@))')dnl
')dnl
dnl ************************
define(
    `define_external_function_with_shim___last_param',
    `ifelse(`$3',`',`ifelse(
    `$2',`...',`regexp(`$1',`\([_a-zA-Z0-9]+\)$',`\1')')',
    `define_external_function_with_shim___last_param(shift($@))')')dnl
dnl ************************
define(
    `define_external_function_with_shim',
    ``
$3 $1('ifelse(`$4',`',`
    void',`define_external_function___scan_param(shift(shift(shift($@))))')`
)
{'ifelse(`$3',`void',,`
    $3 rc = 'ifelse(`$2',`',`0',`$2')`;')ifelse(
    define_external_function_with_shim___last_param(shift(shift(shift($@)))),`',`',``
    va_list args;
    va_start(args, 'define_external_function_with_shim___last_param(shift(shift(shift($@))))`);'')`
    if(g_'THIS_MODULE_NAME`ExternalFunctionEntry_pointer)
    {
        'ifelse(`$3',`void',,`rc = ')`g_'THIS_MODULE_NAME`ExternalFunctionEntry_pointer->$1('ifelse(
    `$4',`',`',`define_external_function_with_shim___scan_param(shift(shift(shift($@))))`
        '')`);
    }'ifelse(
    define_external_function_with_shim___last_param(shift(shift(shift($@)))),`',`',`
    va_end(args);')ifelse(`$3',`void',,`
    return rc;')`
}'dnl
')dnl
dnl ************************
define(
    `external_function_with_shim',
    `define_external_function_with_shim($@)')dnl
dnl ************************
include(`module_defs.m4d')dnl
