
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

#include <stddef.h>

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions for the Trouble Log.
*/

/*!
** \ingroup tlog
** @{
*/

/*****************************************************************************/
/*                               Macros                                      */
/*****************************************************************************/

/*!
** \brief Post a log entry.
** \param [in] severity Serverity of type enum tlog_severity_level.
** \param [in] formatText Text for log entry, use snprintf format.
** \param [in] argumentList Optional arguments with types matching those defined in
** \a formatText.
*/
#define TLOG(severity, formatText, argumentList...) \
    ltrx_tlog_do_not_call_directly( \
        __FILE__, __LINE__, TLOG_FACILITY__USER, \
        severity, formatText, ##argumentList \
    )

/*!
** \brief Dump data in hex form to TLOG as one or more log entries.
** \param [in] severity Serverity of type enum tlog_severity_level.
** \param [in] data Starting address of data to be logged.
** \param [in] length Length in bytes of data to be logged.
** \param [in] baseOfData Base address of data, used for display of data offset.
*/
#define TLOG_HEXDUMP(severity, data, length, baseOfData) \
    ltrx_tlog_hex_dump_do_not_call_directly( \
        __FILE__, __LINE__, TLOG_FACILITY__USER, \
        severity, (const void *)(data), length, (const void *)(baseOfData) \
    )

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum tlog_facility
{
    TLOG_FACILITY__KERNEL = 0,
    TLOG_FACILITY__USER = 1,
    TLOG_FACILITY__MAIL = 2,
    TLOG_FACILITY__DAEMON = 3,
    TLOG_FACILITY__AUTH = 4,
    TLOG_FACILITY__SYSLOG = 5,
    TLOG_FACILITY__LPR = 6,
    TLOG_FACILITY__NEWS = 7,
    TLOG_FACILITY__UUCP = 8,
    TLOG_FACILITY__CRON = 9,
    TLOG_FACILITY__AUTHPRIV = 10,
    TLOG_FACILITY__FTP = 11,
    TLOG_FACILITY__NTP = 12,
    TLOG_FACILITY__LOG_AUDIT = 13,
    TLOG_FACILITY__LOG_ALERT = 14,
    TLOG_FACILITY__CRON2 = 15,
    TLOG_FACILITY__LOCAL0 = 16,
    TLOG_FACILITY__LOCAL1 = 17,
    TLOG_FACILITY__LOCAL2 = 18,
    TLOG_FACILITY__LOCAL3 = 19,
    TLOG_FACILITY__LOCAL4 = 20,
    TLOG_FACILITY__LOCAL5 = 21,
    TLOG_FACILITY__LOCAL6 = 22,
    TLOG_FACILITY__LOCAL7 = 23,
};

/*!
** \brief Severity levels.
**
** The severity levels are defined in accordance with RFC 3164.
*/
enum tlog_severity_level
{
    TLOG_SEVERITY_LEVEL__EMERGENCY = 0, /*!< Emergency. */
    TLOG_SEVERITY_LEVEL__ALERT, /*!< Alert. */
    TLOG_SEVERITY_LEVEL__CRITICAL, /*!< Critical. */
    TLOG_SEVERITY_LEVEL__ERROR, /*!< Error. */
    TLOG_SEVERITY_LEVEL__WARNING, /*!< Warning. */
    TLOG_SEVERITY_LEVEL__NOTICE,  /*!< Notice. */
    TLOG_SEVERITY_LEVEL__INFORMATIONAL, /*!< Informational. */
    TLOG_SEVERITY_LEVEL__DEBUG /*!< Debug. */
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_tlog_do_not_call_directly(
    const char *sourceFile,
    int sourceLine,
    enum tlog_facility facility,
    enum tlog_severity_level severity,
    const char *format,
    ...
);

void ltrx_tlog_hex_dump_do_not_call_directly(
    const char *sourceFile,
    int sourceLine,
    enum tlog_facility facility,
    enum tlog_severity_level severity,
    const void *data,
    size_t length,
    const void *baseOfData
);

/*!
** @}
*/
