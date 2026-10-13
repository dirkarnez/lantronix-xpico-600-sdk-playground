
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2019-2024, Lantronix, Inc. All Rights Reserved.
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

/****************************************************************************/
/*                                 Includes                                 */
/****************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/****************************************************************************/
/*                                 Defines                                  */
/****************************************************************************/

#define UUID_LENGTH 16

#define UUID_STRING_LENGTH 36 /* without terminator */

/****************************************************************************/
/*                             Data Structures                              */
/****************************************************************************/

typedef uint8_t uuid_t[16] __attribute__ ((aligned (4)));

/****************************************************************************/
/*                           Function Prototypes                            */
/****************************************************************************/

bool uuid_parse(const char *s, uuid_t uuid);

bool uuid_unparse(const uuid_t uuid, char *s);

bool uuid_is_null(const uuid_t uuid);

bool uuid_compare(const uuid_t uuid1, const uuid_t uuid2);
