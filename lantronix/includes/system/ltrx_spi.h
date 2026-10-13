
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
** \brief Definitions related to Serial Peripheral Interfaces.
*/

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup spi
** \brief Describes input and output buffers for data transfer.
**
** It it used with ltrx_spi_transfer().
*/
struct ltrx_spi_descriptor
{
    uint16_t        cmd_bytes; /*!< Length of output command. */
    uint16_t        data_bytes; /*!< Length of input and output. */
    const uint8_t  *cmd_buf; /*!< Output command. */
    const uint8_t  *mosi_buf; /*!< Output data. */
    uint8_t        *miso_buf; /*!< Input buffer. */
};

/*!
** \ingroup spi
** \brief Represents a SPI protocol for registration.
**
** This struct designates the procedures to start and stop a Serial Peripheral
** Interface protocol.
** It it used with ltrx_spi_register_protocol().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_spi_protocol
{
    /*!
    ** Name of this protocol as it will appear in configuration menu choices.
    */
    const char *protocolName;
    const char *helpHtml; /*!< HTML help for SPI Protocol selection. */
    bool (*startProtocol)(uint16_t zeroBasedIndex); /*!< Function that starts this protocol. */
    void (*stopProtocol)(uint16_t zeroBasedIndex); /*!< Function that stops this protocol. */
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_spi_close(
    uint16_t zeroBasedSPI
);

bool ltrx_spi_open(
    uint16_t zeroBasedSPI,
    uint32_t blockTimeMsec
);

void ltrx_spi_register_protocol(
    const struct ltrx_spi_protocol *lsp
);

bool ltrx_spi_transfer(
    uint16_t zeroBasedSPI,
    const struct ltrx_spi_descriptor *descriptor
);
