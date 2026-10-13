
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2016-2024, Lantronix, Inc. All Rights Reserved.
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

#include "ltrx_cfgvar.h"

/*****************************************************************************/
/*                              Externs                                      */
/*****************************************************************************/

extern uint8_t ltrx_linker_device_ram_start[];
extern uint8_t ltrx_linker_device_ram_end[];

extern uint8_t ltrx_linker_device_psram_start[];
extern uint8_t ltrx_linker_device_psram_end[];
extern uint8_t ltrx_linker_stack_ram_start[];
extern uint8_t ltrx_linker_stack_ram_end[];

extern void *ltrx_linker_code_size;

extern void *ltrx_linker_data_size;
extern void *ltrx_linker_data_ram_start;

extern void *ltrx_linker_bss_ram_start;
extern void *ltrx_linker_bss_size;

extern const struct ltrx_module_info ltrx_linker_module_main_flash_end;

extern uint8_t ltrx_linker_module_main_ram_end[];


/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

const struct image_header *ltrx_device_get_firmware_image_header(void);
