
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2020-2024, Lantronix, Inc. All Rights Reserved.
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
/*                             Structs                                       */
/*****************************************************************************/
#define MCUBOOT_HEADER_SKIP	0x400
#define PARTITION_SECONDARY	0x08820000

#define BDR_ADDR        0x0803F000   /* dedicated 4KB sector */
#define BDR_SECTOR_SZ   0x1000
#define BDR_MAGIC       0x42445231   /* "BDR1" */

#define PART_PRIMARY    1
#define PART_SECONDARY  2
extern uint32_t s_install_address;

struct boot_decision_record {
    uint32_t magic;         /* written LAST */
    uint32_t active_part;   /* 1 = primary, 2 = secondary */
    uint32_t version;       /* monotonically increasing */
    uint32_t crc;           /* CRC of fields except magic */
};

struct ltrx_firmware_upgrade_context;

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

struct ltrx_firmware_upgrade_context *ltrx_firmware_upgrade_begin(
    const char *optRequiredVersion
);

bool ltrx_firmware_upgrade_data(
    struct ltrx_firmware_upgrade_context *f,
    const void *data,
    size_t length
);

bool ltrx_firmware_upgrade_end(
    struct ltrx_firmware_upgrade_context *f,
    bool goodFinish,
    bool *reboot,
    bool *validPartition
);

const char * ltrx_fw_update_failed_reason_get(void);
void ltrx_fw_update_failed_reason_clear(void);
bool ltrx_write_bdr(
	uint32_t target_part,
	uint32_t version
);

uint8_t ltrx_read_bdr_active_partition(void);
