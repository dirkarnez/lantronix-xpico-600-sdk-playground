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
#include <machine/endian.h>

#include "ltrx_definitions.h"

/*****************************************************************************/
/*                           Documentation                                   */
/*****************************************************************************/

/*!
** \file
** \brief Definitions related to Networking.
*/

/*****************************************************************************/
/*                             Defines                                       */
/*****************************************************************************/

#define LTRX_CFG_PORT_CHECK__ANY_LINE (MAX_LOGICAL_SERIAL_LINES + 1)

#define LTRX_IP_DISPLAY__MINIMUM_BUFFER_LENGTH 45

#define LTRX_IP_AND_PORT_DISPLAY__MINIMUM_BUFFER_LENGTH 53

#define LTRX_NETWORK_PROTOCOL_NAME_STRLEN_MAX 15

/*!
** \ingroup tcp
** Specifies to listen on all interfaces.
*/
#define LTRX_TCP_LISTENER__ANY_INTERFACE 0xff

/*!
** \ingroup ip
** Specifies to count readiness on all interfaces.
*/
#define LTRX_IP_ADDRESS_STATE__ALL_INTERFACES 0xff

/*!
** \ingroup ip
** Specifies to count readiness on non-AP interfaces.
*/
#define LTRX_IP_ADDRESS_STATE__NON_AP_INTERFACES 0xfe

/*****************************************************************************/
/*                              Macros                                       */
/*****************************************************************************/

#define IP_V4_ADDRESS(a, b, c, d) \
    ( \
        (((unsigned long)a) << 24) | \
        (((unsigned long)b) << 16) | \
        (((unsigned long)c) << 8) | \
        ((unsigned long)d) \
    )

#if _BYTE_ORDER == _LITTLE_ENDIAN
# define htonl(_x) __bswap32(_x)
# define htons(_x) __bswap16(_x)
# define ntohl(_x) __bswap32(_x)
# define ntohs(_x) __bswap16(_x)
#else
# define htonl(_x) (_x)
# define htons(_x) (_x)
# define ntohl(_x) (_x)
# define ntohs(_x) (_x)
#endif

#define IN_LINKLOCAL(_a)    (((_a) & 0xFFFF0000) == 0xA9FE0000)

/*****************************************************************************/
/*                              Enums                                        */
/*****************************************************************************/

enum ltrx_cfg_port_check_service_based_on
{
    LTRX_CFG_PORT_CHECK_SERVICE_BASED_ON__TCP,
    LTRX_CFG_PORT_CHECK_SERVICE_BASED_ON__UDP
};

enum ltrx_ip_version
{
    LTRX_IP_VERSION__INVALID = 0,
    LTRX_IP_VERSION__4 = 4,
    LTRX_IP_VERSION__6 = 6,
};

/*!
** \ingroup network_protocols
** Used by ltrx_network_allowed_protocols() and
** ltrx_network_lookup_network_protocol().
**
** More than one of these values may be "or'ed" together.
**
** If neither \c LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__TCP nor
** \c LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__UDP is set,
** both TCP and UDP are allowed.
*/
enum ltrx_network_allowed_protocols_flag
{
    /*! Requires non-blocking send. */
    LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__REQUIRE_NONBLOCKING = 0x0001,
    /*! Requires client. */
    LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__CLIENT = 0x0002,
    /*! Requires server. */
    LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__SERVER = 0x0004,
    /*! Allow TCP based. */
    LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__TCP = 0x0008,
    /*! Allow UDP based. */
    LTRX_NETWORK_ALLOWED_PROTOCOLS_FLAGS__UDP = 0x0010,
};

enum ltrx_network_packet_pool
{
    LTRX_NETWORK_PACKET_POOL__TRANSMIT = 0,
    LTRX_NETWORK_PACKET_POOL__RECEIVE = 1
};

/*!
** \ingroup network_protocols
** \a How in \c protocolShutdown call.
*/
enum ltrx_network_protocol_shutdown
{
    LTRX_NETWORK_PROTOCOL_SHUTDOWN__SEND = 0, /*!< Send direction only. */
    LTRX_NETWORK_PROTOCOL_SHUTDOWN__RECEIVE = 1, /*!< Receive direction only. */
    LTRX_NETWORK_PROTOCOL_SHUTDOWN__BOTH = 2 /*!< Both directions. */
};

/*!
** \ingroup network_protocols
** Return code from \c optProtocolSendDataNonBlocking.
*/
enum ltrx_network_return
{
    LTRX_NETWORK_RETURN__WORKING, /*!< Working. */
    LTRX_NETWORK_RETURN__SUCCESS, /*!< Success. */
    LTRX_NETWORK_RETURN__FAILURE /*!< Failure. */
};


enum ltrx_network_entry_type
{
	LTRX_NETWORK_ENTRY_TYPE__IP_ADDRESS,
	LTRX_NETWORK_ENTRY_TYPE__IP_ADDRESS_CIDR
};

/*****************************************************************************/
/*                             Structs                                       */
/*****************************************************************************/

struct ltrx_country_table_entry;
struct ltrx_ip_socket;
struct ltrx_network_packet;
struct ltrx_network_protocol_handle;
struct ltrx_trigger;
struct ltrx_write_user_message_info;

struct ltrx_bridge_counters
{

};

/*!
** \ingroup ip
** Holds an IP v4 or v6 address.
*/
struct ltrx_ip_address
{
    enum ltrx_ip_version version;
    union
    {
        uint32_t v4;
        uint32_t v6[4];
    } ip;
};

/*!
** \ingroup network_protocols
** \brief Represents a network protocol for registration.
**
** This struct designates the procedures to support a Network protocol.
** It it used with ltrx_network_register_protocol().
**
** Note that your struct must persist, so you will typically declare it
** <tt>static const</tt>.
*/
struct ltrx_network_protocol
{
    /*!
    ** Name of this protocol as it will appear in configuration menu choices.
    */
    const char *protocolName;
    unsigned int isTcpBased : 1; /*!< 1 if layered over TCP. */
    unsigned int isUdpBased : 1; /*!< 1 if layered over UDP. */
    unsigned int isClient : 1; /*!< 1 if supports client role. */
    unsigned int isServer : 1; /*!< 1 if supports server (listener) role. */
    unsigned int requiresCredentials : 1; /*!< 1 if credentials are used. */
    /*!
    ** \brief Constructor.
    **
    ** This \a constructor function performs initialization, typically
    ** allocating necessary memory or other resources.
    ** \returns Abstract \a handle to be used with subsequent network
    ** functions.
    ** \retval NULL Failed.
    ** \param [in] lnp Pointer to this structure.
    ** \param [in] optCredential Name of credential if required,
    ** otherwise \c NULL.
    */
    struct ltrx_network_protocol_handle *(*protocolConstructor)(
        const struct ltrx_network_protocol *lnp,
        const char *optCredential
    );
    /*!
    ** \brief Destructor.
    **
    ** This \a destructor function performs shutdown, typically
    ** freeing any memory or resources allocated by the constructor.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    void (*protocolDestructor)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Establish connection.
    **
    ** Perform any necessary handshakes to establish this protocol layer
    ** connection.
    ** This is called after the underlying TCP or UDP layer is established.
    **
    ** \b Caution: This function may block until it either succeeds or fails.
    ** \retval true Success.
    ** \retval false Failed.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [in,out] lis Socket with established connection.
    ** \param [in] optionalHostname Hostname or NULL.
    */
    bool (*protocolEstablishConnection)(
        struct ltrx_network_protocol_handle *lnph,
        struct ltrx_ip_socket *lis,
        const char *optionalHostname
    );
    /*!
    ** \brief Close connection.
    **
    ** Perform any necessary handshakes to gracefully close this protocol
    ** layer connection.
    ** This is called after this protocol layer has been established.
    **
    ** \b Caution: This function may block until it either succeeds or fails.
    ** \retval true Success.
    ** \retval false Failed.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    bool (*protocolCloseConnection)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Is credential found?
    **
    ** For protocols which require a credential,
    ** this tests that the lookup was successful.
    ** This may be called after this protocol layer has been constructed.
    **
    ** \retval true Credential found in lookup.
    ** \retval false Connection not found.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    bool (*optProtocolCredentialIsFound)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Is connection active?
    **
    ** Checks if a connection is currently active.
    ** This may be called after this protocol layer has been constructed.
    **
    ** \retval true Connection is active.
    ** \retval false Connection is inactive.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    bool (*optProtocolIsConnectionActive)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Send data.
    **
    ** This is called after this protocol layer has been established.
    **
    ** \b Caution: This function may block until it either succeeds or fails.
    ** \retval true Success.
    ** \retval false Failed.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [in] data Data to send.
    ** \param [in] length Length of data to send.
    ** \param [in] push If \c true, force the protocol layer to forward data
    ** now, unless no data has been buffered.
    */
    bool (*protocolSendData)(
        struct ltrx_network_protocol_handle *lnph,
        const void *data,
        size_t length,
        bool push
    );
    /*!
    ** \brief Send data non-blocking.
    **
    ** A protocol implementation optionally supplies this function to
    ** support non-blocking calls.
    ** If not implemented, the protocol implementation sets this function
    ** pointer to \c NULL.
    ** Some applications may require non-blocking calls, so will not operate
    ** with a protocol implementation that does not supply it.
    **
    ** This is called after this protocol layer has been established.
    **
    ** The caller must retain the integrity of \a data if it sees a
    ** return code of \c LTRX_NETWORK_RETURN__WORKING.
    ** In this case the caller must periodically call again, with
    ** \a length of \c 0 and \a push unchanged or \c false,
    ** until it sees \c LTRX_NETWORK_RETURN__SUCCESS or
    ** \c LTRX_NETWORK_RETURN__FAILURE returned.
    ** The caller may use \a sendTrigger to expedite this periodic calling,
    ** but may not rely on being triggered
    ** (must also use a reasonable timeout).
    **
    ** Note that with \a push of \c false, a return code of
    ** \c LTRX_NETWORK_RETURN__SUCCESS does \b NOT imply that the data has been
    ** transmitted, but merely buffered.
    ** To transmit the data, you will need to either call this with \a push of
    ** \c true, or call \c protocolCloseConnection.
    **
    ** \retval LTRX_NETWORK_RETURN__WORKING Operation in progress.
    ** \retval LTRX_NETWORK_RETURN__SUCCESS Success.
    ** \retval LTRX_NETWORK_RETURN__FAILURE Failed.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [in] data Data to send.
    ** \param [in] length Length of data to send.
    ** \param [in] push If \c true, force the protocol layer to forward data
    ** now, unless no data has been buffered.
    ** \param [in] sendTrigger This trigger may be signaled when the operation
    ** is complete.
    */
    enum ltrx_network_return (*optProtocolSendDataNonBlocking)(
        struct ltrx_network_protocol_handle *lnph,
        const void *data,
        size_t length,
        bool push,
        struct ltrx_trigger *sendTrigger
    );
    /*!
    ** \brief Is data available?
    **
    ** Checks if any data is available for receive.
    ** This may be called after this protocol layer has been established.
    **
    ** \retval true One or more bytes are available.
    ** \retval false No data is available.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    bool (*protocolIsDataAvailable)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief How much data can be sent?
    **
    ** Checks how many bytes can now be accepted for sending.
    ** This may be called after this protocol layer has been established.
    **
    ** \returns Number of bytes that may be sent.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    size_t (*protocolCanSend)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Is receive at end of file?
    **
    ** Checks if all receive data has been read and a \c FIN has been received.
    ** This may be called after this protocol layer has been established.
    **
    ** \retval true No more receive data will be available.
    ** \retval false More data might become available.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    */
    bool (*protocolIsEndOfFile)(
        struct ltrx_network_protocol_handle *lnph
    );
    /*!
    ** \brief Receive data.
    **
    ** This may be called after this protocol layer has been established.
    **
    ** \b Note: Any data under the returned \a dataPointerLocation will remain
    ** intact until the next call to \c protocolReceiveData or
    ** \c protocolCloseConnection.
    **
    ** \returns Number of bytes that have been received.
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [out] dataPointerLocation Points to data pointer that will be
    ** filled in if any bytes have been received.
    ** \param [in] length Maximum number of bytes that may be read by this
    ** operation.
    */
    size_t (*protocolReceiveData)(
        struct ltrx_network_protocol_handle *lnph,
        const uint8_t **dataPointerLocation,
        size_t length
    );
    /*!
    ** \brief Protocol shutdown.
    **
    ** This may be called after this protocol layer has been established.
    **
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [in] how Specifies directions of flow to be shut down.
    */
    void (*protocolShutdown)(
        struct ltrx_network_protocol_handle *lnph,
        enum ltrx_network_protocol_shutdown how
    );
    void (*optProtocolWarnings)(
        const struct ltrx_network_protocol_handle *ephemeralHandle,
        const struct ltrx_network_protocol_handle *operationalHandle,
        const char *optIdentity,
        const char *currentCredential,
        const struct ltrx_write_user_message_info *lwumi
    );
    /*!
    ** \brief Has the configured credential been changed?
    **
    ** This may be called after this protocol layer has been established.
    **
    ** The application will call this to see if any changes have been made
    ** to the credential configuration, which it only knows by the
    ** credential name.
    ** Typically the application will close any current connections when it
    ** learns that a change has been made.
    **
    ** \param [in,out] lnph Abstract handle from \a constructor.
    ** \param [in] currentCredential Current name of credential.
    */
    bool (*protocolCredentialHasChanged)(
        struct ltrx_network_protocol_handle *lnph,
        const char *currentCredential
    );
};

/*!
** \ingroup tcp
** \brief Abstract structure containing data for TCP listener.
*/
struct ltrx_tcp_listener
{
#if MAX_NETS_LOOPBACK >= 1
	OPAQUE_STRUCT(96); // By including loopback interface the structure size required is 96 bytes
#else
	OPAQUE_STRUCT(92);
#endif
};

typedef struct SNMP_NETWOK_PARAMS_STRUCT
{
	bool linkUp;
	bool linkDown;
}SNMP_NETWOK_PARAMS;

typedef struct SNMP_PARAMS_STRUCT
{
  bool coldstart;
  bool warmStart;
  SNMP_NETWOK_PARAMS interface[NETS_TOTAL_NUM];
}SNMP_PARAMS;

/*!
** \ingroup udp
** \brief Contains parameters for ltrx_udp_socket_open_with_options().
*/
struct ltrx_udp_socket_options
{
    /*!
    ** [in] Index for the desired interface (if available on the platform).
    ** \arg \c NETS_SOFTAP_START for ap0.
    ** \arg \c NETS_ETHERNET_START for eth0.
    ** \arg \c NETS_WLAN_START for wlan0.
    */
    uint8_t zeroBasedInterface;
    /*!
    ** [in] If non-zero, specifies the local port.
    ** If \c 0, a random unused UDP port number will be assigned.
    */
    uint16_t optLocalPort;
    /*!
    ** [in] If non-NULL, names a destination address.
    */
    const char *optRemoteAddress;
    /*!
    ** [in] If non-0, specifies a remote port.
    */
    uint16_t optRemotePort;
    /*!
    ** [in] If true, received packets whose from address and port do not match
    ** the designated remote address and port will be discarded.
    ** In listen mode, the remote address and port of the first received packet
    ** are taken as designated until the socket is closed.
    */
    bool receptionIsRestricted;
    /*!
    ** [in] If present, the specified trigger will subsequently be signaled
    ** when data is received.
    ** Otherwise, fill in \c NULL.
    */
    struct ltrx_trigger *optReceiveEventTrigger;
    /*!
    ** [in] If present, the function will be called when data is received.
    ** Otherwise, fill in \c NULL.
    */
    void (*optReceiveCallback)(struct ltrx_ip_socket *);
    /*!
    ** [in] If present, the function will be called when the UDP socket
    ** receives a packet from a different remote address or port.
    ** Otherwise, fill in \c NULL.
    */
    void (*optNewConnectionCallback)(
        void *opaque,
        const struct ltrx_ip_address *remoteAddress,
        uint16_t remotePort
    );
    /*!
    ** [in] If and when \c optNewConnectionCallback is called, its "opaque"
    ** parameter will be filled in with this value.
    */
    void *optOpaque;
};

/*****************************************************************************/
/*                             Globals                                       */
/*****************************************************************************/

#if MAX_NETS_ETHERNET > 0
extern uint8_t g_networkEthernetBridgeDynamicMac[6];
#endif

extern bool s_NetworkInterfaceIsUp[NETS_TOTAL_NUM];

extern SNMP_PARAMS snmpParams;

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

bool ltrx_arp_hardware_address_find(
    uint8_t zeroBasedInterface,
    uint32_t ipV4Address,
    uint8_t *hardwareAddressValue,
    size_t hardwareAddressSize,
    bool pingIfNotFound
);

void ltrx_cfg_port_check_configure(
    const char *serviceName,
    uint16_t optOneBasedLineIndex,
    const char *optSubServiceName,
    uint16_t optOneBasedSubServiceIndex,
    enum ltrx_cfg_port_check_service_based_on basedOn,
    uint8_t optOneBasedInterfaceIndex,
    uint16_t initialPort
);

void ltrx_cfg_port_check_default(
    const char *serviceName,
    uint16_t optOneBasedLineIndex,
    const char *optSubServiceName,
    uint16_t optOneBasedSubServiceIndex,
    enum ltrx_cfg_port_check_service_based_on basedOn,
    uint8_t optOneBasedInterfaceIndex,
    uint16_t defaultPort
);

bool ltrx_cfg_port_check_network_port_is_active(
    enum ltrx_cfg_port_check_service_based_on protocol,
    uint8_t zeroBasedInterfaceIndex,
    uint16_t port
);

void ltrx_cfg_port_check_proposal(
    const char *serviceName,
    uint16_t optOneBasedLineIndex,
    const char *optSubServiceName,
    uint16_t optOneBasedSubServiceIndex,
    enum ltrx_cfg_port_check_service_based_on basedOn,
    uint8_t optOneBasedInterfaceIndex,
    uint16_t proposedPort
);

void ltrx_cfg_port_check_start(void);

bool ltrx_cfg_port_check_wrapup(
    bool set,
    const struct ltrx_write_user_message_info *lwumi
);

void ltrx_checksum_adjust(
    uint8_t *checksum,
    const uint8_t *oldPointer,
    const uint8_t *newPointer,
    size_t length
);

uint32_t ltrx_dhcp_client_get_server_ipv4_address(
    uint8_t zeroBasedInterface
);

void ltrx_dhcp_client_get_server_mac_address(
    uint8_t zeroBasedInterface,
    uint8_t *macAddress
);

bool ltrx_host_is_numeric_form(
    const char *hostname
);

bool ltrx_wlan_get_rssi(
    int32_t *rssiPowerValue, uint8_t *rssiScaledValue
);

bool ltrx_host_lookup(
    const char *hostname,
    uint32_t timeout_ms,
    uint8_t *zeroBasedInterface,
    struct ltrx_ip_address *ipaddr
);

bool ltrx_ip_address_register_change_notification(
    uint8_t zeroBasedInterface,
    void (*notifyFunction)(
        uint8_t zeroBasedInterface,
        struct ltrx_ip_address *newIpAddress,
        void *pOpaque
    ),
    void *pOpaque
);

uint8_t ltrx_interface_name_to_one_based_index(
    const char *name
);

uint8_t ltrx_ip_address_state(
    uint8_t zeroBasedInterface
);

void ltrx_ip_addresses_get(
    uint8_t zeroBasedInterface,
    struct ltrx_ip_address addressArray[],
    uint8_t addressCount
);

bool ltrx_ip_and_port_display(
    char *outputBuffer,
    size_t bufferLength,
    const struct ltrx_ip_address *ipAddress,
    uint16_t port
);

bool ltrx_ip_display(
    char *outputBuffer,
    size_t bufferLength,
    const struct ltrx_ip_address *ipAddress
);

void ltrx_ip_get_ipv4_address_and_mask(
    uint8_t zeroBasedInterface,
    uint32_t *optAddress,
    uint32_t *optMask
);

void ltrx_ip_set_ipv4_parameters(
    uint8_t zeroBasedInterface,
    uint32_t address,
    uint32_t mask,
    uint32_t gateway,
    uint32_t primaryDns,
    uint32_t secondaryDns
);

#ifdef LANTRONIX_USE_IPV6_BRIDGING
bool ltrx_ip_check_ipv6_address_local(
    uint8_t zeroBasedInterface,
    uint32_t *optIpv6Address,
    uint32_t *optIpv6Mask
);

/* Tell the given interface (typically wlan0 in bridge mode) to
 * accept the solicited-node multicast for a bridged device's IPv6
 * address. Without this, the NXP Wi-Fi driver's hardware multicast
 * MAC filter drops the upstream router/DHCPv6 server's NS for that
 * address (33:33:ff:XX:XX:XX), and the bridged device's DHCPv6 /
 * NDP exchange stalls. Idempotent within a single binding; called
 * by bridge_mac.c on new bindings only.
 *
 * ipv6AddressNetworkOrder is a 16-byte big-endian buffer. */
bool ltrx_ip_join_ipv6_solicited_node_multicast(
    uint8_t zeroBasedInterface,
    const uint8_t *ipv6AddressNetworkOrder
);

void ltrx_ip_set_ipv6_parameters(
    uint8_t zeroBasedInterface,
    uint32_t *assignedIpv6Add,
    uint32_t *gateway,
    uint32_t *primaryDns,
    uint32_t *secondaryDns
);

bool ltrx_ip_del_ipv6_parameters(
    uint8_t zeroBasedInterface,
    uint32_t *assignedIpv6Add,
    uint32_t *gateway,
    uint32_t *primaryDns,
    uint32_t *secondaryDns
);
#endif /* LANTRONIX_USE_IPV6_BRIDGING */

size_t ltrx_ip_socket_can_send(
    struct ltrx_ip_socket *socket
);

void ltrx_ip_socket_get_local_information(
    struct ltrx_ip_socket *socket,
    int32_t *optZeroBasedInterface,
    uint16_t *optLocalPort
);

void ltrx_ip_socket_get_peer_information(
    struct ltrx_ip_socket *socket,
    struct ltrx_ip_address *optRemoteAddress,
    uint16_t *optRemotePort
);

bool ltrx_ip_socket_has_data(
    struct ltrx_ip_socket *socket,
    uint32_t blockTimeMsec
);

size_t ltrx_ip_socket_receive(
    struct ltrx_ip_socket *socket,
    uint8_t **dataPointerLocation,
    size_t length
);

bool ltrx_ip_socket_send(
    struct ltrx_ip_socket *socket,
    const void *data,
    size_t length,
    bool push
);

void ltrx_ip_socket_signal_receive_event(
    struct ltrx_ip_socket *socket
);

void ltrx_ip_socket_shutdown(
    struct ltrx_ip_socket *socket,
    enum ltrx_network_protocol_shutdown how
);

const char *ltrx_network_allowed_protocols(
    unsigned int zeroBasedIterator,
    enum ltrx_network_allowed_protocols_flag flags
);

bool ltrx_network_get_mac_address(
    uint8_t zeroBasedInterface,
    void *mac,
    size_t size
);

const struct vardef_values_interface *ltrx_network_interface_configuration_get(
    uint8_t zeroBasedInterface
);

const char *ltrx_network_interface_get_name(
    uint8_t zeroBasedInterface
);

bool ltrx_network_interface_status_get(uint8_t zeroBasedInterface);

const struct ltrx_network_protocol *ltrx_network_lookup_network_protocol(
    const char *protocolName,
    enum ltrx_network_allowed_protocols_flag flags
);

struct ltrx_network_packet *ltrx_network_packet_allocate(void);

bool ltrx_network_packet_append_data(
    struct ltrx_network_packet *p,
    const void *data,
    size_t length
);

struct ltrx_network_packet *ltrx_network_packet_copy(
    struct ltrx_network_packet *originalPacket
);

void ltrx_network_packet_release(
    struct ltrx_network_packet *p
);

uint8_t *ltrx_network_packet_get_current_piece_data_pointer(
    struct ltrx_network_packet *p
);

size_t ltrx_network_packet_get_current_piece_size(
    struct ltrx_network_packet *p
);

struct ltrx_network_packet *ltrx_network_packet_get_next_queued(
    struct ltrx_network_packet *p
);

void ltrx_network_packet_send(
    struct ltrx_network_packet *p,
    uint8_t zeroBasedInterface
);

void ltrx_network_packet_set_next_queued(
    struct ltrx_network_packet *p,
    struct ltrx_network_packet *next
);

void ltrx_network_register_protocol(
    const struct ltrx_network_protocol *lnp
);

struct ltrx_ip_socket *ltrx_tcp_accept(
    struct ltrx_tcp_listener *listener,
    struct ltrx_trigger *optReceiveEventTrigger
);

struct ltrx_ip_socket *ltrx_tcp_connect(
    uint16_t optLocalPort,
    const char *remoteAddress,
    uint16_t remotePort,
    struct ltrx_trigger *optReceiveEventTrigger
);

bool ltrx_tcp_listen(
    const struct ltrx_tcp_listener *listener,
    uint32_t blockTimeMsec
);

bool ltrx_tcp_listener_begin(
    struct ltrx_tcp_listener *listener,
    uint8_t zeroBasedInterface,
    uint16_t localPort,
    uint8_t backlog,
    struct ltrx_trigger *optListenerTrigger
);

void ltrx_tcp_listener_end(
    struct ltrx_tcp_listener *listener
);

bool ltrx_tcp_socket_close(
    struct ltrx_ip_socket *socket,
    uint32_t lingerMsec
);

bool ltrx_tcp_socket_is_closed(
    struct ltrx_ip_socket *socket
);

bool ltrx_tcp_socket_is_eof(
    struct ltrx_ip_socket *socket
);

bool ltrx_tcp_socket_send(
    struct ltrx_ip_socket *sock,
    const void *data,
    size_t length,
    bool push
);

enum ltrx_network_return ltrx_tcp_socket_send_nonblocking(
    struct ltrx_ip_socket *socket,
    const void *data,
    size_t length,
    bool push,
    struct ltrx_trigger *sendTrigger
);

void ltrx_tcp_socket_shutdown(
    struct ltrx_ip_socket *socket
);

void ltrx_udp_socket_close(
    struct ltrx_ip_socket *sock
);

bool ltrx_udp_socket_get_received_packet_information(
    struct ltrx_ip_socket *sock,
    struct ltrx_ip_address *optRemoteAddress,
    uint16_t *optRemotePort
);

bool ltrx_udp_socket_get_received_packet_mac(
    struct ltrx_ip_socket *sock,
    uint8_t *mac
);

bool ltrx_udp_socket_is_active(
    struct ltrx_ip_socket *sock
);

bool ltrx_udp_socket_multicast_join(
    uint8_t zeroBasedInterface,
    struct ltrx_ip_address *groupAddress
);

struct ltrx_ip_socket *ltrx_udp_socket_open(
    uint8_t zeroBasedInterface,
    uint16_t optLocalPort
);

struct ltrx_ip_socket *ltrx_udp_socket_open_with_options(
    const struct ltrx_udp_socket_options *luso
);

bool ltrx_udp_socket_reply(
    struct ltrx_ip_socket *socket,
    size_t length
);

bool ltrx_udp_socket_send(
    struct ltrx_ip_socket *sock,
    const struct ltrx_ip_address *address,
    uint16_t port,
    const void *data,
    size_t length
);

bool ltrx_text_to_ip_address(
    const char *input,
    uint8_t *output,
    enum ltrx_network_entry_type entryType
);

bool ltrx_get_oem_mac_address(
    uint8_t zeroBasedInterface,
    uint8_t *buffer,
    size_t length
);

bool ltrx_ip_socket_is_okay(
	struct ltrx_ip_socket *socket
);

const struct ltrx_country_table_entry *ltrx_network_lookup_country_table_entry(
    uint8_t ltrxVardefEnumRegionCode
);

#if defined(LANTRONIX_EN18031)
bool haveNewUrlAfterReboot(
    uint8_t zeroBasedInterfaceIndex,
    bool isSecure
);
#endif
