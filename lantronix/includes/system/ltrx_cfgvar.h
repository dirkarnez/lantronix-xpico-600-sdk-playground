
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2015-2024, Lantronix, Inc. All Rights Reserved.
** By using this software, you are agreeing to the terms of the Software
** Development Kit (SDK) License Agreement included in the distribution package
** for this software (the “License Agreement”).
** Under the License Agreement, this software may be used solely to create
** custom applications for use on the Lantronix xPico Wi-Fi, xPico 200 Series,
** and xPort® Edge products.
** THIS SOFTWARE AND ANY ACCOMPANYING DOCUMENTATION IS PROVIDED "AS IS".
** LANTRONIX SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS
** FOR A PARTICULAR PURPOSE.
** LANTRONIX HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
** ENHANCEMENTS, OR MODIFICATIONS TO THIS SOFTWARE.
** IN NO EVENT SHALL LANTRONIX BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
** SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
** ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
** LANTRONIX HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*****************************************************************************/
/*                             Includes                                      */
/*****************************************************************************/

#include "ltrx_definitions.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to configuration.
*/

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum cfgvar_testset_environment
{
    CFGVAR_TESTSET_ENVIRONMENT__BLUETOOTH,
    CFGVAR_TESTSET_ENVIRONMENT__CLI,
    CFGVAR_TESTSET_ENVIRONMENT__CLI_XML,
    CFGVAR_TESTSET_ENVIRONMENT__CLI_TRUSTED_XML,
    CFGVAR_TESTSET_ENVIRONMENT__MACH10,
    CFGVAR_TESTSET_ENVIRONMENT__WEB_API,
    CFGVAR_TESTSET_ENVIRONMENT__WEB_MANAGER,
    CFGVAR_TESTSET_ENVIRONMENT__AZURE,
    CFGVAR_TESTSET_ENVIRONMENT__AZURE_TRUSTED_XML,
    CFGVAR_TESTSET_ENVIRONMENT__OEM,
    CFGVAR_TESTSET_ENVIRONMENT__UNKNOWN
};

enum VaridType
{
    VaridTypeEnableDisable = 1,
    VaridTypeText,
    VaridTypeControl,
    VaridTypeBinary,
    VaridTypeHexadecimal,
    VaridTypeEnum,
    VaridTypeUint8,
    VaridTypeSint8,
    VaridTypeUint16,
    VaridTypeSint16,
    VaridTypeUint32,
    VaridTypeSint32,
    VaridTypeBitFlags,
    VaridTypeOther
};

enum VaridKind
{
    VaridKindBoundary = 0,
    VaridKindSinglet,
    VaridKindPacked,
    VaridKindIndexInformation,
    VaridKindSummary,
    VaridKindBeginIndex,
    VaridKindEndIndex
};

enum StatusType
{
    StatusTypeBoundary = 0,
    StatusTypeBeginIndex,
    StatusTypeIndexInformation,
    StatusTypeSummary,
    StatusTypeText,
    StatusTypeEnum,
    StatusTypeUint8,
    StatusTypeSint8,
    StatusTypeUint16,
    StatusTypeSint16,
    StatusTypeUint32,
    StatusTypeSint32,
    StatusTypeCounter,
    StatusTypeAction,
    StatusTypeSet,
    StatusTypeEndIndex
};

enum ltrx_user_message_severity
{
    LTRX_USER_MESSAGE_SEVERITY__NOT_APPLICABLE = 0,
    LTRX_USER_MESSAGE_SEVERITY__INFORMATIONAL,
    LTRX_USER_MESSAGE_SEVERITY__WARNING,
    LTRX_USER_MESSAGE_SEVERITY__ERROR,
    LTRX_USER_MESSAGE_SEVERITY__CONFIRM,
    LTRX_USER_MESSAGE_SEVERITY__EPHEMERAL,
    LTRX_USER_MESSAGE_SEVERITY__RESULT,
};

/*!
** \ingroup xml_export
** \brief Selects type of XML value to emit.
*/
enum xml_emit_value_type
{
    XML_EMIT_VALUE_TYPE__CONFIGURATION = 0, /*!< Emit an XML configuration value. */
    XML_EMIT_VALUE_TYPE__STATUS = 1 /*!< Emit an XML status value. */
};

enum varid_text_property
{
    VARID_TEXT_PROPERTY__NONE = 0,
    VARID_TEXT_PROPERTY__HIDDEN,
    VARID_TEXT_PROPERTY__RIGID,
    VARID_TEXT_PROPERTY__SECRET
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct cli_thread_info;

struct main_external_functions;

struct output_stream;

struct input_stream;

struct StatusInfo;

struct ltrx_mutex{
    OPAQUE_STRUCT(4);
};

struct ltrx_trigger{
    OPAQUE_STRUCT(28);
};

struct ltrx_xml_import_context
{
    bool authenticatedImportControlPassword;
    uint8_t pass;
};

struct ltrx_write_user_message_type_cli_info
{
    int (*confirm)(struct cli_thread_info *cti);
    size_t (*prompt)(
        struct cli_thread_info *cti,
        const char *prompt,
        char *buffer,
        size_t bufferSize,
        bool isHidden
    );
    struct cli_thread_info *cti;
};

struct ltrx_write_user_message_type_web_manager_info
{
    char confirms[20];
};

union ltrx_write_user_message_type_specific_info
{
    struct ltrx_write_user_message_type_cli_info cli;
    struct ltrx_write_user_message_type_web_manager_info webManager;
};

/*!
** \brief Abstract reference to environment.
*/
struct ltrx_write_user_message_info
{
    enum cfgvar_testset_environment env;
    bool isTlogOutput;
    void (*optStatusContainedShow)(
        uint32_t zeroBasedIndex,
        const struct StatusInfo *s,
        const struct ltrx_write_user_message_info *lwumi
    );
    struct cli_thread_info *optCliThreadInfo;
    struct ltrx_xml_import_context *optXmlImportContext;
    void (*writeBegin)(
        enum ltrx_user_message_severity severity,
        void *pOpaque
    );
    void (*writeMessage)(const char *message, size_t length, void *pOpaque);
    void (*writeEnd)(
        enum ltrx_user_message_severity severity,
        void *pOpaque
    );
    void *pOpaque;
    union ltrx_write_user_message_type_specific_info typeSpecificInfo;
};

/* The following struct provides pointer access to type binary of any size */
struct varid_type_binary {
    uint16_t length;
    uint8_t data[1];
};

struct VaridTypeInfo_BeginIndex
{
    uint8_t least_significant_bit;
    uint8_t size_in_bits;
    uint16_t dimension;
    bool (*opt_is_present_function)(uint32_t zeroBasedIndex);
    const char *opt_is_present_expression;
};

struct VaridTypeInfo_EnableDisable
{
    bool default_value;
};

struct VaridTypeInfo_Text
{
    const char *default_value;
    const char *(*optDefaultValueFunction)(unsigned int zeroBasedIndex);
    uint16_t max_length;
    enum varid_text_property textProperty;
    const char *(*optValuesFunction)(unsigned int zeroBasedIterator);
};

struct VaridTypeInfo_Control
{
    const char *default_value;
    uint16_t max_length;
};

struct VaridTypeInfo_Binary
{
    const char *default_value;
    uint16_t max_length;
};

struct VaridTypeInfo_Hexadecimal
{
    const char *default_value;
    uint16_t max_length;
    uint16_t legacy_length;
    bool is_secret;
};

struct VaridTypeInfo_Enum
{
    const char *definition_string;
    uint8_t default_value;
};

struct VaridTypeInfo_Uint
{
    uint32_t default_value;
    const char *units;
    const char *zero_value_represents;
};

struct VaridTypeInfo_BitFlags
{
    const char *definition_string;
    uint32_t default_value;
};

struct VaridTypeInfo_IndexInformation
{
    bool isLineOriented;
    const char *(*optNameFunction)(unsigned int zeroBasedIndex);
};

struct VaridTypeInfo_Summary
{
    bool (*writeFunction)(
        uint32_t zeroBasedIndex,
        struct output_stream *out
    );
};

struct VaridTypeInfo_EndIndex
{
    bool (*opt_test_set_function)(
        uint32_t zeroBasedIndex,
        void *config,
        bool set,
        const struct ltrx_write_user_message_info *lwumi
    );
    void (*opt_message_function)(
        uint32_t zeroBasedIndex,
        const struct ltrx_write_user_message_info *lwumi
    );
};

union VaridTypeInfo
{
    struct VaridTypeInfo_BeginIndex begin_index;
    struct VaridTypeInfo_EnableDisable enable_disable;
    struct VaridTypeInfo_Text text;
    struct VaridTypeInfo_Control control;
    struct VaridTypeInfo_Binary binary;
    struct VaridTypeInfo_Hexadecimal hexadecimal;
    struct VaridTypeInfo_Enum enumeration;
    struct VaridTypeInfo_Uint uint;
    struct VaridTypeInfo_BitFlags bitflags;
    struct VaridTypeInfo_IndexInformation index_information;
    struct VaridTypeInfo_Summary summary;
    struct VaridTypeInfo_EndIndex end_index;
};

struct VaridInfo
{
    uint16_t number;
    const char *text;
    enum VaridType varid_type;
    enum VaridKind varid_kind;
    size_t offset_in_structure;
    union VaridTypeInfo info;
};

struct StatusTypeInfo_BeginIndex
{
    uint8_t least_significant_bit;
    uint8_t size_in_bits;
    uint16_t dimension;
    bool (*status_opt_is_present_function)(uint32_t zeroBasedIndex);
    const char *opt_is_present_expression;
};

struct StatusTypeInfo_EndIndex
{
    void (*opt_status_get_function)(
        uint32_t zeroBasedIndex,
        void *status,
        const struct ltrx_write_user_message_info *lwumi
    );
};

struct StatusTypeInfo_IndexInformation
{
    bool isLineOriented;
    const char *(*optNameFunction)(unsigned int zeroBasedIndex);
};

struct StatusTypeInfo_Summary
{
    bool (*writeFunction)(
        const void *status,
        struct output_stream *out
    );
};

struct StatusTypeInfo_Text
{
    uint16_t max_length;
    bool is_ip_address;
};

struct StatusTypeInfo_Enum
{
    const char *definition_string;
};

struct StatusTypeInfo_Uint8
{
    const char *units;
    const char *zero_value_represents;
    bool is_duration;
};

struct StatusTypeInfo_Uint16
{
    const char *units;
    const char *zero_value_represents;
    bool is_duration;
};

struct StatusTypeInfo_Uint32
{
    const char *units;
    const char *zero_value_represents;
    bool is_duration;
};

struct StatusTypeInfo_Counter
{
    const char *units;
};

struct StatusTypeInfo_Action
{
    bool (*actionFunction)(
        uint32_t zeroBasedIndex,
        const struct ltrx_write_user_message_info *lwumi
    );
};

struct StatusTypeInfo_Set
{
    bool (*setFunction)(
        uint32_t zeroBasedIndex,
        const char *value,
        const struct ltrx_write_user_message_info *lwumi
    );
    const char *optValues;
    const char *prompt;
};

union StatusTypeInfo
{
    struct StatusTypeInfo_BeginIndex begin_index;
    struct StatusTypeInfo_EndIndex end_index;
    struct StatusTypeInfo_IndexInformation index_information;
    struct StatusTypeInfo_Summary summary;
    struct StatusTypeInfo_Text text;
    struct StatusTypeInfo_Enum enumeration;
    struct StatusTypeInfo_Uint8 uint8;
    struct StatusTypeInfo_Uint16 uint16;
    struct StatusTypeInfo_Uint32 uint32;
    struct StatusTypeInfo_Counter counter;
    struct StatusTypeInfo_Action action;
    struct StatusTypeInfo_Set set;
};

struct StatusInfo
{
    const char *text;
    enum StatusType status_type;
    size_t offset_in_structure;
    union StatusTypeInfo info;
};

struct ltrx_message_to_tlog
{
    struct ltrx_write_user_message_info lwumi;
    size_t length;
    size_t line;
    char message[47];
    enum ltrx_user_message_severity severity;
    struct ltrx_xml_import_context lxic;
};

/*!
** \ingroup xml_export
** \brief Specifies a value to emit.
**
** Used with ltrx_xml_emit_value to specify which XML value is being selected.
*/
struct xml_emit_value_specification
{
    enum xml_emit_value_type type;  /*!< Designates either configuration or status emit. */
    const char *groupName;          /*!< XML name attribute of group tag. */
    uint16_t optGroupInstanceNumber; /*!< Option to read the Nth group instance text. */
    const char *optGroupInstance;   /*!< Optional XML instance attribute of group tag. */
    const char *itemName;           /*!< XML name attribute of item tag. */
    uint16_t optItemInstanceNumber; /*!< Option to read the Nth item instance text. */
    const char *optItemInstance;    /*!< Optional XML instance attribute of item tag. */
    const char *optValueName;       /*!< Optional XML name attribute of value tag. */
    bool omitUnits;                 /*!< Optionally omit units when emitting the value. */
};

struct ltrx_module_info
{
    const char signature[12];
    uint32_t code_size;
    uint32_t data_size;
    uint32_t bss_size;
    const char *name;
    const char *built;
    void (*module_registration)(void);
    void (*module_startup)(void);
    void (*module_shutdown)(void);
    const void *function_entry_points;
    const struct VaridInfo *config_table;
    const struct StatusInfo *status_table;
    const struct ltrx_embedded_file * const *embedded_file_contents;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_cfg_flash_save(void);

bool ltrx_cfgvar_delete_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v
);

bool ltrx_cfgvar_get_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    void *pDesignatedVar
);

bool ltrx_cfgvar_get_default_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    void *pDesignatedVar
);

bool ltrx_cfgvar_get_factory_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    void *pDesignatedVar
);

bool ltrx_cfgvar_get_lantronix_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    void *pDesignatedVar
);

bool ltrx_cfgvar_send_cached_value(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    struct output_stream *os
);

bool ltrx_cfgvar_set_data(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *v,
    const void *pDesignatedVar
);

bool ltrx_config_instance_of_is_(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *varid_info,
    const char *value
);

bool ltrx_config_intergroup_get_data(
    const struct ltrx_write_user_message_info *lwumi,
    uint32_t zeroBasedIndex,
    const char *moduleName,
    size_t vardefIndex,
    void *pDesignatedVar
);

bool ltrx_config_value_of_is_(
    uint32_t zeroBasedIndex,
    const struct VaridInfo *varid_info,
    const char *value
);

const void *ltrx_module_functions_lookup(
    const char *module_name
);

void ltrx_module_register(
    const struct ltrx_module_info *lmi
);

const struct ltrx_module_info *ltrx_module_lookup(
    const char *module_name
);

bool ltrx_initialize_message_to_tlog(
    struct ltrx_message_to_tlog *mtot
);

bool ltrx_status_instance_of_is_(
    uint32_t zeroBasedIndex,
    const struct StatusInfo *s,
    const char *value
);

bool ltrx_status_value_of_is_(
    uint32_t zeroBasedIndex,
    const struct StatusInfo *s,
    const char *value
);

bool ltrx_write_user_message(
    const struct ltrx_write_user_message_info *lwumi,
    enum ltrx_user_message_severity severity,
    const char *message,
    ...
);

bool ltrx_xml_emit_value(
    const struct xml_emit_value_specification *xevs,
    struct output_stream *out
);
