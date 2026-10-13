
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
** \brief Definitions for date and time.
*/

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

/*!
** \ingroup date_and_time
** The Lantronix epoch is year 2000; this is the base value for the
** elapsed seconds to the current time for functions ltrx_time_get(),
** ltrx_time_set(), ltrx_time_to_utc() and ltrx_time_from_utc().
*/
#define LTRX_EPOCH_YEAR     2000

/*
** Macros useful for converting between various epochs 
** LTRX epoch: 2000
** UNIX epoch: 1970
** NTP, gmtime(), etc. epoch: 1900
*/
#define YEAR1900_UNIX_EPOCH_SECONDS 2208988800
#define YEAR1900_LTRX_EPOCH_SECONDS 3155673600
#define YEAR1970_LTRX_EPOCH_SECONDS ( \
    YEAR1900_LTRX_EPOCH_SECONDS - YEAR1900_UNIX_EPOCH_SECONDS \
)

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup date_and_time
** \brief Represents "broken-down" time
**
** ltrx_time_to_utc(), ltrx_time_to_local(), and ltrx_time_from_utc() work similar to
** the POSIX libc functions gmtime(), localtime() and mktime(). The 
** values in struct ltrx_time can be overloaded and conversion calculations
** will be correct.
*/
struct ltrx_time
{
    int16_t t_year; /*!< Full year, for example, 2014 */
    int16_t t_month; /*!< January is 1, February is 2, and so on. */
    int16_t t_dayofmonth; /*!< 1 to 31. */
    int16_t t_hour; /*!< 0 to 23. */
    int16_t t_minute; /*!< 0 to 59. */
    int16_t t_second; /*!< 0 to 59. */
};

/*!
** \ingroup date_and_time
** \brief Represents a time source for registration.
**
** This struct designates the procedures to start and stop a time source
** service. It it used with ltrx_time_register_source().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_time_source
{
    /*!
    ** Name of this source as it will appear in configuration menu choices.
    */
    const char *ts_name;
    void (*ts_start)(void); /*!< Function that starts up this time source. */
    void (*ts_stop)(void); /*!< Function that stops this time source. */
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

uint32_t ltrx_time_from_utc(
    struct ltrx_time *lt
);

uint32_t ltrx_time_get(void);

void ltrx_time_register_source(
    const struct ltrx_time_source *lts
);

void ltrx_time_set(
    uint32_t seconds_since_2000
);

void ltrx_time_to_local(
    uint32_t seconds_since_2000,
    struct ltrx_time *lt
);

void ltrx_time_to_utc(
    uint32_t seconds_since_2000,
    struct ltrx_time *lt
);
