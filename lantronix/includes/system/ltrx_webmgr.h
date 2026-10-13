
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

/*****************************************************************************/
/*                              Structs                                      */
/*****************************************************************************/

struct ltrx_http_client;
struct ltrx_write_user_message_info;

struct ltrx_webmgr_message_info
{
    struct ltrx_http_client *http_client;
    const char *current_group;
    const char *current_instance;
    bool isAction;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_webmgr_init_js_register(
    const char *javascriptFilename
);

void ltrx_webmgr_initialize_write_user_message_info(
    struct ltrx_write_user_message_info *lwumi,
    struct ltrx_webmgr_message_info *wmi
);
