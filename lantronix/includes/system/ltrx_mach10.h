
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

#include "main_module_definitions.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

enum ltrx_mach10_api_return_code 
{
    LTRX_MACH10_API_RC__SUCCESS           =  0,
    LTRX_MACH10_API_RC__NOT_ENABLED       =  -1,
    LTRX_MACH10_API_RC__CALLER_EXIT       =  -2,
    LTRX_MACH10_API_RC__INVALID_PARAMETER =  -3,
    LTRX_MACH10_API_RC__NOT_ENOUGH_MEMORY =  -4,
    LTRX_MACH10_API_RC__UNKNOWN_COMMAND   =  -5,
    LTRX_MACH10_API_RC__TRANSPORT_ERROR   =  -6,
};

