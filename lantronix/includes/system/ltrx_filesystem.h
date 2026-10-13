
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
** \brief Definitions related to the file system.
*/

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

/*!
** \ingroup file_system
** \brief Bank in the file system.
*/
enum ltrx_fs_bank {
    /*! Bank A. */
    LTRX_FS_BANK__A = 1,
    /*! Bank B. */
    LTRX_FS_BANK__B = 2
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup file_system
** \brief Contains file system statistics.
*/
struct ltrx_statfs
{
    uint32_t f_bsize; /*!< Block size in bytes. */
    uint32_t f_blocks; /*!< Total number of blocks. */
    enum ltrx_fs_bank f_bank; /*!< Current active bank. */
    uint32_t f_metadata; /*!< Bytes in clean headers and directories. */
    uint32_t f_data; /*!< Bytes in clean files. */
    uint32_t f_unlinked_metadata; /*!< Bytes in dirty headers and directories. */
    uint32_t f_unlinked_data; /*!< Bytes in dirty files. */
    uint32_t f_user_files; /*!< Number of clean user files. */
    uint32_t f_system_files; /*!< Number of clean system files. */
    uint32_t f_directories; /*!< Number of clean directories. */
    bool f_compacting; /*!< \c true if currently performing a compact. */
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void ltrx_fs_compact(void);

void ltrx_fs_format(
    bool removeSystemFiles
);

void ltrx_fs_stat(
    struct ltrx_statfs *statfs
);
