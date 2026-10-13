dnl ************************ EXTERNAL FUNCTION STRUCT DEFINE SECTION ************************
`#pragma GCC diagnostic ignored "-Wtype-limits"

#include "'THIS_MODULE_NAME`_module_defs.h"
#ifndef LTRX_MKCONFIG
#include "ltrx_embedded_files.h"
#include "ltrx_linker.h"
#include "ltrx_module_datetime.h"
#endif

static const struct VaridInfo s_'THIS_MODULE_NAME`VaridEntry[];
#ifndef LTRX_MKCONFIG
static const struct StatusInfo s_'THIS_MODULE_NAME`StatusEntry[];
static const struct 'THIS_MODULE_NAME`_external_functions s_'THIS_MODULE_NAME`ExternalFunctionEntry =
{'dnl
include(`module_defs_clean.m4')dnl
dnl ************************
include(`module_defs.m4d')dnl
dnl ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `define_external_function',
    ``
    $1,'dnl')dnl
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
    $1'ifelse(define_external_function_with_shim___last_param(shift(shift(shift($@)))),`',`',`__internal')`,'dnl')dnl
dnl ************************
define(
    `external_function_with_shim',
    `define_external_function_with_shim($@)')dnl
dnl ************************
include(`module_defs.m4d')dnl
`
};'
dnl ************************ EXTERNAL FUNCTION WITH VARIABLE PARAMETERS SHIM SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `define_external_function___scan_param',
    `ifelse(`$1',`',,``
    $1'ifelse(`$2',`',,`,')define_external_function___scan_param(shift($@))')')dnl
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
    `ifelse(define_external_function_with_shim___last_param(shift(shift(shift($@)))),`',`',``
$3 $1('ifelse(`$4',`',`
    void',`define_external_function___scan_param(shift(shift(shift($@))))')`
)
{'ifelse(`$3',`void',,`
    $3 rc = 'ifelse(`$2',`',`0',`$2')`;')`
    va_list args;
    va_start(args, 'define_external_function_with_shim___last_param(shift(shift(shift($@))))`);
    'ifelse(`$3',`void',,`rc = ')`$1__internal('define_external_function_with_shim___scan_param(shift(shift(shift($@))))`
    );
    va_end(args);'ifelse(`$3',`void',,`
    return rc;')`
}'')dnl
')dnl
dnl ************************
define(
    `external_function_with_shim',
    `define_external_function_with_shim($@)')dnl
dnl ************************
include(`module_defs.m4d')dnl
dnl ************************ VARID IS PRESENT SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `vardef_current_group', `')dnl
dnl ************************
define(
    `vardef_enabled_group__'vardef_current_group,
    `GENERATE')dnl
dnl ************************
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
dnl ************************
define(
    `CONFIG_VALUE_OF_IS_',
    ``ltrx_config_value_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`VaridEntry[VARDEF_ELEMENT_ITEM_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `CONFIG_INSTANCE_OF_IS_',
    ``ltrx_config_instance_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`VaridEntry[VARDEF_ELEMENT_GROUP_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `vardef_begin_index',
    `dnl
define(
    `vardef_current_group',
    format(
        `%s_%s',
        translit(vardef_current_group,`A-Z',`a-z'),
        translit($1,`- /.A-Z',`____a-z')))dnl
define(
    `vardef_enabled_group__'vardef_current_group,
    ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `ifelse(`$4',`',`GENERATE',`ifelse(eval($4),`0',`SUPPRESS',`GENERATE')')',
        vardef_current_generation_state))dnl
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
ifelse(
    vardef_current_generation_state,
    `GENERATE',
    ifelse(
        substr(`$2',`0',`1'),`@',`',
        ifelse(
            `$2',`',`',`
static bool var_group_is_present'vardef_current_group`(uint32_t zeroBasedIndex)
{
    (void)zeroBasedIndex;
    return $2;
}')))dnl
dnl')dnl
dnl ************************
define(
    `vardef_end_index',
    `dnl
define(
    `vardef_current_group',
    substr(
        vardef_current_group,
        0,
        eval(
            len(vardef_current_group)-len(`$1')-1)))dnl
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
dnl')dnl
dnl ************************
include(`module_defs.m4d')dnl
dnl ************************ VARID SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `vardef_current_group', `')dnl
dnl ************************
define(
    `vardef_enabled_group__'vardef_current_group,
    `GENERATE')dnl
dnl ************************
define(
    `vardef_least_significant_bit__'vardef_current_group,
    `0')dnl
dnl ************************
define(
    `vardef_current_least_significant_bit',
    `0')dnl
dnl ************************
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
dnl ************************
define(
    `CONFIG_VALUE_OF_IS_',
    ``ConfigValueOf_Is_(false,zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\",\"$2\")'')
dnl ************************
define(
    `CONFIG_INSTANCE_OF_IS_',
    ``ConfigValueOf_Is_(true,zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\\Instance\",\"$2\")'')
dnl ************************
define(
    `vardef_number_test',
    `ifelse(
        eval(($1) < VARDEF_NUMBER_RANGE_MIN),`1',
        `
#error "__file__:__line__: varid_number must be >= VARDEF_NUMBER_RANGE_MIN"
        ')ifelse(
        eval(($1) > VARDEF_NUMBER_RANGE_MAX),`1',
        `
#error "__file__:__line__: varid_number must be <= VARDEF_NUMBER_RANGE_MAX"
        ')')dnl
dnl ************************
define(
    `vardef_this_offset',
    `ifelse(
        len(vardef_current_group), `0',
        `0',
        `(uint32_t)(&((struct vardef_values'translit(vardef_current_group,`A-Z',`a-z')`*)0)->'translit(
            $1,`- /.A-Z',`____a-z')`)')')dnl
dnl ************************
define(
    `vardef_current_kind',
    `ifelse(
        len(vardef_current_group), `0',
        `VaridKindSinglet',
        ifelse(
            vardef_current_least_significant_bit,
            `0',
            `VaridKindSinglet',
            `VaridKindPacked'))')dnl
dnl ************************
define(
    `vardef_enable_disable',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeEnableDisable,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.enable_disable.default_value = 'ifelse(`$3',`1',`1',`0')`,
    },')dnl')dnl
dnl ************************
define(
    `vardef_text',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeText,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.text.optDefaultValueFunction = 'dnl
ifelse(`$4',`',`0',ifelse(substr(`$4',`0',`1'),`@',substr(`$4',`1'),`0'))`,
        .info.text.default_value = 'dnl
ifelse(substr(`$4',`0',`1'),`@',"","$4")`,
        .info.text.max_length = $3,
        .info.text.textProperty = 'ifelse(`$5',`HIDDEN',`VARID_TEXT_PROPERTY__HIDDEN',ifelse(`$5',`RIGID',`VARID_TEXT_PROPERTY__RIGID',ifelse(`$5',`SECRET',`VARID_TEXT_PROPERTY__SECRET',`VARID_TEXT_PROPERTY__NONE')))`,
        .info.text.optValuesFunction = 'ifdef(`LTRX_MKCONFIG',`0',ifelse(`$5',`SECRET',`NULL',ifelse(`$5',`HIDDEN',`NULL',ifelse(`$5',`RIGID',`NULL',ifelse(`$5',`',`NULL',`$5')))))`
    },')dnl')dnl
dnl ************************
define(
    `vardef_control',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeControl,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.control.default_value = "$4",
        .info.control.max_length = $3
    },')dnl')dnl
dnl ************************
define(
    `vardef_binary',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeBinary,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.binary.default_value = "$4",
        .info.binary.max_length = $3
    },')dnl')dnl
dnl ************************
define(
    `vardef_hexadecimal',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeHexadecimal,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.hexadecimal.default_value = "$4",
        .info.hexadecimal.max_length = $3,
        .info.hexadecimal.is_secret = 'ifelse(`$5',`SECRET',`true',`false')`,
        .info.hexadecimal.legacy_length = 'ifelse(`$6',`',`0',``$6
#if $3 < $6
#error "Varid $1 ($2) maxLength must be >= legacyLength"
#endif'')`
    },')dnl')dnl
dnl ************************
define(
    `vardef_enum',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeEnum,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.enumeration.definition_string = "$3",
        .info.enumeration.default_value = 'ifelse(regexp(`$4',`\<[0-9]'),`0',`$4',`0')`
    },')dnl')dnl
dnl ************************
define(
    `vardef_uint8',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeUint8,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = $3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_sint8',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeSint8,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = (uint32_t)(int32_t)$3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_uint16',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeUint16,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = $3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_sint16',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeSint16,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = (uint32_t)(int32_t)$3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_uint32',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeUint32,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = $3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_sint32',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeSint32,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
        .info.uint.default_value = (uint32_t)(int32_t)$3,
        .info.uint.units = "$4",
        .info.uint.zero_value_represents = "$5"
    },')dnl')dnl
dnl ************************
define(
    `vardef_bitflags',
    `vardef_number_test($1)ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .number = $1,
        .text = "$2",
        .varid_type = VaridTypeBitFlags,
        .varid_kind = 'vardef_current_kind`,
        .offset_in_structure = 'vardef_this_offset(`$2')`,
		.info.bitflags.definition_string = "$3",
        .info.bitflags.default_value = $4
    },')dnl')dnl
dnl ************************
define(
    `vardef_index_information',
    `ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "Instance",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindIndexInformation,
        .info.index_information.isLineOriented = $1,
        .info.index_information.optNameFunction = 'ifelse(`$2',`',`0',`$2')`
    },')dnl')dnl
dnl ************************
define(
    `vardef_summary',
    `ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `
    {
		.text = "Summary",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindSummary,
        .info.summary.writeFunction = ifdef(`LTRX_MKCONFIG',`0',ifelse(`$1',`',`0',`$1'))
    },')dnl')dnl
dnl ************************
define(
    `vardef_begin_index',
    `dnl
define(
    `vardef_group_offset',
    vardef_this_offset(`$1'))dnl
define(
    `vardef_current_group',
    format(
        `%s_%s',
        translit(vardef_current_group,`A-Z',`a-z'),
        translit($1,`- /.A-Z',`____a-z')))dnl
define(
    `vardef_enabled_group__'vardef_current_group,
    ifelse(
        vardef_current_generation_state,
        `GENERATE',
        `ifelse(`$4',`',`GENERATE',`ifelse(eval($4),`0',`SUPPRESS',`GENERATE')')',
        vardef_current_generation_state))dnl
define(
    `vardef_index_of_next_entry__'vardef_current_group,
    ifelse(
        `$3',
        `',
        `',
        `[1]'))dnl
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
ifelse(
    vardef_current_generation_state,
    `GENERATE',
`
/* Begin index $1 */
    {
        .number = (uint16_t)-1,
        .text = "$1",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindBeginIndex,
        .offset_in_structure = 'vardef_group_offset`,
        .info.begin_index.least_significant_bit = 'vardef_current_least_significant_bit`,
        .info.begin_index.size_in_bits = 'ifelse(`$3',`',`0',`$3')`,
        .info.begin_index.dimension = 'ifelse(`$4',`',`0',`$4')`,
        .info.begin_index.opt_is_present_function = 'dnl
ifdef(`LTRX_MKCONFIG',`0',ifelse(`$2',`',`0',ifelse(substr(`$2',`0',`1'),`@',substr(`$2',`1'),`var_group_is_present'vardef_current_group)))`,
        .info.begin_index.opt_is_present_expression = 'dnl
ifdef(`LTRX_MKCONFIG',`0',ifelse(`$2',`',`0',ifelse(substr(`$2',`0',`1'),`@',`0',`"'patsubst(`$2',`\"',`\\"')`"')))`
    },',
`
/* Suppressing index $1 */')dnl
define(
    `vardef_current_least_significant_bit',
    eval($3 + vardef_current_least_significant_bit))dnl
define(
    `vardef_least_significant_bit__'vardef_current_group,
    vardef_current_least_significant_bit)dnl')dnl
dnl ************************
define(
    `vardef_end_index',
    `dnl
define(
    `vardef_current_index_of_next_entry',
    format(`%s',`vardef_index_of_next_entry__'vardef_current_group))dnl
define(`vardef_end_index_group',vardef_current_group)dnl
define(
    `vardef_current_group',
    substr(
        vardef_current_group,
        0,
        eval(
            len(vardef_current_group)-len(`$1')-1)))dnl
ifelse(
    vardef_current_generation_state,
    `GENERATE',`
    {
        .number = (uint16_t)-1,
        .text = "$1",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindEndIndex,
        .offset_in_structure = 'ifelse(
    vardef_current_index_of_next_entry,
    `',
    ifelse(
        len(vardef_current_group), `0',
        `sizeof(struct vardef_values'translit(vardef_end_index_group,`A-Z',`a-z')`)',
        `(uint32_t)((&((struct vardef_values'translit(vardef_current_group,`A-Z',`a-z')`*)0)->'translit(
            $1,`- /.A-Z',`____a-z')`)+1)'),
    ifelse(
        len(vardef_current_group), `0',
        `sizeof(struct vardef_values'translit(vardef_end_index_group,`A-Z',`a-z')`)',
        vardef_this_offset(
            `$1'vardef_current_index_of_next_entry)))`,
        .info.end_index.opt_test_set_function = 'ifelse(
            `$2',`',
            `0',`(
				bool (*)(
					uint32_t,
					void *,
					bool,
					const struct ltrx_write_user_message_info *
				)
			)'ifdef(`LTRX_MKCONFIG',`DummyTestSet',`$2'))`,
        .info.end_index.opt_message_function = 'ifdef(`LTRX_MKCONFIG',`0',ifelse(`$3',`',`0',`$3'))`
    },
/* End index $1 */')dnl
define(
    `vardef_current_generation_state',
    `vardef_enabled_group__'vardef_current_group)dnl
define(
    `vardef_current_least_significant_bit',
    `vardef_least_significant_bit__'vardef_current_group)dnl
dnl')dnl
dnl ************************
`
#endif /* LTRX_MKCONFIG */
static const struct VaridInfo s_'THIS_MODULE_NAME`VaridEntry[] =
{
    {
        .text = "",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindBoundary
    }, /* Initiator */'dnl
dnl ************************
include(`module_defs.m4d')dnl
dnl ************************
`
    {
        .text = "",
        .varid_type = VaridTypeOther,
        .varid_kind = VaridKindBoundary
    } /* Terminator */
};'dnl
dnl ************************************************
dnl ************************ STATUS GROUP IS PRESENT SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `statusdef_current_group', `')dnl
dnl ************************
define(
    `statusdef_enabled_group__'statusdef_current_group,
    `GENERATE')dnl
dnl ************************
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
dnl ************************
define(
    `STATUS_VALUE_OF_IS_',
    ``ltrx_status_value_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`StatusEntry[STATUSDEF_ELEMENT_ITEM_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `STATUS_INSTANCE_OF_IS_',
    ``ltrx_status_instance_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`StatusEntry[STATUSDEF_ELEMENT_GROUP_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `CONFIG_VALUE_OF_IS_',
    ``ltrx_config_value_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`VaridEntry[VARDEF_ELEMENT_ITEM_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `CONFIG_INSTANCE_OF_IS_',
    ``ltrx_config_instance_of_is_(zeroBasedIndex,&s_'THIS_MODULE_NAME`VaridEntry[VARDEF_ELEMENT_GROUP_'translit(`$1',`- /.a-z\',`____A-Z_')`],"$2")'')
dnl ************************
define(
    `statusdef_begin_index',
    `dnl
define(
    `statusdef_current_group',
    format(
        `%s_%s',
        translit(statusdef_current_group,`A-Z',`a-z'),
        translit($1,`- /.A-Z',`____a-z')))dnl
define(
    `statusdef_enabled_group__'statusdef_current_group,
    ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `ifelse(`$4',`',`GENERATE',`ifelse(eval($4),`0',`SUPPRESS',`GENERATE')')',
        statusdef_current_generation_state))dnl
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
ifelse(
    statusdef_current_generation_state,
    `GENERATE',
    ifelse(
        substr(`$2',`0',`1'),`@',`',
        ifelse(
        `$2',`',`',`
static bool status_group_is_present'statusdef_current_group`(uint32_t zeroBasedIndex)
{
    (void)zeroBasedIndex;
    return $2;
}')))dnl
dnl')dnl
dnl ************************
define(
    `statusdef_end_index',
    `dnl
define(
    `statusdef_current_group',
    substr(
        statusdef_current_group,
        0,
        eval(
            len(statusdef_current_group)-len(`$1')-1)))dnl
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
dnl')dnl
`
#ifndef LTRX_MKCONFIG
'
dnl ************************
include(`module_defs.m4d')dnl
`
#endif /* LTRX_MKCONFIG */
'
dnl ************************ STATUS SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
define(
    `statusdef_current_group', `')dnl
dnl ************************
define(
    `statusdef_enabled_group__'statusdef_current_group,
    `GENERATE')dnl
dnl ************************
define(
    `statusdef_least_significant_bit__'statusdef_current_group,
    `0')dnl
dnl ************************
define(
    `statusdef_current_least_significant_bit',
    `0')dnl
dnl ************************
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
dnl ************************
define(
    `CONFIG_VALUE_OF_IS_',
    ``ConfigValueOf_Is_(false,zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\",\"$2\")'')
dnl ************************
define(
    `CONFIG_INSTANCE_OF_IS_',
    ``ConfigValueOf_Is_(true,zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\\Instance\",\"$2\")'')
dnl ************************
define(
    `STATUS_VALUE_OF_IS_',
    ``StatusValueOf_Is_(zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\",\"$2\")'')
dnl ************************
define(
    `STATUS_INSTANCE_OF_IS_',
    ``StatusValueOf_Is_(zeroBasedIndex,\"'patsubst(`$1',`\\',`\\\\')`\\Instance\",\"$2\")'')
dnl ************************
define(
    `statusdef_this_offset',
    `ifelse(
        len(statusdef_current_group), `0',
        `0',
        `(uint32_t)(&((struct statusdef_values'translit(statusdef_current_group,`A-Z',`a-z')`*)0)->'translit(
            $1,`- /.A-Z',`____a-z')`)')')dnl

dnl ************************
define(
    `statusdef_index_information',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "Instance",
        .status_type = StatusTypeIndexInformation,
        .info.index_information.isLineOriented = $1,
        .info.index_information.optNameFunction = 'ifelse(`$2',`',`0',`$2')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_summary',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "Summary",
        .status_type = StatusTypeSummary,
        .info.summary.writeFunction = 'ifdef(`LTRX_MKCONFIG',`0',$1)`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_text',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeText,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.text.max_length = $2,
        .info.text.is_ip_address = 'ifelse(`$3',`IP_ADDRESS',`true',`false')`
    },')dnl')dnl
dnl ************************
dnl ************************
define(
    `statusdef_enum',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeEnum,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.enumeration.definition_string = "$2"
    },')dnl')dnl
dnl ************************
define(
    `statusdef_uint8',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeUint8,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint8.units = "$2",
        .info.uint8.zero_value_represents = "$3",
        .info.uint8.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_sint8',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeSint8,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint8.units = "$2",
        .info.uint8.zero_value_represents = "$3",
        .info.uint8.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_uint16',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeUint16,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint16.units = "$2",
        .info.uint16.zero_value_represents = "$3",
        .info.uint16.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_sint16',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeSint16,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint16.units = "$2",
        .info.uint16.zero_value_represents = "$3",
        .info.uint16.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_uint32',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeUint32,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint32.units = "$2",
        .info.uint32.zero_value_represents = "$3",
        .info.uint32.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_sint32',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeSint32,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.uint32.units = "$2",
        .info.uint32.zero_value_represents = "$3",
        .info.uint32.is_duration = 'ifelse(`$4',`DURATION',`true',`false')`
    },')dnl')dnl
dnl ************************
define(
    `statusdef_counter',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeCounter,
        .offset_in_structure = 'statusdef_this_offset(`$1')`,
        .info.counter.units = "$2"
    },')dnl')dnl
dnl ************************
define(
    `statusdef_action',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeAction,
        .info.action.actionFunction = $2
    },')dnl')dnl
dnl ************************
define(
    `statusdef_set',
    `ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `
    {
        .text = "$1",
        .status_type = StatusTypeSet,
        .info.set.setFunction = $2,
        .info.set.optValues = "$3",
        .info.set.prompt = " 'ifelse(`$4',`',`<value>',`$4')`",
    },')dnl')dnl
dnl ************************
define(
    `statusdef_begin_index',
    `dnl
define(
    `statusdef_group_offset',
    statusdef_this_offset(`$1'))dnl
define(
    `statusdef_current_group',
    format(
        `%s_%s',
        translit(statusdef_current_group,`A-Z',`a-z'),
        translit($1,`- /.A-Z',`____a-z')))dnl
define(
    `statusdef_enabled_group__'statusdef_current_group,
    ifelse(
        statusdef_current_generation_state,
        `GENERATE',
        `ifelse(`$4',`',`GENERATE',`ifelse(eval($4),`0',`SUPPRESS',`GENERATE')')',
        statusdef_current_generation_state))dnl
define(
    `statusdef_index_of_next_entry__'statusdef_current_group,
    ifelse(
        `$3',
        `',
        `',
        `[1]'))dnl
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
ifelse(
    statusdef_current_generation_state,
    `GENERATE',
`
/* Begin index $1 */
    {
        .text = "$1",
        .status_type = StatusTypeBeginIndex,
        .offset_in_structure = 'statusdef_group_offset`,
        .info.begin_index.least_significant_bit = 'statusdef_current_least_significant_bit`,
        .info.begin_index.size_in_bits = 'ifelse(`$3',`',`0',`$3')`,
        .info.begin_index.dimension = 'ifelse(`$4',`',`0',`$4')`,
        .info.begin_index.status_opt_is_present_function = 'dnl
ifdef(`LTRX_MKCONFIG',`0',ifelse(`$2',`',`0',ifelse(substr(`$2',`0',`1'),`@',substr(`$2',`1'),`status_group_is_present'statusdef_current_group)))`,
        .info.begin_index.opt_is_present_expression = 'dnl
ifdef(`LTRX_MKCONFIG',`0',ifelse(`$2',`',`0',ifelse(substr(`$2',`0',`1'),`@',`0',`"'patsubst(`$2',`\"',`\\"')`"')))`
    },',
`
/* Suppressing index $1 */')dnl
define(
    `statusdef_current_least_significant_bit',
    eval($3 + statusdef_current_least_significant_bit))dnl
define(
    `statusdef_least_significant_bit__'statusdef_current_group,
    statusdef_current_least_significant_bit)dnl')dnl
dnl ************************
define(
    `statusdef_end_index',
    `dnl
define(
    `statusdef_current_index_of_next_entry',
    format(`%s',`statusdef_index_of_next_entry__'statusdef_current_group))dnl
define(`statusdef_end_index_group',statusdef_current_group)dnl
define(
    `statusdef_current_group',
    substr(
        statusdef_current_group,
        0,
        eval(
            len(statusdef_current_group)-len(`$1')-1)))dnl
ifelse(
    statusdef_current_generation_state,
    `GENERATE',`
    {
        .text = "$1",
        .status_type = StatusTypeEndIndex,
        .offset_in_structure = 'ifelse(
    statusdef_current_index_of_next_entry,
    `',
    ifelse(
        len(statusdef_current_group), `0',
        `sizeof(struct statusdef_values'translit(statusdef_end_index_group,`A-Z',`a-z')`)',
        `(uint32_t)((&((struct statusdef_values'translit(statusdef_current_group,`A-Z',`a-z')`*)0)->'translit(
            $1,`- /.A-Z',`____a-z')`)+1)'),
    ifelse(
        len(statusdef_current_group), `0',
        `sizeof(struct statusdef_values'translit(statusdef_end_index_group,`A-Z',`a-z')`)',
        statusdef_this_offset(
            `$1'statusdef_current_index_of_next_entry)))`,
        .info.end_index.opt_status_get_function = 'ifelse(`$2',`',`0',`(
			void (*)(
				uint32_t,
				void *,
				const struct ltrx_write_user_message_info *
			)
        )$2')`
    },
/* End index $1 */')dnl
define(
    `statusdef_current_generation_state',
    `statusdef_enabled_group__'statusdef_current_group)dnl
define(
    `statusdef_current_least_significant_bit',
    `statusdef_least_significant_bit__'statusdef_current_group)dnl
dnl')dnl
dnl ************************
`
#ifndef LTRX_MKCONFIG
static const struct StatusInfo s_'THIS_MODULE_NAME`StatusEntry[] =
{
    {
        .text = "",
        .status_type = StatusTypeBoundary
    }, /* Initiator */'dnl
dnl ************************
include(`module_defs.m4d')dnl
dnl ************************
`
    {
        .text = "",
        .status_type = StatusTypeBoundary
    } /* Terminator */
};
#endif /* LTRX_MKCONFIG */'dnl
dnl ************************
dnl ************************ MODULE SECTION ************************
include(`module_defs_clean.m4')dnl
dnl ************************
`
#ifdef LTRX_MKCONFIG
const struct ltrx_module_info g_'THIS_MODULE_NAME`ModuleInfo =
{
	.signature = "LTRX_MODULE",
	.name = "'THIS_MODULE_NAME`",
	.config_table = s_'THIS_MODULE_NAME`VaridEntry
};
#else
__attribute__ ((__section__ (".module_info"))) const struct ltrx_module_info g_'THIS_MODULE_NAME`ModuleInfo =
{
	.signature = "LTRX_MODULE",
	.code_size = (uint32_t)&ltrx_linker_code_size,
	.data_size = (uint32_t)&ltrx_linker_data_size,
	.bss_size = (uint32_t)&ltrx_linker_bss_size,
	.name = "'THIS_MODULE_NAME`",
	.built = g_DateAndTimeOfModuleBuild,
    .module_registration = 'THIS_MODULE_NAME`_module_registration,
	.module_startup = 'THIS_MODULE_NAME`_module_startup,
    .module_shutdown = 'THIS_MODULE_NAME`_module_shutdown,
	.function_entry_points = &s_'THIS_MODULE_NAME`ExternalFunctionEntry,
	.config_table = s_'THIS_MODULE_NAME`VaridEntry,
	.status_table = s_'THIS_MODULE_NAME`StatusEntry,
	.embedded_file_contents = g_Embedded_file_contents
};
#endif'
dnl ************************************************
