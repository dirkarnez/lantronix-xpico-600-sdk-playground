
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

#include "ltrx_cfgvar.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to streams.
*/

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

/*!
** \ingroup utilities
** \brief Mode of a buffer output stream.
*/
enum output_stream_to_buffer_mode {
    /*! Binary mode allows any data values. */
	OUTPUT_STREAM_TO_BUFFER_MODE__BINARY,
    /*!
    ** Zero-terminate mode allows only non-zero data and terminates
    ** with a zero byte.
    */
	OUTPUT_STREAM_TO_BUFFER_MODE__ZERO_TERMINATE
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \brief Abstract reference to an input stream.
*/
struct input_stream
{
    /* Blocking read from an input stream. Returns < 0 disconnected. */
    int (*readCharacter)(
        struct input_stream *inStream
    );
    /* Blocking peek. Returns -1 wait, -2 disconnected.*/
    int (*peekCharacter)(
        struct input_stream *inStream,
        uint32_t blockTimeMsec
    );
    /* Destructor. */
    void (*inputClose)(
        struct input_stream *inStream
    );
};

struct input_stream_from_const_char
{
    struct input_stream inStream;
    const unsigned char *p;
};

struct input_stream_from_binary
{
    struct input_stream inStream;
    const uint8_t *p;
    void *optAllocatedMemory;
    size_t n;
};

/*!
** \ingroup file_system
** \brief Concrete struct for a file input stream.
*/
struct input_stream_from_file
{
    struct input_stream inStream; /*!< Abstract input stream. */
    int fd;
    int limitInBytes;
    int bytesRead;
    unsigned long lineNumber;
    char optNewLineCharacter;
    bool prohibitCloseOfFd;
};

/*!
** \ingroup tcp
** \brief Concrete struct for a tcp input stream.
*/
struct input_stream_from_open_tcp_socket
{
    struct input_stream inStream; /*!< Abstract input stream. */
    struct ltrx_ip_socket *lis;
    bool haveData;
    uint8_t data;
    bool isClosed;
};

/*!
** \ingroup network_protocols
** \brief Concrete struct for an abstract network protocol input stream.
*/
struct input_stream_from_open_abstract_socket
{
    struct input_stream inStream;
    struct ltrx_ip_socket *lis;
    const struct ltrx_network_protocol *lnp;
    struct ltrx_network_protocol_handle *lnph;
    bool haveData;
    uint8_t data;
    bool isClosed;
};

/*!
** \ingroup serial_line
** \brief Concrete struct for a Serial Line input stream.
*/
struct input_stream_from_uart
{
    struct input_stream inStream; /*!< Abstract input stream. */
    unsigned int zeroBasedIndex;
    bool haveBufferedCharacter;
    bool isClosed;
    unsigned char c;
};

struct input_stream_from_varid
{
    union
    {
        struct input_stream inStream; /*!< Abstract input stream. */
        struct input_stream_from_file file;
        struct input_stream_from_binary binary;
    } choice;
};

/*!
** \brief Abstract reference to an output stream.
*/
struct output_stream
{
    /* Blocking write to an output stream. Returns false for failure. */
    bool (*writeData)(
        struct output_stream *outStream,
        const char *data, size_t length
    );
    /* Blocking write to an output stream. Returns false for failure. */
    bool (*writeNewline)(struct output_stream *outStream);
    /* Forces any buffered data to be actually output. */
    bool (*flushData)(struct output_stream *outStream);
    /* Destructor. */
    bool (*outputClose)(struct output_stream *outStream);
    uint16_t lineCount;
};

/*!
** \ingroup utilities
** \brief Concrete struct for a buffer output stream.
*/
struct output_stream_to_buffer
{
    struct output_stream outStream; /*!< Abstract output stream. */
    char *buffer;
    size_t bufferLength;
    size_t bytesNeeded;
	enum output_stream_to_buffer_mode mode;
};

/*!
** \ingroup file_system
** \brief Concrete struct for a file output stream.
*/
struct output_stream_to_file
{
    struct output_stream outStream; /*!< Abstract output stream. */
    int fd;
    size_t allocatedBufferSize;
    size_t bytesHeld;
    char *optAllocatedBuffer;
};

/*!
** \ingroup tcp
** \brief Concrete struct for a tcp output stream.
*/
struct output_stream_from_open_tcp_socket
{
    struct output_stream outStream; /*!< Abstract output stream. */
    struct ltrx_ip_socket *lis;
    bool isClosed;
};

/*!
** \ingroup network_protocols
** \brief Concrete struct for a network protocol output stream.
*/
struct output_stream_to_open_abstract_socket
{
    struct output_stream outStream; /*!< Abstract output stream. */
    struct ltrx_ip_socket *lis;
    const struct ltrx_network_protocol *lnp;
    struct ltrx_network_protocol_handle *lnph;
    bool isClosed;
};

/*!
** \ingroup serial_line
** \brief Concrete struct for a Serial Line output stream.
*/
struct output_stream_to_uart
{
    struct output_stream outStream; /*!< Abstract output stream. */
    unsigned int zeroBasedIndex;
    bool isClosed;
};

struct output_stream_to_count
{
    struct output_stream outStream;
    uint32_t count;
    bool isClosed;
};

struct output_stream_to_message
{
    struct output_stream outStream;
    const struct ltrx_write_user_message_info *lwumi;
    enum ltrx_user_message_severity severity;
};

struct message_to_output_stream
{
    struct ltrx_write_user_message_info lwumi;
    struct output_stream *outStream;
};

/*!
** \brief Concrete struct for an abstract routine input stream.
*/
struct input_stream_from_routine
{
    struct input_stream inStream;
    struct output_stream outStream;
    void (*routine)(
        struct output_stream *os,
        void *opaque
    );
    struct ltrx_trigger out_to_in;
    struct ltrx_trigger in_to_out;
    void *userOpaque;
    const uint8_t *p;
    size_t n;
    bool isEof;
    bool isClosed;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_cli_command_loop(
    struct input_stream *is,
    struct output_stream *os,
    const bool *isRunning,
    bool echoIsOn
);

struct input_stream *ltrx_cli_get_input_stream(
    struct cli_thread_info *cti
);

struct output_stream *ltrx_cli_get_output_stream(
    struct cli_thread_info *cti
);

void ltrx_input_stream_close(
    struct input_stream *inStream
);

int ltrx_input_stream_case_compare(
    struct input_stream *s1,
    struct input_stream *s2
);

int ltrx_input_stream_compare(
    struct input_stream *s1,
    struct input_stream *s2
);

bool ltrx_input_stream_init_from_binary(
    struct input_stream_from_binary *inStream,
    const void *data,
    size_t length
);

bool ltrx_input_stream_init_from_const_char(
    struct input_stream_from_const_char *inStream,
    const char *data
);

bool ltrx_input_stream_init_from_file(
    struct input_stream_from_file *inStream,
    const char *fileName
);

bool ltrx_input_stream_init_from_open_tcp_socket(
    struct input_stream_from_open_tcp_socket *inStream,
    struct ltrx_ip_socket *lis
);

bool ltrx_input_stream_init_from_open_abstract_socket(
    struct input_stream_from_open_abstract_socket *inStream,
    struct ltrx_ip_socket *lis,
    const struct ltrx_network_protocol *lnp,
    struct ltrx_network_protocol_handle *lnph
);

bool ltrx_input_stream_init_from_routine(
    struct input_stream_from_routine *inStream,
    const char *thread_name,
    uint32_t stack_size,
    void (*routine)(
        struct output_stream *os,
        void *opaque
    ),
    void *opaque
);

bool ltrx_input_stream_init_from_uart(
    struct input_stream_from_uart *inStream,
    unsigned int zeroBasedIndex
);

int ltrx_input_stream_peek(
    struct input_stream *inStream
);

int ltrx_input_stream_peek_with_block_time(
    struct input_stream *inStream,
    uint32_t blockTimeMsec
);

int ltrx_input_stream_read(
    struct input_stream *inStream
);

bool ltrx_output_stream_close(
    struct output_stream *outStream
);

bool ltrx_output_stream_flush_data(
    struct output_stream *outStream
);

bool ltrx_output_stream_init_to_buffer(
    struct output_stream_to_buffer *outStream,
    void *buffer,
    size_t bufferLength,
	enum output_stream_to_buffer_mode mode
);

bool ltrx_output_stream_init_to_count(
    struct output_stream_to_count *outStream
);

bool ltrx_output_stream_init_to_file(
    struct output_stream_to_file *outStream,
    const char *fileName
);

bool ltrx_output_stream_init_to_open_tcp_socket(
    struct output_stream_from_open_tcp_socket *outStream,
    struct ltrx_ip_socket *lis
);

bool ltrx_output_stream_init_to_open_abstract_socket(
    struct output_stream_to_open_abstract_socket *outStream,
    struct ltrx_ip_socket *lis,
    const struct ltrx_network_protocol *lnp,
    struct ltrx_network_protocol_handle *lnph
);

void ltrx_output_stream_hexdump(
    struct output_stream *outStream,
    const void *data,
    size_t length,
    const void *baseOfData
);

bool ltrx_output_stream_init_to_uart(
    struct output_stream_to_uart *outStream,
    unsigned int zeroBasedIndex
);

bool ltrx_output_stream_write_binary(
    struct output_stream *outStream,
    const void *data,
    size_t length
);

bool ltrx_output_stream_write_hexadecimal(
    struct output_stream *outStream,
    uint32_t value
);

bool ltrx_output_stream_write_unsigned(
    struct output_stream *outStream,
    uint32_t value
);

bool ltrx_output_stream_from_input_stream(
    struct output_stream *outStream,
    struct input_stream *inStream
);

bool ltrx_output_stream_write_line(
    struct output_stream *outStream,
    const char *data
);

bool ltrx_output_stream_write_without_ending_line(
    struct output_stream *outStream,
    const char *data
);
