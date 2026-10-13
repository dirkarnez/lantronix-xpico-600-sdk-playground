
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2018-2024, Lantronix, Inc. All Rights Reserved.
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
//#include "ltrx_stream.h"

/*****************************************************************************/
/*                               Enums                                       */
/*****************************************************************************/

enum ltrx_websockets_client_return_code
{
    LTRX_WSC_RC__SUCCESS                = 0,
    LTRX_WSC_RC__INVALID_PARAMETER      = -1,
    LTRX_WSC_RC__INVALID_CONFIG_ITEM    = -2,
    LTRX_WSC_RC__NOT_ENOUGH_MEMORY      = -3,
    LTRX_WSC_RC__INVALID_STATE          = -4,
    LTRX_WSC_RC__PROTOCOL_ERROR         = -5,
    LTRX_WSC_RC__NET_OPEN_FAILURE       = -6,
    LTRX_WSC_RC__THREAD_FAILURE         = -7,
    LTRX_WSC_RC__WS_CONNECT_FAILURE     = -8,
    LTRX_WSC_RC__HTTP_ERROR_RESPONSE    = -9,
    LTRX_WSC_RC__OTHER_FAILURE          = -10,
};

enum ltrx_websockets_client_message_opcode
{
    LTRX_WSC_MSG_OPCODE__TEXT = 1,
    LTRX_WSC_MSG_OPCODE__BINARY = 2,
    LTRX_WSC_MSG_OPCODE__CONNECTION_CLOSE = 8,
};

enum ltrx_websockets_status_code
{
    LTRX_WSC_STATUS_CODE__NORMAL_CLOSURE = 1000,
    LTRX_WSC_STATUS_CODE__GOING_AWAY = 1001,
    LTRX_WSC_STATUS_CODE__PROTOCOL_ERROR = 1002,
    LTRX_WSC_STATUS_CODE__UNSUPPORTED_DATA = 1003,
    LTRX_WSC_STATUS_CODE__NO_STATUS_RCVD = 1005,
    LTRX_WSC_STATUS_CODE__ABNORMAL_CLOSURE = 1006,
    LTRX_WSC_STATUS_CODE__INVALID_FRAME_PAYLOAD_DATA = 1007,
    LTRX_WSC_STATUS_CODE__POLICY_VIOLATION = 1008,
    LTRX_WSC_STATUS_CODE__MESSAGE_TOO_BIG = 1009,
    LTRX_WSC_STATUS_CODE__MANDATORY_EXT = 1010,
    LTRX_WSC_STATUS_CODE__INTERNAL_SERVER_ERROR = 1011,
    LTRX_WSC_STATUS_CODE__TLS_HANDSHAKE = 1015
};


/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct ltrx_websockets_client_connect_info
{
    bool secure;
    const char *host;
    const char *url;
    uint16_t host_port;
    uint16_t local_port;
    const char *sec_websocket_protocol;
    const char *optCredential;
};

struct ltrx_websockets_client_message
{
    enum ltrx_websockets_client_message_opcode opcode;
    uint16_t opt_close_code;
    const uint8_t *msg;
    size_t len;
};

/*****************************************************************************/
/*                         Function Prototypes                               */
/*****************************************************************************/
