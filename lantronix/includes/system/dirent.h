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

#include <stdint.h>

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/* Lantronix minimal posix dirent interface. */

/*!
** \file
** \brief Definitions for file directory entries.
*/

/*****************************************************************************/
/*                             Defines                                       */
/*****************************************************************************/

/* Directory entry types: */

/*!
** \ingroup file_system
** \brief Directory entry type directory.
*/
#define DT_DIR          4

/*!
** \ingroup file_system
** \brief Directory entry type regular file.
*/
#define DT_REG          8

/*!
** \ingroup file_system
** \brief Directory entry type character device. 
*/
#define DT_CHR          2 

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup file_system
** \brief Directory entry struct written by readdir().
*/
struct dirent
{
    /*! Size of the entry in bytes. */
    uint32_t d_size;
    /*! Type of the entry. (\c DT_REG, \c DT_DIR, or \c DT_CHR). */
    uint32_t d_type;
    /*! Name of the entry. */
    char d_name[101];
}; 

/*****************************************************************************/
/*                             Typedefs                                      */
/*****************************************************************************/

/*!
** \ingroup file_system
** \brief Directory stream type.
**
** Typedef \c DIR is a stream opened by opendir(), read by readdir(),
** and closed by closedir().
*/
typedef void DIR;

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

DIR *opendir(const char *path);

int readdir(DIR *dir, struct dirent *dent);

int closedir(DIR *dir);

int dirfd(DIR *dir);
