
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
** \brief Definitions for Configurable Pins.
*/

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

/*!
** \ingroup cpm
** Defines possible usage for a Configurable Pin role.
*/
enum ltrx_cpm_role_usage
{
    LTRX_CPM_ROLE_USAGE__RESERVED = 0, /*!< Reserved. */
    LTRX_CPM_ROLE_USAGE__INPUT = 1, /*!< Input. */
    LTRX_CPM_ROLE_USAGE__OUTPUT = 2, /*!< Output. */
};

/*!
** \ingroup cpm
** Defines possible requirement for assert high or low.
*/
enum ltrx_cpm_required_assert
{
    LTRX_CPM_REQUIRED_ASSERT__NONE = 0, /*!< Not applicable. */
    LTRX_CPM_REQUIRED_ASSERT__HIGH = 1, /*!< High. */
    LTRX_CPM_REQUIRED_ASSERT__LOW = 2, /*!< Low. */
};

/*!
** \ingroup cpm
** Defines possible requirement for mode.
*/
enum ltrx_cpm_required_mode
{
    LTRX_CPM_REQUIRED_MODE__NONE = 0, /*!< Not applicable. */
    LTRX_CPM_REQUIRED_MODE__PUSH_PULL = 1, /*!< Push-Pull. */
    LTRX_CPM_REQUIRED_MODE__WEAK_PULLUP = 2, /*!< Weak Pullup. */
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup cpm
** \brief Represents a Configurable Pin role for registration.
**
** This struct designates the procedure and options to define a role.
** It it used with ltrx_cp_register_role().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_cpm_role
{
    /*!
    ** Name of this role as it will appear in configuration menu choices.
    */
    const char *name;
    const char *helpHtml; /*!< HTML help for this role. */
    /*! Usage of the Configurable Pin in this role. */
    enum ltrx_cpm_role_usage usage;
    /*!
    ** If zero, it means that the user may select any Configurable Pin for this
    ** role.
    ** Otherwise it represents a Configurable Pin number that is a
    ** \b required assignment for this role.
    */
    uint8_t optOneBasedCp;
    /*!
    ** If present, can constrain assert setting High or Low.
    */
    enum ltrx_cpm_required_assert optRequiredAssert;
    /*!
    ** If present, can constrain mode setting Push-Pull or Weak Pullup.
    */
    enum ltrx_cpm_required_mode optRequiredMode;
    /*!
    ** If present, this function will be called when an input is toggled.
    ** Otherwise, set to \c NULL.
    */
    void (*optToggleCall)(const char *roleName);
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_cp_read(
    uint16_t roleIndex,
    bool *isAsserted
);

void ltrx_cp_register_role(
    const struct ltrx_cpm_role *role
);

uint16_t ltrx_cp_role_index_get(
    const char *roleName
);

bool ltrx_cp_write(
    uint16_t roleIndex,
    bool setting
);
