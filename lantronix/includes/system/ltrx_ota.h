
/*
 * Copyright 2017-2024, Lantronix, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Lantronix, Inc.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Lantronix, Inc.
 */

#pragma once

/*****************************************************************************/
/*                            Includes                                       */
/*****************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "ltrx_loader_network.h"


/*****************************************************************************/
/*                              Macros                                       */
/*****************************************************************************/

#define image_is_compressed(_h)  (                              \
    ntohl(((struct image_header *)_h)->ContentsMangleType) ==   \
    IMAGE_MANGLE_TYPE_LZSS                                      \
)

#if defined(stm32f2xx)
# define DEST_FLASH(_t)     ( \
    (_t) == IMAGE_TYPE_BOOTLOADER || \
    (_t) == IMAGE_TYPE_FIRMWARE || \
    (_t) == IMAGE_TYPE_PRODUCTION_CONFIG || \
    (_t) == IMAGE_TYPE_AUTOLOADER \
)

# define DEST_SPI_FLASH(_t) ( \
    (_t) == IMAGE_TYPE_OTA || \
    (_t) == IMAGE_TYPE_RADIO_FW || \
    (_t) == IMAGE_TYPE_RADIO_NVRAM \
)
#else
# define DEST_FLASH(_t)     (false)
# define DEST_SPI_FLASH(_t) (true)
#endif

#define OTA_PARAM_SIZE              4096
#define OTA_MAGIC_OLD               0xDEADFAD1
#define OTA_MAGIC                   0xDEADFAD2

#if defined(stm32f2xx)
# define OTA_PARAM_ADDRESS          0x0
# define OLD_OTA_LOADER_OFFSET      (1024 * 64 * 5)
# define OTA_LOADER_OFFSET          (1024 * 256)
#elif defined(bcm4390x)
# define OTA_PARAM_ADDRESS          0x1400A000
#endif


/*****************************************************************************/
/*                          Data Structures                                  */
/*****************************************************************************/

struct ota_eth_link
{
    uint32_t oel_speed;
    uint32_t oel_duplex;
};

union ota_network_link
{
    struct network_wifi_link nl_wifi;
    struct ota_eth_link nl_eth;
};

struct ota_interface
{
    uint8_t ota_ifindex;
    uint8_t ota_hwaddress[6];
    uint32_t ota_mss;
    struct network_ip_config ota_ip;
    //union ota_network_link ota_link;
    struct network_wifi_link ota_wifilink;
};

struct ota_log_params
{
    uint32_t line;
    uint32_t baud_rate;
    uint8_t parity;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t flow_control;
    uint8_t xon;
    uint8_t xoff;
};

struct ota_http_params
{
    uint32_t port;
};

struct ota_params
{
    uint32_t ota_magic;
    struct ota_log_params ota_log;
    struct ota_http_params ota_http;
    uint32_t ota_interface_count;
    struct ota_interface ota_network_interface[1];
};



#if 0
/* OLD STUFF in use on xpwifi 1.5 still (pre-xpwifi remote management, pre-bcm4390x ) */
struct ota_network_link
{
    char ssid[32 + 1];
    uint32_t channel;
    uint8_t suite;
    uint8_t keylen;
    uint16_t unused;
    uint32_t encryption;
    char keydata[64];
};

strut ota_network_interface
{
    struct ota_ip_address address;
    struct ota_ip_address netmask;
    struct ota_ip_address gateway;
};

struct ota_network_config_softap
{
    bool dhcp_server_enabled;
};

struct ota_network_config_wlan
{
    bool dhcp_client_enabled;
    char hostname[63 + 1];
    char dhcp_client_id[128 + 1];
    struct ota_ip_address primary_dns;
    struct ota_ip_address secondary_dns;
};

struct ota_network_params
{
    uint32_t iftype;
    uint8_t mac[6];
    uint32_t region;
    struct ota_network_link link;
    strut ota_network_interface interface;
    union
    {
        struct ota_network_config_softap softap;
        struct ota_network_config_wlan wlan;
    } config;
};

struct ota_log_params
{
    uint32_t line;
    uint32_t baud_rate;
    uint8_t parity;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t flow_control;
    uint8_t xon;
    uint8_t xoff;
};

struct ota_http_params
{
    uint32_t port;
};

struct ota_params_old
{
    uint32_t ota_magic;
    struct ota_network_params ota_network;
    struct ota_log_params ota_log;
    struct ota_http_params ota_http;
};

struct ota_remote_mgmt_params
{
    struct ota_ip_address address;
    uint16_t port;
    char url[128];
};

struct ota_params
{
    uint32_t ota_magic;
    struct ota_network_params ota_network;
    struct ota_log_params ota_log;
    struct ota_http_params ota_http;
    struct ota_remote_mgmt_params ota_rmp;
};
#endif
