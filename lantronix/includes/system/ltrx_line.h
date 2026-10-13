
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
#include "main_module_definitions.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to Serial Lines.
*/

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

/*!
** \ingroup serial_line
** \brief Index out of range error code
**
** This error code indicates the number of registered line is over the max
** number of lines allowed
*/
#define LINE_REGISTRATION_FAILED 0xff

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum line_state
{
    LINE_STATE__UNINITIALIZED = 0,
    LINE_STATE__INITIALIZED,
    LINE_STATE__CONFIGURATION_BEING_APPLIED,
    LINE_STATE__CONFIGURED,
    LINE_STATE__INVALID_PORT
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup serial_line
** \brief Represents capabilities of a Serial Line.
*/
struct ltrx_line_capabilities
{
    /* 1 = capable */
    unsigned int    rs232 : 1; /*!< 1 if supports RS-232. */
    unsigned int    rs232_hw_flow : 1; /*!< 1 if supports RS-232 flow control. */
    unsigned int    rs232_modem_ctrl : 1; /*!< 1 if supports RS-232 modem control. */
#ifdef USE_RS485
    unsigned int    rs485_half_duplex : 1;
    unsigned int    rs485_full_duplex : 1;  
#ifdef USE_RS485_TERMINATION
    unsigned int    rs485_termination : 1;  
#endif
#endif
    unsigned int    custom_baud : 1; /*!< 1 if supports custom baud rates. */
    uint32_t        baud_min; /*!< Minimum supported baud rate in bits per second. */
    uint32_t        baud_max; /*!< Maximum supported baud rate in bits per second. */
    const uint32_t  *standard_baud_list; /*!< A zero-terminated array of standard baud rates supported. */
    uint16_t        rx_gap_time_ms_max; /*!< Maximum supported gap time in milliseconds. */
    uint16_t        rx_bytes_threshold_min; /*!< Minimum supported threshold in bytes. */
    uint16_t        rx_bytes_threshold_max; /*!< Maximum supported threshold in bytes. */
#ifdef USE_RS485
    uint16_t        rs485_half_tx_to_rx_delay_ms_max;
#endif
};

struct line_status_info
{
    struct statusdef_values_line_receiver svl_rx;
    struct statusdef_values_line_transmitter svl_tx;
    struct statusdef_values_line_signals svl_sig;
};

struct serial_config
{
    struct vardef_values_line__driver vvl;
    uint16_t gap_time_ms;

#if 0
    /* optional modem state change notifier and mask (see RFC2217) */
    void (*opt_notify_modem_state)(void *opaque, uint8_t modem_state);
    void *opt_notify_modem_state_opaque;
    uint8_t opt_notify_modem_state_mask;
#endif
};

/*!
** \ingroup serial_line
** \brief Represents a line protocol for registration.
**
** This struct designates the procedures to start and stop a Serial Line
** protocol.
** It it used with ltrx_line_register_protocol().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_line_protocol
{
    /*!
    ** Name of this protocol as it will appear in configuration menu choices.
    */
    const char *protocolName;
    const char *helpHtml; /*!< HTML help for Line Protocol selection. */
    bool (*startProtocol)(uint16_t zeroBasedIndex); /*!< Function that starts this protocol. */
    void (*stopProtocol)(uint16_t zeroBasedIndex); /*!< Function that stops this protocol. */
};

/*!
** \ingroup serial_line
** \brief API's for a serial line driver
*/
struct ltrx_line_driver
{
    /*!
    ** \brief Open a line for exclusive use.
    **
    ** \b Warning: Check the return value even if you specify #TIME_WAIT_FOREVER
    ** because your thread can return early if another thread calls
    ** ltrx_thread_wake().
    ** \retval true Success.
    ** \retval false Failed.
    */
    bool (*line_serial_open)(
        uint16_t zeroBasedLine,
        uint32_t blockTimeMsec
    );

    void (*line_config_warnings)(
        uint16_t zeroBasedLine,
        const struct ltrx_write_user_message_info *lwumi
    );

    struct serial_config* (*line_get_config)(uint16_t zeroBasedLine);

    bool (*line_set_config)(
        uint16_t zeroBasedLine,
        struct serial_config *config,
        const struct ltrx_write_user_message_info *lwumi
    );

    /*!
    ** \brief Get DSR status.
    **
    ** Note that on some lines, a CP may need to be configured to read DSR.
    ** \retval true The result is in \a dsr.
    ** \retval false No DSR status was available.
    */
    bool (*line_serial_get_dsr)(uint16_t zeroBasedLine, bool *dsr);

    /*!
    ** \brief Set DTR value.
    **
    ** Note that on some lines, a CP may need to be configured to write DTR.
    */
    void (*line_serial_set_dtr)(uint16_t zeroBasedLine, bool dtr);

    /*!
    ** \brief Purge data.
    **
    ** Clears any data not yet read from the Serial Line and
    ** any data previously written but not yet sent out on the Serial Line.
    */
    void (*line_serial_purge)(uint16_t zeroBasedLine);

    /*!
    ** \brief Read data.
    **
    ** The number of bytes to be read will be limited by \a max_size,
    ** but this call will generally return with fewer bytes.
    ** The number of bytes is governed by the Line configured
    ** <b>Gap Timer</b> and \b Threshold.
    **
    ** If /c 0 bytes were read, your data pointer will not have been filled in,
    ** so do not attempt to reference it.
    **
    ** You are free to read the data under the data pointer until either your next
    ** call to ltrx_line_read(), ltrx_line_read_bytes_available() or ltrx_line_close().
    ** \returns Number of bytes sitting under the data pointer.
    */
    uint16_t (*line_serial_read)(
        uint16_t zeroBasedLine,
        uint8_t **dataPointerLocation,
        size_t max_size,
        uint32_t blockTimeMsec
    );

    /*!
    ** \brief How many bytes are available?
    **
    ** If \a optReadTrigger is not \c NULL,
    ** the trigger will later be signaled when data is available.
    ** \returns Number of bytes available to read.
    */
    uint16_t (*line_serial_read_bytes_available)(
        uint16_t zeroBasedLine,
        struct ltrx_trigger *optReadTrigger
    );

    /*!
    ** \brief Write data.
    **
    ** If \a optWriteTrigger is \c NULL, this function blocks until the write is
    ** completed.
    ** Otherwise this routine returns without blocking and the trigger will later
    ** be signaled when the write has completed.
    ** \retval true Success.
    ** \retval false Failure.
    */
    bool (*line_serial_write)(
        uint16_t zeroBasedLine,
        const void *data,
        size_t size,
        struct ltrx_trigger *optWriteTrigger
    );

    bool (*line_serial_register_break_callback)(
        uint16_t zeroBasedLine,
        void (*break_callback)(void *opaque),
        void *opaque
    );

    /*!
    ** \brief Retrieve line's status information
    **
    ** Some fields in line_status_info are only applicable for physical serial line.
    */
    enum line_state (*line_get_status_info)(
        uint16_t zeroBasedLine,
        struct line_status_info *optStatus
    );

    /*!
    ** \brief Relinquish a line previously opened.
    **
    ** Previously you would have called ltrx_line_open() and saw it return \c true.
    ** This will allow other threads to open the line.
    */
    void (*line_serial_close)(uint16_t zeroBasedLine);
};

struct ltrx_virtual_line_constructor_info
{
    uint8_t zeroBasedVirtualLine;
    struct ltrx_trigger *eventTrigger;
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_line_close(
    uint16_t zeroBasedLine
);

void ltrx_line_config_request_protocol_change(
    uint16_t zeroBasedLine
);

void ltrx_line_destroy(
    uint16_t zeroBasedLine
);

const struct ltrx_line_capabilities *ltrx_line_get_capabilities(
    uint16_t zeroBasedLine
);

bool ltrx_line_get_dsr(
    uint16_t zeroBasedLine,
    bool *dsr
);

const char *ltrx_line_get_registered_name(
    uint16_t zeroBasedLine
);

uint8_t ltrx_line_get_registered_count(void);

bool ltrx_line_init(
    uint16_t zeroBasedLine,
    bool openTheBootupCli
);

bool ltrx_line_open(
    uint16_t zeroBasedLine,
    uint32_t blockTimeMsec
);

void ltrx_line_purge(
    uint16_t zeroBasedLine
);

uint16_t ltrx_line_read(
    uint16_t zeroBasedLine,
    uint8_t **dataPointerLocation,
    size_t max_size,
    uint32_t blockTimeMsec
);

uint16_t ltrx_line_read_bytes_available(
    uint16_t zeroBasedLine,
    struct ltrx_trigger *optReadTrigger
);

bool ltrx_line_register_break_callback(
    uint16_t zeroBasedLine,
    void (*break_callback)(void *opaque),
    void *opaque
);

void ltrx_line_register_protocol(
    const struct ltrx_line_protocol *llp
);

void ltrx_line_set_dtr(
    uint16_t zeroBasedLine,
    bool dtr
);

bool ltrx_line_warning_if_shutdown(
    uint16_t zeroBasedLine,
    const struct ltrx_write_user_message_info *lwumi
);

bool ltrx_line_write(
    uint16_t zeroBasedLine,
    const void *data,
    size_t size,
    struct ltrx_trigger *optWriteTrigger
);

void ltrx_line_notify_break(
    uint16_t zeroBasedLine
);

void ltrx_line_kickstart_protocol(uint16_t zeroBasedLine);

uint8_t ltrx_logical_line_driver_register(
    const struct ltrx_line_driver *driver,
    const char *name
);
