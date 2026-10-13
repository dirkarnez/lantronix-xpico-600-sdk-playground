
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
#include "ltrx_stream.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to HTTP client.
*/

/*****************************************************************************/
/*                               Enums                                       */
/*****************************************************************************/

/*!
** \ingroup httpc
** \brief HTTP client Return codes
*/
enum ltrx_httpc_return_code
{
    LTRX_HTTPC_RC__SUCCESS              = 0, /*!< Success. */
    LTRX_HTTPC_RC__INVALID_PARAMETER    = -1, /*!< Invalid parameter. */
    LTRX_HTTPC_RC__NOT_ENOUGH_MEMORY    = -2, /*!< Insufficient memory. */
    LTRX_HTTPC_RC__INVALID_STATE        = -3, /*!< Invalid state. */
    LTRX_HTTPC_RC__CONNECT_FAILED       = -4, /*!< Connect failed. */
    LTRX_HTTPC_RC__PROTOCOL_ERROR       = -5, /*!< Protocol error. */
    LTRX_HTTPC_RC__HTTP_ERROR_RESPONSE  = -6, /*!< HTTP error response. */
    LTRX_HTTPC_RC__OTHER_FAILURE        = -7, /*!< Unknown error. */
};

/*!
** \ingroup httpc
** \brief HTTP client methods
*/
enum ltrx_httpc_method
{
    LTRX_HTTPC_METHOD__UNSPECIFIED, /*!< Unspecified method (can be specified later). */
    LTRX_HTTPC_METHOD__POST, /*!< POST method. */
    LTRX_HTTPC_METHOD__GET, /*!< GET method. */
    LTRX_HTTPC_METHOD__PUT, /*!< PUT method. */
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup httpc
** \brief HTTP client header
*/
struct ltrx_http_client_header
{
    const char *name; /*!< Name. */
    const char *value; /*!< Value. */
};

/*!
** \ingroup httpc
** \brief HTTP client connect information
*/
struct ltrx_http_client_connect_info
{
    const char *host; /*!< Host name to connect to. */
    const char *url; /*!< URL to connect to. */
    uint16_t host_port; /*!< Host port to connect to. */
    uint16_t local_port; /*!< Local port to use when connecting or zero for random. */
    struct ltrx_ip_socket *optional_socket; /*< Optional socket if TCP layer already connected. */
};

struct ltrx_http_client_request;

struct input_stream_from_httpc_request
{
    struct input_stream inStream;
    struct ltrx_http_client_request *hcr;
    bool headersComplete;
    bool haveData;
    uint8_t data;
    bool isClosed;
};

struct output_stream_to_httpc_request
{
    struct output_stream outStream;
    struct ltrx_http_client_request *hcr;
    uint16_t bufferUsed;
    uint8_t *buffer;
    bool isClosed;
};

/*****************************************************************************/
/*                         Function Prototypes                               */
/*****************************************************************************/

const char *ltrx_httpc_strerror(enum ltrx_httpc_return_code);

struct ltrx_http_client_request *ltrx_httpc_request_create(
    enum ltrx_httpc_method method
);

enum ltrx_httpc_return_code ltrx_httpc_request_clear(
    struct ltrx_http_client_request *handle
);

void ltrx_httpc_request_destroy(
    struct ltrx_http_client_request *handle
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_method(
    struct ltrx_http_client_request *handle,
    enum ltrx_httpc_method method
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_connect_info(
    struct ltrx_http_client_request *handle,
    const struct ltrx_http_client_connect_info *info
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_user_agent(
    struct ltrx_http_client_request *handle,
    const char *userAgent
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_tls_credential(
    struct ltrx_http_client_request *handle,
    const char *credentialName
);

enum ltrx_httpc_return_code ltrx_httpc_request_add_tls_authority(
    struct ltrx_http_client_request *handle,
    const char *authorityPemCertificate
);

enum ltrx_httpc_return_code ltrx_httpc_request_add_header(
    struct ltrx_http_client_request *handle,
    struct ltrx_http_client_header *httpHeader
);

enum ltrx_httpc_return_code ltrx_httpc_request_add_mime_type(
    struct ltrx_http_client_request *handle,
    const char *mimeType
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_response_inactivity_timeout(
    struct ltrx_http_client_request *handle,
    uint32_t timeoutMsec
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_100continue_timeout(
    struct ltrx_http_client_request *handle,
    uint32_t timeoutMsec
);

/* Request I/O execution (connect/send/receive/disconnect) */
enum ltrx_httpc_return_code ltrx_httpc_request_connect_and_send_headers(
    struct ltrx_http_client_request *handle
);

enum ltrx_httpc_return_code ltrx_httpc_request_send_content(
    struct ltrx_http_client_request *handle
);

enum ltrx_httpc_return_code ltrx_httpc_request_receive(
    struct ltrx_http_client_request *handle
);

enum ltrx_httpc_return_code ltrx_httpc_request_disconnect(
    struct ltrx_http_client_request *handle
);

/* This function runs through all the I/O functions above */
enum ltrx_httpc_return_code ltrx_httpc_request_execute(
    struct ltrx_http_client_request *handle
);

/* External streams interface */
bool ltrx_input_stream_init_from_httpc_request(
    struct input_stream_from_httpc_request *inStream,
    struct ltrx_http_client_request *handle
);

bool ltrx_output_stream_init_to_httpc_request(
    struct output_stream_to_httpc_request *outStream,
    struct ltrx_http_client_request *handle
);

/*
** HTTP Content Output (POST/PUT request) options.
** These are mutually exclusive.
*/
enum ltrx_httpc_return_code ltrx_httpc_request_set_write_buffer(
    struct ltrx_http_client_request *handle,
    const void *buffer,
    size_t bufferSize
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_write_function(
    struct ltrx_http_client_request *handle,
    void (*writeCallback)(
        const uint8_t **datap, 
        size_t *sizep, 
        void *opaque
    ),
    void *writeCallbackOpaque
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_write_stream(
    struct ltrx_http_client_request *handle,
    struct input_stream *inStream
);

/*
** HTTP Content Input (GET/POST/PUT response)
** These are mutually exclusive.
*/
enum ltrx_httpc_return_code ltrx_httpc_request_set_response_buffer_malloc(
    struct ltrx_http_client_request *handle,
    uint8_t **bufferp,
    size_t optResponseSizeEstimate
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_response_callback(
    struct ltrx_http_client_request *handle,
    bool (*readCallback)(
        struct ltrx_http_client_request *handle,
        void *opaque,
        const void *data,
        size_t size
    ),
    void *readCallbackOpaque
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_response_stream(
    struct ltrx_http_client_request *handle,
    struct output_stream *outStream
);

/* Response header values */
enum ltrx_httpc_return_code ltrx_httpc_request_get_status_code(
    struct ltrx_http_client_request *handle,
    uint32_t *optStatusNumber,
    char *optStatusStringBuf,
    size_t *optStatusStringBufLengthp
);

enum ltrx_httpc_return_code ltrx_httpc_request_get_content_length(
    struct ltrx_http_client_request *handle,
    uint32_t *length
);

#ifdef USE_WEBSOCKETS
int ltrx_httpc_request_get_connection_upgrade(
    struct ltrx_http_client_request *hcr,
    bool *value
);

int ltrx_httpc_request_get_upgrade_websocket(
    struct ltrx_http_client_request *hcr,
    bool *value
);

int ltrx_httpc_request_get_sec_websocket_accept(
    struct ltrx_http_client_request *hcr,
    char *buffer,
    size_t *buffer_lengthp
);

int ltrx_httpc_request_get_sec_websocket_protocol(
    struct ltrx_http_client_request *hcr,
    char *buffer,
    size_t *buffer_lengthp
);

int ltrx_httpc_request_get_network_handles(
    struct ltrx_http_client_request *hcr,
    struct ltrx_ip_socket **socket,
    const struct ltrx_network_protocol **lnp,
    struct ltrx_network_protocol_handle **lnph
);
#endif

/* Debug */

enum ltrx_httpc_return_code ltrx_httpc_request_set_log_verbosity(
    struct ltrx_http_client_request *handle,
    uint8_t verbosityLevel
);

enum ltrx_httpc_return_code ltrx_httpc_request_get_log_verbosity(
    struct ltrx_http_client_request *handle,
    uint8_t *verbosityLevel
);

enum ltrx_httpc_return_code ltrx_httpc_request_set_debug(
    struct ltrx_http_client_request *handle, 
    bool dumpSend,
    bool dumpReceive
);
