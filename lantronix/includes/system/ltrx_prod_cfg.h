#ifndef PROD_H
#define PROD_H

#include <stdint.h>
#include <stdbool.h>
#include "ltrx_flash.h"
#include "ltrx_tlog.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Production config magic */
#define PROD_MAGIC                  0x58412d534144494dULL   /* "MIDAS-AX" */
#define PROD_VERSION                0x00000001U

/* Configuration variable IDs */
#define PROD_CFG_REGION             35          /* Region code (1 byte) */
#define PROD_CFG_HWADDR0            36          /* STA MAC address (6 bytes) */
#define PROD_CFG_HWADDR1            37          /* uAP MAC address (6 bytes) */
#define PROD_CFG_HWADDR2            38          /* BLE MAC address (6 bytes) */
#define PROD_CFG_HWADDR3            39          /* ETH MAC address (6 bytes) */
#define PROD_CFG_SKU                194         /* SKU string */
#define PROD_CFG_PID                251         /* Product ID */
#define PROD_CFG_DEVKEY             252         /* Device key (32 bytes) */
#define PROD_CFG_DEVID              254         /* Device ID (32 bytes) */

/* Flash layout */
#define PROD_FLASH_OFFSET           0x801C000     /* 112KB offset */
#define PROD_FLASH_SIZE             0x2000      /* 8KB (2 sectors) */

/* Fixed values */
#define PROD_FIXED_REGION           0           /* Region code: 0 = US */
#define PROD_FIXED_SKU              "XPC600"    /* Product model, fixed to XPC600 */
#define PROD_FIXED_PID              "Z7"        /* Product ID, fixed to Z7 */

/* Production configuration header */
typedef struct
{
    uint64_t magic;              /* Magic: "MIDAS-AX" */
    uint32_t version;            /* Version */
    uint32_t total_length;       /* Total TLV length */
    uint32_t checksum;           /* CRC32 checksum */
    uint8_t  reserved[12];       /* Reserved */
} __attribute__((packed)) prod_header_t;

/* Complete configuration structure */
typedef struct
{
    prod_header_t header;

    struct
    {
        uint8_t type;
        uint8_t length;
        uint8_t region;
    } __attribute__((packed)) region;
    struct
    {
        uint8_t type;
        uint8_t length;
        uint8_t mac[6];
    } __attribute__((packed)) hwaddr0;  /* STA MAC */
    struct
    {
        uint8_t type;
        uint8_t length;
        uint8_t mac[6];
    } __attribute__((packed)) hwaddr1;  /* uAP MAC */
    struct
    {
        uint8_t type;
        uint8_t length;
        uint8_t mac[6];
    } __attribute__((packed)) hwaddr2;  /* BLE MAC */
    struct
    {
        uint8_t type;
        uint8_t length;
        uint8_t mac[6];
    } __attribute__((packed)) hwaddr3;  /* ETH MAC */
    struct
    {
        uint8_t type;
        uint8_t length;
        char sku[32];
    } __attribute__((packed)) sku;
    struct
    {
        uint8_t type;
        uint8_t length;
        char pid[32];
    } __attribute__((packed)) pid;
    struct
    {
        uint8_t type;
        uint8_t length;
        char devkey[32];
    } __attribute__((packed)) devkey;
    struct
    {
        uint8_t type;
        uint8_t length;
        char devid[32];
    } __attribute__((packed)) devid;

} __attribute__((packed)) prod_config_t;


/**
 * @brief Initialize configuration buffer
 */
void prod_init_buffer(prod_config_t *config);

/**
 * @brief Write configuration to flash
 */
//uint8_t prod_write(const prod_config_t *config);

/**
 * @brief Read configuration from flash
 */
bool prod_read(prod_config_t *config);

/**
 * @brief Erase configuration area
 */
//uint8_t prod_erase(void);

/**
 * @brief Verify configuration in flash
 */
//uint8_t prod_verify(void);

/**
 * @brief Calculate CRC32 checksum
 */
uint32_t prod_crc32(const uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* PROD_H */
