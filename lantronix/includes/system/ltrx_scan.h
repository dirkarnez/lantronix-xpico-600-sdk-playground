
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
#include <stdint.h>

/*****************************************************************************/
/*                             Defines                                       */
/*****************************************************************************/

/*!
** \ingroup network_scan
** \brief Open security protocol
**
** Open security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__OPEN  0x00

/*!
** \ingroup network_scan
** \brief WEP security protocol
**
** WEP security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__WEP   0x01

/*!
** \ingroup network_scan
** \brief WPA security protocol
**
** WPA security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__WPA   0x02

/*!
** \ingroup network_scan
** \brief WPA2 security protocol
**
** WPA2 security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__WPA2  0x04

/*!
** \ingroup network_scan
** \brief WPA/WPA2 Mixed security protocol
**
** WPA/WPA2 Mixed security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__WPA_MIXED  0x08

/*!
** \ingroup network_scan
** \brief WPA3 security protocol
**
** WPA3 security protocol
*/
#define LTRX_SCAN_SECURITY_SUITE__WPA3  0x10


/*!
** \ingroup network_scan
** \brief WEP security level
**
** WEP security level
*/
#define LTRX_SCAN_ENCR_FLAGS__WEP       0x01

/*!
** \ingroup network_scan
** \brief CCMP encryption protocol
**
** CCMP encryption protocol
*/
#define LTRX_SCAN_ENCR_FLAGS__CCMP      0x02

/*!
** \ingroup network_scan
** \brief TKIP encryption protocol
**
** TKIP encryption protocol
*/
#define LTRX_SCAN_ENCR_FLAGS__TKIP      0x04

/*!
** \ingroup network_scan
** \brief GCMP encryption protocol
**
** GCMP encryption protocol
*/
#define LTRX_SCAN_ENCR_FLAGS__GCMP      0x08

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

/*!
** \ingroup wifi_network_information
** \brief Contains network information acquired from network scan.
*/
struct ltrx_scan_result
{
    unsigned char 	ssid[LANTRONIX_WLAN_SSID_LENGTH + 1];  /*!<  Network SSID */
    unsigned char 	bssid[LANTRONIX_WLAN_MAC_ADDRESS_LENGTH];  /*!<  Network BSSID */
    unsigned char   channel;  /*!<  Network channel */
    int             rssi;  /*!<  Network rssi */
    unsigned char   security_suite;  /*!<  Network security suite */
    unsigned char   encr_flags;  /*!<  Network encryption flags */
#ifdef USE_ENTERPRISE_AUTH
    bool            use_enterprise_auth;
#endif /* USE_ENTERPRISE_AUTH */
// #ifdef USE_MIXED_MODE
    unsigned int    ap_indicated_security;
// #endif
    bool            wpa3_ent;
    bool            suiteB;
    bool            suiteB_192;
#ifdef USE_IEEE80211R
    bool            supports_80211r;
#endif
};

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_scan_begin(uint32_t scanMutexWaitMsec);

bool ltrx_scan_collect(const char *optSsid);

struct ltrx_scan_result *ltrx_scan_get(unsigned int readoutIndex);

void ltrx_scan_end(void);
