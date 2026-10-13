
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

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to MQTT client.
*/

/*****************************************************************************/
/*                               Enums                                       */
/*****************************************************************************/

/*!
** \ingroup mqtt_client
** \brief MQTT client Return codes
*/
enum ltrx_mqtt_client_return_code
{
    LTRX_MQTT_CLIENT_RC__SUCCESS                = 0,  /*!< Success. */
    LTRX_MQTT_CLIENT_RC__INVALID_PARAMETER      = -1,  /*!< Invalid parameter. */
    LTRX_MQTT_CLIENT_RC__INVALID_CONFIG_ITEM    = -2,  /*!< Invalid configuration item. */
    LTRX_MQTT_CLIENT_RC__NOT_ENOUGH_MEMORY      = -3,  /*!< Insufficient memory. */
    LTRX_MQTT_CLIENT_RC__INVALID_STATE          = -4,  /*!< Invalid state. */
    LTRX_MQTT_CLIENT_RC__PROTOCOL_ERROR         = -5,  /*!< Protocol error. */
    LTRX_MQTT_CLIENT_RC__NET_OPEN_FAILURE       = -6,  /*!< Network error. */
    LTRX_MQTT_CLIENT_RC__THREAD_FAILURE         = -7,  /*!< Thread failure. */
    LTRX_MQTT_CLIENT_RC__MQTT_CONNECT_FAILURE   = -8,  /*!< Connect failed. */
    LTRX_MQTT_CLIENT_RC__HTTP_ERROR_RESPONSE    = -9,  /*!< HTTP error received. */
    LTRX_MQTT_CLIENT_RC__OTHER_FAILURE          = -10,  /*!< Unknown error. */
};

/*!
** \ingroup mqtt_client
** \brief MQTT client protocols
*/
enum ltrx_mqtt_client_protocol
{
    LTRX_MQTT_CLIENT_PROTOCOL__UNREGISTERED,  /*!< Unregistered. */
    LTRX_MQTT_CLIENT_PROTOCOL__TCP,  /*!< TCP. */
    LTRX_MQTT_CLIENT_PROTOCOL__TLS,  /*!< TLS. */
    LTRX_MQTT_CLIENT_PROTOCOL__WEBSOCKET,  /*!< Websocket. */
    LTRX_MQTT_CLIENT_PROTOCOL__WEBSOCKET_SECURE,  /*!< Websocket secure. */
    LTRX_MQTT_CLIENT_PROTOCOL_NUM,
};

/*!
** \ingroup mqtt_client
** \brief MQTT QoS levels
*/
enum ltrx_mqtt_qos
{
    LTRX_MQTT_QOS0 = 0,  /*!< At most once. */
    LTRX_MQTT_QOS1 = 1,  /*!< At least once. */
    LTRX_MQTT_QOS2 = 2,  /*!< Exactly once. */
};

/*!
** \ingroup mqtt_client
** \brief Supported MQTT versions
*/
enum ltrx_mqtt_version
{
    LTRX_MQTT_VERSION_3_1 = 3,      /*!< Protocol "MQIsdp" */
    LTRX_MQTT_VERSION_3_1_1 = 4,    /*!< Protocol "MQTT" */
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup mqtt_client
** \brief Contains MQTT client network information.
*/
struct ltrx_mqtt_client_network_info
{
    enum ltrx_mqtt_client_protocol protocol; /*!< Protocol type. */
    const char *host; /*!< Host server name. */
    const char *url; /*!< MQTT service url. */
    uint16_t host_port; /*!< Host port number. */
    uint16_t local_port; /*!< Local port number. */
    const char * const *trusted_auth_array; /*!< Certificate authorities. */
    const char *tls_name; /*!< TLS credential name. */
};

/*!
** \ingroup mqtt_client
** \brief Contains MQTT client connection information.
*/
struct ltrx_mqtt_client_connect_info
{
    const char *client_id; /*!< Client ID. */
    const char *username; /*!< Client user name. */
    const char *password; /*!< Client password. */
    enum ltrx_mqtt_version version; /*!< MQTT version number. */
    bool cleansession; /*!< clean session flag. */
    uint16_t keepalive_interval_sec; /*!< Keep alive interval in seconds. */
};

/*!
** \ingroup mqtt_client
** \brief Contains MQTT client message information.
*/
struct ltrx_mqtt_message
{
    enum ltrx_mqtt_qos qos; /*!< Quality of service level. */
    uint8_t retained; /*!< retained flag bit */
    uint8_t dup; /*!< DUP flag bit */
    uint16_t id; /*!< Message ID */
    const void *payload; /*!< Message payload */
    size_t payloadlen; /*!< Message payload length */
};

/*!
** \ingroup mqtt_client
** \brief MQTT length string
*/
struct ltrx_mqtt_len_string
{
    int len;
    char *data;
};

/*!
** \ingroup mqtt_client
** \brief MQTT string
*/
struct ltrx_mqtt_string
{
    char *cstring;  /*!< string data */
    struct ltrx_mqtt_len_string len_string;  /*!< string length */
};

/*!
** \ingroup mqtt_client
** \brief MQTT message data
*/
struct ltrx_mqtt_message_data
{
    struct ltrx_mqtt_message *message;  /*!< MQTT message */
    struct ltrx_mqtt_string *topic;  /*!< Topic string */
};

typedef void (*ltrx_mqtt_message_handler)(struct ltrx_mqtt_message_data *);

