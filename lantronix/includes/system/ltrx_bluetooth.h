
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
#include <stdint.h>


/*****************************************************************************/
/*                             Defines                                       */
/*****************************************************************************/

#define BD_ADDRESS_SIZE                             6

#define BLE_ADVERT_DATA_MAX_LENGTH                  31

#define LTRX_BLE_ADVERT_DATA_MAX_ELEMENTS           6

#define LTRX_BLE_ADVERT_FILTER_DEVICE_MAX           7

#define LTRX_BLE_ADVERT_FILTER_SCAN_EVENT_MAX       4

/* BLE Advertisement flags found in struct ltrx_ble_advert::lba_advert_flags */
#define BLE_ADVERT_FLAG__NON_LIMITED_DISCOVERABLE   0x00
#define BLE_ADVERT_FLAG__LIMITED_DISCOVERABLE       0x01
#define BLE_ADVERT_FLAG__GENERAL_DISCOVERABLE       0x02
#define BLE_ADVERT_FLAG__BREDR_NOT_SUPPORTED        0x04
#define BLE_ADVERT_FLAG__DUAL_MODE_SAME_CONTROLLER  0x08
#define BLE_ADVERT_FLAG__DUAL_MODE_SAME_HOST        0x10

/* BLE Advertisement types. This is not an exhaustive list. */
#define BLE_ADVERT_TYPE__FLAG                       0x01
#define BLE_ADVERT_TYPE__16SRV_PARTIAL              0x02
#define BLE_ADVERT_TYPE__16SRV_COMPLETE             0x03
#define BLE_ADVERT_TYPE__32SRV_PARTIAL              0x04
#define BLE_ADVERT_TYPE__32SRV_COMPLETE             0x05
#define BLE_ADVERT_TYPE__128SRV_PARTIAL             0x06
#define BLE_ADVERT_TYPE__128SRV_COMPLETE            0x07
#define BLE_ADVERT_TYPE__NAME_SHORT                 0x08
#define BLE_ADVERT_TYPE__NAME_COMPLETE              0x09
#define BLE_ADVERT_TYPE__TX_POWER                   0x0A
#define BLE_ADVERT_TYPE__DEV_CLASS                  0x0D
#define BLE_ADVERT_TYPE__SM_TEMP_KEY                0x10
#define BLE_ADVERT_TYPE__SM_OOB_FLAG                0x11
#define BLE_ADVERT_TYPE__INTERVAL_RANGE             0x12
#define BLE_ADVERT_TYPE__SOLICITATION_SRV_UUID      0x14
#define BLE_ADVERT_TYPE__128SOLICITATION_SRV_UUID   0x15
#define BLE_ADVERT_TYPE__16SERVICE_DATA             0x16
#define BLE_ADVERT_TYPE__PUBLIC_TARGET              0x17
#define BLE_ADVERT_TYPE__RANDOM_TARGET              0x18
#define BLE_ADVERT_TYPE__APPEARANCE                 0x19
#define BLE_ADVERT_TYPE__ADVERT_INTERVAL            0x1A
#define BLE_ADVERT_TYPE__32SOLICITATION_SRV_UUID    0x1B
#define BLE_ADVERT_TYPE__32SERVICE_DATA             0x1C
#define BLE_ADVERT_TYPE__128SERVICE_DATA            0x1D
#define BLE_ADVERT_TYPE__MANUFACTURER_DATA          0xFF


/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum ltrx_bluetooth_state
{
    LTRX_BLUETOOTH_STATE__DISABLED,
    LTRX_BLUETOOTH_STATE__ENABLED,
    LTRX_BLUETOOTH_STATE__RUNNING,
};

/* Bluetooth LE Advertisements */

enum ble_scan_event_type
{
    BLE_SCAN_EVENT_TYPE__CONNECTABLE_ADVERTISEMENT,
    BLE_SCAN_EVENT_TYPE__CONNECTABLE_DIRECTED_ADVERTISEMENT,
    BLE_SCAN_EVENT_TYPE__SCANNABLE_ADVERTISEMENT,
    BLE_SCAN_EVENT_TYPE__NON_CONNECTABLE_ADVERTISEMENT,
    BLE_SCAN_EVENT_TYPE__SCAN_RESPONSE,
    BLE_SCAN_EVENT_TYPE__EXTENDED_ADVERTISEMENT,
};

enum ble_address_type
{
    BLE_ADDRESS_TYPE__PUBLIC,
    BLE_ADDRESS_TYPE__RANDOM,
    BLE_ADDRESS_TYPE__PUBLIC_ID,
    BLE_ADDRESS_TYPE__RANDOM_ID
};

enum ltrx_ble_advert_filter_type
{
    LTRX_BLE_ADVERT_FILTER_TYPE__INCLUDE,
    LTRX_BLE_ADVERT_FILTER_TYPE__EXCLUDE
};

enum bluetooth_transport
{
    BT_TRANSPORT__BREDR = 1,
    BT_TRANSPORT__LE,
};

enum bluetooth_role
{
    BT_ROLE__UNKNOWN,
    BT_ROLE__MASTER,
    BT_ROLE__SLAVE,
};

enum bluetooth_device_type
{
    BT_DEVICE_TYPE__UNKNOWN = 0,
    BT_DEVICE_TYPE__BLE,
    BT_DEVICE_TYPE__BLE_PUBLIC,
    BT_DEVICE_TYPE__BLE_RANDOM,
    BT_DEVICE_TYPE__BREDR_BLE,
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct bluetooth_device
{
    uint8_t bd_device_address[BD_ADDRESS_SIZE];
    char bd_device_name[25];
    int8_t bd_rssi;
    enum bluetooth_device_type bd_device_type;
    enum ble_address_type bd_address_type;
};


/* BLE Advertisements */

struct ltrx_ble_advert_data
{
    uint8_t lbad_type;
    uint8_t lbad_length;
    uint8_t lbad_content[BLE_ADVERT_DATA_MAX_LENGTH];
};

struct ltrx_ble_advert
{
#define lba_bda lba_device_address
    uint8_t lba_device_address[BD_ADDRESS_SIZE];
    enum ble_address_type lba_address_type;
    enum ble_scan_event_type lba_scan_event_type;
    uint8_t lba_advert_flags;
    int8_t lba_rssi;
    uint8_t lba_data_count;
    struct ltrx_ble_advert_data lba_data[
        LTRX_BLE_ADVERT_DATA_MAX_ELEMENTS
    ];
};

/* BLE Advertisement notification filters */

struct ltrx_ble_advert_device_filter
{
    enum ltrx_ble_advert_filter_type lbdf_filter_type;
    uint8_t lbdf_count;
    uint8_t lbdf_addresses[BD_ADDRESS_SIZE][
        LTRX_BLE_ADVERT_FILTER_DEVICE_MAX
    ];
};

struct ltrx_ble_advert_scan_event_filter
{
    enum ltrx_ble_advert_filter_type lbef_filter_type;
    uint8_t lbef_count;
    enum ble_scan_event_type lbef_scan_events[
        LTRX_BLE_ADVERT_FILTER_SCAN_EVENT_MAX
    ];
};

struct ltrx_ble_advert_filter
{
    struct ltrx_ble_advert_device_filter device;
    struct ltrx_ble_advert_scan_event_filter scan_event;
};


/****************************************************************************/
/*                           Function Prototypes                            */
/****************************************************************************/

bool ltrx_bluetooth_get_device_address(uint8_t bdaddr[BD_ADDRESS_SIZE]);

enum ltrx_bluetooth_state ltrx_bluetooth_get_state(void);

bool ltrx_bluetooth_is_background_scanning_enabled(void);

bool ltrx_ble_advert_notification_register(
    const struct ltrx_ble_advert_filter *filter,
    void (*advert_notification_callback)(
        const struct ltrx_ble_advert *lba,
        void *user_arg
    ),
    void *user_arg
);

void ltrx_ble_advert_notification_unregister(
    void (*advert_notification_callback)(
        const struct ltrx_ble_advert *lba, void *user_arg
    )
);

