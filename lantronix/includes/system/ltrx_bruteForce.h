/*
 * Copyright ©2025-2026, Lantronix, Inc. All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Lantronix, Inc.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Lantronix, Inc.^M
 */

#pragma once

/*****************************************************************************/
/*                             Includes                                      */
/*****************************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


/*****************************************************************************/
/*                              Macros                                       */
/*****************************************************************************/

#define MAX_ATTEMPTS 5
#define BLOCK_DURATION 300 * 1000  // 5 minutes in mseconds
#define MAX_IPS 100

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

struct IPRecord {
    char ipAddr[46];
    uint8_t authFailed_attempts;
    uint32_t blockStart_time;
    bool islogged;
    bool isBlocked;
};


struct IPRecord* 
ltrx_bruteForce_findORcreate_Entry
(
    struct IPRecord ip_records[],
    const char* ip_address
);

bool 
ltrx_bruteForce_isIPblocked
(
    struct IPRecord* record
);

void 
ltrx_bruteForce_recordFailedattempt
(
    struct IPRecord* record
);

void 
ltrx_bruteForce_deleteIPRecord
(
    struct IPRecord* record
);
