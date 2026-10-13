
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

#include <stdbool.h>
#include <stdint.h>

/*****************************************************************************/
/*                              Macros                                       */
/*****************************************************************************/

#define LTRX_JSON_BADARG            -1
#define LTRX_JSON_NOMEM             -2
#define LTRX_JSON_TEXT_INVALID      -3
#define LTRX_JSON_TEXT_INCOMPLETE   -4

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum ltrx_json_type
{
    LTRX_JSON_TYPE__PRIMITIVE,
    LTRX_JSON_TYPE__STRING,
    LTRX_JSON_TYPE__OBJECT,
    LTRX_JSON_TYPE__ARRAY,
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct ltrx_json_token
{
    enum ltrx_json_type ljt_type;
    size_t ljt_size;
    uint32_t ljt_private;
    const char *ljt_key_start;
    const char *ljt_key_end;
    const char *ljt_value_start;
    const char *ljt_value_end;
};

struct ltrx_json_handle;

struct m10_json_parse_value
{
    const char *jpv_name;
    enum ltrx_json_type jpv_type;
#define jpv_strp jpv_value.jv_strp
#define jpv_nump jpv_value.jv_nump
#define jpv_parsefcn jpv_value.jv_parsefcn
    union
    {
        char **jv_strp;
        uint32_t *jv_nump;
        bool (*jv_parsefcn)(
            struct ltrx_json_handle *, struct ltrx_json_token *, void *
        );
    } jpv_value;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

struct ltrx_json_handle *ltrx_json_init(void);

void ltrx_json_term(struct ltrx_json_handle *ljh);

int ltrx_json_parse(
    struct ltrx_json_handle *ljh, 
    const char *json, 
    size_t jsonLength
);

bool ltrx_json_get_object_token_from_name(
    struct ltrx_json_handle *ljh,
    const struct ltrx_json_token *optParent,
    const char *keyName,
    struct ltrx_json_token *ljt
);

bool ltrx_json_iterate_object(
    struct ltrx_json_handle *ljh,
    const struct ltrx_json_token *object,
    int *iterator,
    struct ltrx_json_token *ljt
);

bool ltrx_json_get_array_token_from_name(
    struct ltrx_json_handle *ljh,
    struct ltrx_json_token *optParent,
    const char *keyName,
    int arrayIndex,
    struct ltrx_json_token *ljt
);

bool ltrx_json_get_array_token_from_token(
    struct ltrx_json_handle *ljh,
    const struct ltrx_json_token *array,
    int arrayIndex,
    struct ltrx_json_token *ljt
);

const char *ltrx_json_strtype(enum ltrx_json_type);
