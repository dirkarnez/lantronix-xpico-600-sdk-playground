
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2015-2023, Lantronix, Inc. All Rights Reserved.
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
#include <stdint.h>


/*****************************************************************************/
/*                             Defines                                       */
/*****************************************************************************/

/* Property and permission bits, defined by the protocol. */

#define GATT_DB_PERMISSION__NONE                0x00
#define GATT_DB_PERMISSION__VARIABLE_LENGTH     0x01
#define GATT_DB_PERMISSION__READABLE            0x02
#define GATT_DB_PERMISSION__WRITE_CMD           0x04
#define GATT_DB_PERMISSION__WRITE_REQ           0x08
#define GATT_DB_PERMISSION__AUTH_READABLE       0x10
#define GATT_DB_PERMISSION__RELIABLE_WRITE      0x20
#define GATT_DB_PERMISSION__AUTH_WRITABLE       0x40
#define GATT_DB_PERMISSION__SERVICE_UUID_128    0x80

#define GATT_DB_PROPERTY__BROADCAST             0x01
#define GATT_DB_PROPERTY__READ                  0x02
#define GATT_DB_PROPERTY__WRITE_NO_RESPONSE     0x04
#define GATT_DB_PROPERTY__WRITE                 0x08
#define GATT_DB_PROPERTY__NOTIFY                0x10
#define GATT_DB_PROPERTY__INDICATE              0x20
#define GATT_DB_PROPERTY__AUTHD_WRITES          0x40
#define GATT_DB_PROPERTY__EXTENDED              0x80

#define LTRX_GATT_CLIENT_CONFIG__NONE           0x0000
#define LTRX_GATT_CLIENT_CONFIG__NOTIFICATION   0x0001
#define LTRX_GATT_CLIENT_CONFIG__INDICATION     0x0002

#define UUID_LENGTH_128                             16

#define UUID_LENGTH_32                              4

#define UUID_LENGTH_16                              2

#define GATT_MTU_SIZE_DEFAULT                       23


/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum ltrx_gatt_status
{
    LTRX_GATT_STATUS__SUCCESS,
    LTRX_GATT_STATUS__INVALID_HANDLE,
    LTRX_GATT_STATUS__READ_NOT_PERMITTED,
    LTRX_GATT_STATUS__WRITE_NOT_PERMITTED,
    LTRX_GATT_STATUS__INVALID_PDU,
    LTRX_GATT_STATUS__REQUEST_NOT_SUPPORTED = 0x06,
    LTRX_GATT_STATUS__INVALID_OFFSET,
    LTRX_GATT_STATUS__PREPARE_QUE_FULL = 0x09,
    LTRX_GATT_STATUS__NOT_FOUND,
    LTRX_GATT_STATUS__INSUFFICIENT_RESOURCES = 0x11,
    LTRX_GATT_STATUS__INVALID_ATTRIBUTE_LENGTH = 0x0D,
    LTRX_GATT_STATUS__NO_RESOURCES = 0x80,
    LTRX_GATT_STATUS__INTERNAL_ERROR,
    LTRX_GATT_STATUS__WRONG_STATE,
    LTRX_GATT_STATUS__DB_FULL,
    LTRX_GATT_STATUS__BUSY,
    LTRX_GATT_STATUS__ERROR,
    LTRX_GATT_STATUS__CMD_STARTED,
    LTRX_GATT_STATUS__ILLEGAL_PARAMETER,
    LTRX_GATT_STATUS__PENDING,
};

enum ltrx_gatt_write_type
{
    LTRX_GATT_WRITE__NORMAL,
    LTRX_GATT_WRITE__NO_RESPONSE,
    LTRX_GATT_WRITE__PREPARE,
};


/*****************************************************************************/
/*                             Structures                                    */
/*****************************************************************************/

struct ltrx_uuid
{
    uint8_t length;
    union
    {
        uint16_t id16;
        uint32_t id32;
        uint8_t id128[16];
    } uu;
};

struct ltrx_gatt_handle_range
{
    uint16_t h_start;
    uint16_t h_end;
};

struct ltrx_gatt_disc_descriptor
{
    struct ltrx_uuid uuid;
    uint16_t handle;
};

struct ltrx_gatt_disc_characteristic
{
    struct ltrx_uuid uuid;
    uint16_t handle;
    uint16_t value_handle;
    uint8_t properties;
};

struct ltrx_gatt_disc_service
{
    struct ltrx_uuid uuid;
    struct ltrx_gatt_handle_range handle_range;
};

struct ltrx_gatt_read_by_type_result
{
    uint16_t handle;
    uint16_t length;
    uint8_t data[];
};
