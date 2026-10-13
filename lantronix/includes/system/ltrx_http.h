
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
** \brief Definitions related to HTTP server.
*/

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

/*!
** \ingroup https
** \brief HTTP server header content types
*/
enum ltrx_http_header_content_type
{
	LTRX_HTTP_HEADER_CONTENT_TYPE__TEXT_PLAIN, /*!< text/plain. */
	LTRX_HTTP_HEADER_CONTENT_TYPE__MULTIPART_FORM_DATA, /*!< multipart/form-data. */
	LTRX_HTTP_HEADER_CONTENT_TYPE__APPLICATION_X_WWW_FORM_URLENCODED, /*!< application/x-www-form-urlencoded. */
	LTRX_HTTP_HEADER_CONTENT_TYPE__OTHERS, /*!< Any other. */
};

/*!
** \ingroup https
** \brief HTTP server header methods
*/
enum ltrx_http_header_method
{
	LTRX_HTTP_HEADER_METHOD__GET, /*!< GET. */
	LTRX_HTTP_HEADER_METHOD__POST, /*!< POST. */
    LTRX_HTTP_HEADER_METHOD__PUT, /*!< PUT. */
    LTRX_HTTP_HEADER_METHOD__DELETE, /*!< DELETE. */
    LTRX_HTTP_HEADER_METHOD__MKCOL, /*!< MKCOL. */
    LTRX_HTTP_HEADER_METHOD__OPTIONS, /*!< OPTIONS. */
	LTRX_HTTP_HEADER_METHOD__OTHERS, /*!< Any other. */
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct ltrx_http_client;
struct ltrx_http_multipart_parse_data;
struct ltrx_write_user_message_info;

struct ltrx_http_ajax
{
    const char *registerName;
    bool (*callback)(struct ltrx_http_client *pClient);
};

/*!
** \ingroup https
** \brief HTTP server dynamic callback
*/
struct ltrx_http_dynamic_callback
{
    const char *uriPath; /*!< Name to register. */
    bool (*callback)(struct ltrx_http_client *client); /*!< Callback function to register. */
    const char *helpText; /*!< Help text for this callback. */
};

/*!
** \ingroup https
** \brief HTTP server query data
*/
struct ltrx_http_query_data
{
	const char *key; /*!< Name to watch for. */
	bool found; /*!< Initially false, to be set true if name found. */
	char *value; /*!< Array to be set with value if found. */
	unsigned int size; /*!< Number of bytes in value array that may be set. */
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_ajax_end_response(
    struct ltrx_http_client *client
);

void ltrx_ajax_register(
    const struct ltrx_http_ajax *ajaxDef
);

void ltrx_ajax_send_xml_end(
    struct ltrx_http_client *client
);

void ltrx_ajax_send_xml_node_encoded(
    struct ltrx_http_client *pClient,
    const char *pTarget,
    const char *pData
);

void ltrx_ajax_send_xml_node_end(
    struct ltrx_http_client *client,
    const char *target
);

void ltrx_ajax_send_xml_node_start(
    struct ltrx_http_client *client,
    const char *target
);

void ltrx_ajax_send_xml_node_unsigned(
    struct ltrx_http_client *client,
    const char *target,
    uint32_t value
);

void ltrx_ajax_send_xml_start(
    struct ltrx_http_client *client,
    const char *target,
    const char *attribute
);

void ltrx_ajax_start_response(
    struct ltrx_http_client *client
);

void ltrx_http_dynamic_callback_register(
    const struct ltrx_http_dynamic_callback *hdc
);

void ltrx_http_error(
    struct ltrx_http_client *pClient
);

enum ltrx_http_header_content_type ltrx_http_get_content_type(
    struct ltrx_http_client *client
);

enum ltrx_http_header_method ltrx_http_get_header_method(
    const struct ltrx_http_client *client
);

const char *ltrx_http_get_request_path(
    const struct ltrx_http_client *client
);

const char *ltrx_http_get_request_query_data(
    const struct ltrx_http_client *client
);

struct ltrx_ip_socket *ltrx_http_get_socket( /* DEPRECATED. See ltrx_http_read_char_from_body_stream() and ltrx_http_send_data_encoded(). */
    const struct ltrx_http_client *client
);

bool ltrx_http_multipart_process(
	struct ltrx_http_client *client,
	struct ltrx_http_query_data *query_data[],
	bool (*unknownKeyHandler)(
        struct ltrx_http_client *client,
        struct ltrx_http_multipart_parse_data *pMultipart_Data,
        const char *key,
        const char *attribute_key,
        void *arg
    ),
	void *arg,
	struct ltrx_write_user_message_info *lwumi
);

int ltrx_http_multipart_read_char(
	struct ltrx_http_client *client,
	struct ltrx_http_multipart_parse_data *pData
);

int ltrx_http_read_char_from_body_stream(
    struct ltrx_http_client *client
);

void ltrx_http_send_data_encoded(
    struct ltrx_http_client *client,
    const char *data
);

void ltrx_http_send_data_flush(
    struct ltrx_http_client *client
);

bool ltrx_http_server_is_user_allowed_to_configure(
    const char *groupName,
    const struct ltrx_write_user_message_info *lwumi
);

int ltrx_get_http_login_failures(void);
#if defined(LANTRONIX_EN18031)
bool isTlsCredentailsPresent(const char *secure_credential);
#endif
