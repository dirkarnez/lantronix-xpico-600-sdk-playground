
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
/*                             Defines                                       */
/*****************************************************************************/

/* GATT attribute types */
#define GATT_UUID_PRI_SERVICE           0x2800
#define GATT_UUID_SEC_SERVICE           0x2801
#define GATT_UUID_INCLUDE_SERVICE       0x2802
#define GATT_UUID_CHAR_DECLARE          0x2803      /*  Characteristic Declaration*/

#define GATT_UUID_CHAR_EXT_PROP         0x2900      /*	Characteristic Extended Properties */
#define GATT_UUID_CHAR_DESCRIPTION      0x2901      /*  Characteristic User Description*/
#define GATT_UUID_CHAR_CLIENT_CONFIG    0x2902      /*  Client Characteristic Configuration */
#define GATT_UUID_CHAR_SRVR_CONFIG      0x2903      /*  Server Characteristic Configuration */
#define GATT_UUID_CHAR_PRESENT_FORMAT   0x2904      /*  Characteristic Presentation Format*/
#define GATT_UUID_CHAR_AGG_FORMAT       0x2905      /*  Characteristic Aggregate Format*/
#define GATT_UUID_CHAR_VALID_RANGE      0x2906      /*  Characteristic Valid Range */
#define GATT_UUID_EXT_RPT_REF_DESCR     0x2907
#define GATT_UUID_RPT_REF_DESCR         0x2908

/* GAP Profile Attributes */
#define GATT_UUID_GAP_DEVICE_NAME       0x2A00
#define GATT_UUID_GAP_ICON              0x2A01
#define GATT_UUID_GAP_PREF_CONN_PARAM   0x2A04
#define GATT_UUID_GAP_CENTRAL_ADDR_RESOL 0x2AA6

/* Attribute Profile Attribute UUID */
#define GATT_UUID_GATT_SRV_CHGD         0x2A05

/* Link Loss Service */
#define GATT_UUID_ALERT_LEVEL           0x2A06      /* Alert Level */
#define GATT_UUID_TX_POWER_LEVEL        0x2A07      /* TX power level */

/* Time Profile */
#define GATT_UUID_CURRENT_TIME          0x2A2B      /* Current Time */
#define GATT_UUID_LOCAL_TIME_INFO       0x2A0F      /* Local time info */
#define GATT_UUID_REF_TIME_INFO         0x2A14      /* reference time information */

/* NwA Profile */
#define GATT_UUID_NW_STATUS             0x2A18      /* network availability status */
#define GATT_UUID_NW_TRIGGER            0x2A1A      /* Network availability trigger */

/* phone alert */
#define GATT_UUID_ALERT_STATUS          0x2A3F      /* alert status */
#define GATT_UUID_RINGER_CP             0x2A40      /* ringer control point */
#define GATT_UUID_RINGER_SETTING        0x2A41      /* ringer setting */

/* Glucose Service */
#define GATT_UUID_GM_MEASUREMENT        0x2A18
#define GATT_UUID_GM_CONTEXT            0x2A34
#define GATT_UUID_GM_CONTROL_POINT      0x2A52
#define GATT_UUID_GM_FEATURE            0x2A51

/* device infor characteristic */
#define GATT_UUID_SYSTEM_ID             0x2A23
#define GATT_UUID_MODEL_NUMBER_STR      0x2A24
#define GATT_UUID_SERIAL_NUMBER_STR     0x2A25
#define GATT_UUID_FW_VERSION_STR        0x2A26
#define GATT_UUID_HW_VERSION_STR        0x2A27
#define GATT_UUID_SW_VERSION_STR        0x2A28
#define GATT_UUID_MANU_NAME             0x2A29
#define GATT_UUID_IEEE_DATA             0x2A2A
#define GATT_UUID_PNP_ID                0x2A50

/* HID characteristics */
#define GATT_UUID_HID_INFORMATION       0x2A4A
#define GATT_UUID_HID_REPORT_MAP        0x2A4B
#define GATT_UUID_HID_CONTROL_POINT     0x2A4C
#define GATT_UUID_HID_REPORT            0x2A4D
#define GATT_UUID_HID_PROTO_MODE        0x2A4E
#define GATT_UUID_HID_BT_KB_INPUT       0x2A22
#define GATT_UUID_HID_BT_KB_OUTPUT      0x2A32
#define GATT_UUID_HID_BT_MOUSE_INPUT    0x2A33

/* Battery Service char */
#define GATT_UUID_BATTERY_LEVEL         0x2A19

#define GATT_UUID_SC_CONTROL_POINT      0x2A55
#define GATT_UUID_SENSOR_LOCATION       0x2A5D

/* RUNNERS SPEED AND CADENCE SERVICE      */
#define GATT_UUID_RSC_MEASUREMENT       0x2A53
#define GATT_UUID_RSC_FEATURE           0x2A54

/* CYCLING SPEED AND CADENCE SERVICE      */
#define GATT_UUID_CSC_MEASUREMENT       0x2A5B
#define GATT_UUID_CSC_FEATURE           0x2A5C

/* CYCLING POWER SERVICE  (Temp for IOP)    */
#define GATT_UUID_CP_MEASUREMENT        0x2A63
#define GATT_UUID_CP_VECTOR             0x2A64
#define GATT_UUID_CP_FEATURE            0x2A65
#define GATT_UUID_CP_CONTROL_POINT      0x2A66

/* LOCATION AND NAVIGATION SERVICE  (Temp for IOP)    */
#define GATT_UUID_LN_LOC_AND_SPEED      0x2A67
#define GATT_UUID_LN_NAVIGATION         0x2A68
#define GATT_UUID_LN_POSITION_QUALITY   0x2A69
#define GATT_UUID_LN_FEATURE            0x2A6A
#define GATT_UUID_LN_CONTROL_POINT      0x2A6B

/* Magnetic Flux    */
#define GATT_UUID_MAG_FLUX_DENSITY_2D   0x2AA0
#define GATT_UUID_MAG_FLUX_DENSITY_3D   0x2AA1

/* Analog           */
#define GATT_UUID_ANALOG                0x2A58

/* Temperature & Humidity   */
#define GATT_UUID_TEMP                  0x2A6E
#define GATT_UUID_HUMIDITY              0x2A6F


/* HTTP Proxy Service       */
#define GATT_UUID_HPS_URI               0x7F11
#define GATT_UUID_HPS_HEADERS           0x7F12
#define GATT_UUID_HPS_STATUS_CODE       0x7F13
#define GATT_UUID_HPS_ENTITY_BODY       0x7F14
#define GATT_UUID_HPS_CONTROL_POINT     0x7F15
#define GATT_UUID_HPS_SERCURITY         0x7F16


/* Scan Parameter charatceristics */
#define GATT_UUID_SCAN_INT_WINDOW       0x2A4F
#define GATT_UUID_SCAN_REFRESH          0x2A31

#define GATT_APPEARANCE__GENERIC_PHONE                     64
#define GATT_APPEARANCE__GENERIC_COMPUTER                  128
#define GATT_APPEARANCE__GENERIC_WATCH                     192
#define GATT_APPEARANCE__WATCH_SPORTS                      193
#define GATT_APPEARANCE__GENERIC_CLOCK                     256
#define GATT_APPEARANCE__GENERIC_DISPLAY                   320
#define GATT_APPEARANCE__GENERIC_REMOTE_CONTROL            384
#define GATT_APPEARANCE__GENERIC_EYE_GLASSES               448
#define GATT_APPEARANCE__GENERIC_TAG                       512
#define GATT_APPEARANCE__GENERIC_KEYRING                   576
#define GATT_APPEARANCE__GENERIC_MEDIA_PLAYER              640
#define GATT_APPEARANCE__GENERIC_BARCODE_SCANNER           704
#define GATT_APPEARANCE__GENERIC_THERMOMETER               768
#define GATT_APPEARANCE__THERMOMETER_EAR                   769
#define GATT_APPEARANCE__GENERIC_HEART_RATE_SENSOR         832
#define GATT_APPEARANCE__HEART_RATE_BELT                   833
#define GATT_APPEARANCE__GENERIC_BLOOD_PRESSURE            896
#define GATT_APPEARANCE__BLOOD_PRESSURE_ARM                897
#define GATT_APPEARANCE__BLOOD_PRESSURE_WRIST              898
#define GATT_APPEARANCE__GENERIC_HID_DEVICE                960
#define GATT_APPEARANCE__HID_KEYBOARD                      961
#define GATT_APPEARANCE__HID_MOUSE                         962
#define GATT_APPEARANCE__HID_JOYSTICK                      963
#define GATT_APPEARANCE__HID_GAMEPAD                       964
#define GATT_APPEARANCE__HID_DIGITIZER_TABLET              965
#define GATT_APPEARANCE__HID_CARD_READER                   966
#define GATT_APPEARANCE__HID_DIGITAL_PEN                   967
#define GATT_APPEARANCE__HID_BARCODE_SCANNER               968
#define GATT_APPEARANCE__GENERIC_GLUCOSE_METER             1024
#define GATT_APPEARANCE__GENERIC_RUNNING_WALKING_SENSOR    1088
#define GATT_APPEARANCE__RUNNING_WALKING_SENSOR_IN_SHOE    1089
#define GATT_APPEARANCE__RUNNING_WALKING_SENSOR_ON_SHOE    1090
#define GATT_APPEARANCE__RUNNING_WALKING_SENSOR_ON_HIP     1091
#define GATT_APPEARANCE__GENERIC_CYCLING                   1152
#define GATT_APPEARANCE__CYCLING_COMPUTER                  1153
#define GATT_APPEARANCE__CYCLING_SPEED_SENSOR              1154
#define GATT_APPEARANCE__CYCLING_CADENCE_SENSOR            1155
#define GATT_APPEARANCE__CYCLING_POWER_SENSOR              1156
#define GATT_APPEARANCE__CYCLING_SPEED_AND_CADENCE_SENSOR  1157

