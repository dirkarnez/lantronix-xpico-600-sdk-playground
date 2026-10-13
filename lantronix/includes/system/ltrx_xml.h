
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
#include <stddef.h>
#include <stdint.h>

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to XML.
*/

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct input_stream;

struct ltrx_write_user_message_info;

struct ltrx_xml_export
{
    struct input_stream *optIn;
    struct output_stream *out;
    const struct ltrx_write_user_message_info *lwumi;
    const char *lines;
    const char *groups;
    bool secrets;
    bool withUnits;
    bool onlyNonDefault;
    bool suppressDtdHeader;
    bool suppressIndentation;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_xml_import_from_stream(
    struct input_stream *in,
    const struct ltrx_write_user_message_info *lwumi
);

bool ltrx_xml_trusted_import_from_stream(
    struct input_stream *in,
    const struct ltrx_write_user_message_info *lwumi
);

bool ltrx_xml_config_export(
    struct ltrx_xml_export *params
);

bool ltrx_xml_status_export(
    struct ltrx_xml_export *params
);

bool ltrx_xml_contained_status_export(
    struct output_stream *out,
    uint32_t baseIndex,
    const struct StatusInfo *s,
    bool withUnits
);

#if defined(LANTRONIX_EN18031)
bool IsConfiggroupAllowedToConfigure(
    const char *groupName,
    const struct ltrx_write_user_message_info *lwumi
);
#endif
