
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2008-2024, Lantronix, Inc. All Rights Reserved.
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

#include "ltrx_definitions.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
**
** \addtogroup snmp
**
** \brief SNMP Agent MIB registration.
**
**  This module is used to register MIB handlers for custom
**  MIB implementations.
**
** @{
*/


/*!
** \name Maximums
** This define specifies the maximum number of keys.  For example,
** the standard MIB-II includes the tcpConnTable which has four values
** in its INDEX clause.  When encoded in the identifier, two of those
** index values may be 8 bytes each and the other two may be 3 bytes
** each for a total of 22 bytes.  These values cannot be changed by
** the SDK.
** @{
*/
#define MAXKEY 4
#define MAXKLEN 22
/*!
** This define specifies the maximum length of an OID in encoded
** format.  This value cannot be changed by the SDK.
*/
#define MAXOID 32
/* @} */

/*!
** \name MIB variable characteristics.
** These defines are options used to define the charactistics for a MIB variable.
** @{
*/
#define MIBOPT_IMMED   0x01 /*!< immediate value located in (MIBVAR->len) */
#define MIBOPT_IMMED2  0x02 /*!< immediate value (MIBVAR->type + MIBVAR->len) */
#define MIBOPT_BASE1   0x03 /*!< base 0 in data space, base 1 in MIB */
#define MIBOPT_SCALAR  0x04 /*!< table not indexed directly (no offset) */
#define MIBOPT_W       0x08 /*!< writes are allowed */
#define MIBOPT_SX      0x10 /*!< sequential table index inferred */
#define MIBOPT_NWORDER 0x20 /*!< network byte ordering for basic type */
#define MIBOPT_CAR     0x40 /*!< call application cbk for read */
#define MIBOPT_CAW     0x80 /*!< call application cbk for write */
/* @} */

/*!
** \name MIB variable types.
** These defines are the MIB variable types.
** @{
*/
#define SNMP_Integer     0x02
#define SNMP_String      0x04
#define SNMP_Null        0x05
#define SNMP_Identifier  0x06
#define SNMP_OctetString 0x14 /*!< Uses length, not zero termination. Externally seen as 0x04. */
#define SNMP_Sequence    0x30
#define SNMP_IpAddress   0x40
#define SNMP_Counter     0x41
#define SNMP_Counter32   0x41
#define SNMP_Gauge       0x42
#define SNMP_Ticks       0x43
#define SNMP_Uinteger32  0x47
/* @} */

/*!
** \name Return Values.
** These defines are the return values that can be returned by the
** various MIB handler callback functions.
** @{
*/
#define SNMP_RV_ok                  0
#define SNMP_RV_tooBig              1
#define SNMP_RV_noSuchName          2
#define SNMP_RV_badValue            3
#define SNMP_RV_readOnly            4
#define SNMP_RV_genErr              5
#define SNMP_RV_noAccess            6
#define SNMP_RV_wrongType           7
#define SNMP_RV_wrongLength         8
#define SNMP_RV_wrongEncoding       9
#define SNMP_RV_wrongValue          10
#define SNMP_RV_noCreation          11
#define SNMP_RV_inconsistentValue   12
#define SNMP_RV_resourceUnavailable 13
#define SNMP_RV_commitFailed        14
#define SNMP_RV_undoFailed          15
#define SNMP_RV_authorizationError  16
#define SNMP_RV_notWritable         17
#define SNMP_RV_inconsistentName    18
/* @} */

struct sockaddr;
struct timeval;

/*!
** This enum defines the SNMP Operation of the request.
*/
typedef enum
{
    SnmpGet  = 1,
    SnmpNext = 2,
    SnmpSet  = 3 
} SnmpOperationType;


/*!
** This struct is used to define an ASN.1 OID.
*/
typedef struct 
{
    uint8_t nlen;          /*!< number of elements in the OID */
    uint8_t name[MAXOID];  /*!< encoded OID elements */
} OID;


/*!
** This struct is used to define a MIB variable.  Every MIB variable, whether
** it's in a table or not, must be defined by a MIBVAR struct.  For example
** the sysContact variable can be defined as:
**
** \code
**  char sysContact[255];
**  sysContactMibVar = {{8,{0x2b,6,1,2,1,1,4,0}}, MIBOPT_W + MIBOPT_CAW,
**                      SNMP_String, sizeof(sysContact), sysContact}
** \endcode
*/
typedef struct  
{
    OID oid;        /*!< OID for the variable */
    uint8_t opt;    /*!< options (see defines above) */
    uint8_t type;   /*!< variable SNMP SMI type (see defines above) */
    int16_t len;    /*!< length/size of the data pointed to by 'ptr' */
    void *ptr;      /*!< pointer to the (possible) variable data */
} MIBVAR;

/*!
** This struct is used to define a MIB Table.  For example the MIB-II UDP
** group and Listener table can be defined as:
**
** \code
**  static const MIBVAR mibvar_udp[] =
**  {
**      {{8,{0x2b,6,1,2,1,7,1,0}}, 0, SNMP_Counter,
**                        sizeof(long), &g_UdpGroup.udpInDatagrams},
**      {{8,{0x2b,6,1,2,1,7,2,0}}, 0, SNMP_Counter,
**                        sizeof(long), &g_UdpGroup.udpNoPorts},
**      {{8,{0x2b,6,1,2,1,7,3,0}}, 0, SNMP_Counter,
**                        sizeof(long), &g_UdpGroup.udpInErrors},
**      {{8,{0x2b,6,1,2,1,7,4,0}}, 0, SNMP_Counter,
**                        sizeof(long), &g_UdpGroup.udpOutDatagrams},
**      {{9,{0x2b,6,1,2,1,7,5,1,1}}, MIBOPT_CAR + MIBOPT_SCALAR,
**                        SNMP_IpAddress, IID_SIZE, &dummy_uint32},
**      {{9,{0x2b,6,1,2,1,7,5,1,2}}, MIBOPT_CAR + MIBOPT_NWORDER, SNMP_Integer,
**                        sizeof(g_Connections[0].myport), &g_Connections[0].myport},
**  };
**
**  static int mibvarsize_udp(void)
**  {
**      return ARRAY_SIZE(mibvar_udp);
**  }
**
**  #define XudpLocalAddress 4
**  #define XudpLocalPort 5
**
**  static const MIBTAB mibtab_udp[] =
**  {
**      {{7,{0x2b,6,1,2,1,7,5}}, 2,
**       {XudpLocalAddress,XudpLocalPort,0,0}, sizeof(struct connection)}
**  };
** \endcode
**
**   The UDP Listener table uses two indexes.  One is the Local IP Address
**   the the other is the Port number.  The XudpLocalAddress and
**   XudpLocalPort defines are used as index pointers intto the actual
**   MIBVAR definition within the mibvar_udp table where the table indexes
**   can be found.
*/
typedef struct
{
    OID oid;                /*!< base OID for the table */
    uint8_t nix;            /*!< number of indices for the table */
    uint16_t ix[MAXKEY];    /*!< Index values (offsets) */
    uint16_t len;           /*!< length of the table where the data lives */
} MIBTAB;


/*!
** This struct is used to define SNMP access to a particular MIB.
**
**   The get(), set(), init(), and check() callback functions can be defined
**   as NULL.  The index() function must be defined if the MIB contains a
**   table.  Additionally the get() and/or set() should be defined if a MIB
**   variable is defined using MIBOPT_CAR and/or MIB_OPT_CAW.
**
**   When a MIB variable is defined with MIBOPT_CAR the get() function
**   is called when an SNMP GET operation is performed on the variable.
**
**   void (*get)(int varix, int tabix, uint8_t ** vvptr);
**     \param varix  (in) current 'MIBVAR' index
**     \param tabix  (in) current data storage table/struct index
**     \param vvptr  (out) store value here
**     \retval void
**
**   When a MIB variable is defined with MIBOPT_CAW the set() function
**   is called when an SNMP Set operation is performed on the variable.
**   The data value to be set is first written to the area specified by
**   'ptr' in the variable MIBVAR definition.  The set() function is
**   used to performed post processing on the data value (i.e. copy the
**   data elsewhere and/or trigger some event).  If your MIB Handler contains
**   a table and you use the index() function then you should use set().
**   Likewise if you use the index2() function then you should use set2().
**   The table index/data passed to the set2() function is that returned by a
**   previous call to your index2() function.
**
**   int (*set)(int varix, int tabix);
**     \param varix  (in) current 'MIBVAR' index
**     \param tabix  (in) current data storage table/struct index
**     \retval int   an SNMP_RV code
**
**   int (*set2)(int varix,
**               const uint8_t * pIndex, uint32_t indexLen,
**               void * pData);
**     \param varix    (in) current 'MIBVAR' index
**     \param pIndex   (in) encoded OID Table index
**     \param indexLen (in) length of the encoded OID Table index
**     \param pData    (in) data being set (encoded)
**     \retval int     an SNMP_RV code
**
**   If the MIB contains a table then an index() function must be implemented.
**
**   The basic index() function is used by the agent to determine what table
**   indexes (tabix) are valid.  Using this routine is very inefficient.  The
**   agent will call your index() routine for every entry in your table until
**   you return -1.  After every call to your index() function, assuming the
**   function returns 1, the agent will then call your get() routine to get
**   the actual table index for that tabix.  It will then do some
**   lexicographic OID compares and keep track of the best match (for SNMP
**   GetNext operations).  If your table data is unorganized by SNMP standards
**   then implementing this function makes things easy at a cost of bad
**   performance.
**
**   int (*index)(int varix, int tabix);
**     \param varix  (in) current 'MIBVAR' index
**     \param tabix  (in) current data storage table/struct index
**     \retval -1    end of table reached
**     \retval 0     skip entry
**     \retval 1     valid entry
**
**   This index2() function is a more traditional MIB Handler index function
**   in that the entire requested table index is passed to the function and
**   there are variables used to return the resulting index/value for the
**   SNMP operation back to the agent. Note that the passed in index is
**   the exact data from the SNMP message.  The index is BER encoded so you
**   must handle any single index values that are potentially greater than
**   127.  If you don't then you most likely will break lexicographic ordering
**   or the table data.  For example the BER format of an integer can result in
**   the first (most sig) bit being set and make a small number look larger
**   than a larger num.  For example 30718 encodes to 0x81 0xef 0x7e and 10001
**   encodes to 0xce 0x11.  If a basic byte comparison is made then 10001 will
**   be considered larger than 30718 which is lexicraphically incorrect.  You
**   can safely assume the pointers returned are reentrant-safe since there is
**   only a single SNMP Agent processing requests. If you implement this
**   then you don't need to support the get() function for getting table
**   data since you return the get data from this function directly.
**
**   int (*index2)(int varix, SnmpOperationType oflag,
**                 const uint8_t * index, uint32_t indexLen,
**                 const uint8_t * resCharIndex, uint32_t * resIndexLen,
**                 void ** retValue);
**     \param varix        (in) current 'MIBVAR' index
**     \param oflag        (in) type of SNMP operation
**     \param index        (in) encoded OID Table index
**     \param indexLen     (in) length of the encoded OID Table index
**     \param resIndex     (out) resulting encoded OID Table index
**     \param resIndexLen  (out) length of the resulting encoded OID Table index
**     \param retValue     (out) data for resulting OID Table index (get/set)
**     \retval -1 end of table reached or error (i.e. invalid index)
**     \retval 0  valid entry (results in resIndex, resIndexLen, retValue)
**
**   An initialization function that is called when the MIB is registered
**   with the SNMP Agent.
**
**   int (*init)(uint16_t type);
**     \param type   (in) always 0
**     \retval void
**
**   This routine is called to check the validity of a value before it
**   is set via an SNMP SET operation.  If your MIB Handler contains a
**   table and you use the index() function then you should use check().
**   Likewise if you use the index2() function then you should use check2().
**   The table index passed to the check2() function is that returned by a
**   previous call to your index2() function.
**
**   int (*check)(int varix, int tabix, const uint8_t * inp);
**     \param varix  (in) current 'MIBVAR' index
**     \param tabix  (in) current data storage table/struct index
**     \param inp    (in) pointer to the BER encoded value to be set
**     \retval int   an SNMP_RV code
**
**   int (*check2)(int varix,
**                 const uint8_t * pIndex, uint32_t indexLen,
**                 const uint8_t * inp);
**     \param varix    (in) current 'MIBVAR' index
**     \param index    (in) encoded OID Table index
**     \param indexLen (in) length of the encoded OID Table index
**     \param inp      (in) pointer to the BER encoded value to be set
**     \retval int     an SNMP_RV code
*/
typedef struct
{
    const MIBVAR *mvp;      /*!< array of MIB variables */
    int (*numvars)(void);   /*!< function to return the number of variables */
    const MIBTAB *mtp;      /*!< array of MIB tables */
    int (*numtabs)(void);   /*!< function to return the number of tables */
    void (*get)(                                        /*!< get cbk */
        int varix, int tabix, uint8_t ** vvptr
    );
    int (*set)(int varix, int tabix);                   /*!< set cbk */
    int (*set2)(                                        /*!< set2 */
        int varix,
        const uint8_t *ind, uint32_t indexLen,
        uint8_t *data
    );
    int (*index)(int varix, int tabix);                 /*!< index cbk */
    int (*index2)(                                      /*!< index2 */
        int varix, SnmpOperationType oflag,
        const uint8_t *ind, uint32_t indexLen,
        uint8_t **resIndex, uint32_t *resIndexLen,
        void **retValue
    );
    void (*init)(uint16_t type);                        /*!< init cbk */
    int (*check)(                                       /*!< test cbk */
        int varix, int tabix, const uint8_t *inp
    );
    int (*check2)(                                      /*!< check2 */
        int varix,
        const uint8_t *ind, uint32_t indexLen,
        const uint8_t *inp
    );
} MIB;

/*! @} End of Group. */
