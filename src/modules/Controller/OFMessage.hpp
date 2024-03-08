#ifndef __OFMESSAGE_HPP__
#define __OFMESSAGE_HPP__

#include <stdint.h>

#define OFP_VERSION 0x04 // version 1.3.1

#define OFP_ASSERT(bool_exptr) static_assert(bool_exptr);

/* Header on all OpenFlow packets. */
struct ofp_header {
    uint8_t version; /* OFP_VERSION. */
    uint8_t type; /* One of the OFPT_ constants. */
    uint16_t length; /* Length including this ofp_header. */
    uint32_t xid; /* Transaction id associated with this packet.
    Replies use the same id as was in the request
    to facilitate pairing. */
} __attribute__((packed));
OFP_ASSERT(sizeof(struct ofp_header) == 8);

enum ofp_type {
    /* Immutable messages. */
    OFPT_HELLO = 0, /* Symmetric message */
    OFPT_ERROR = 1, /* Symmetric message */
    OFPT_ECHO_REQUEST = 2, /* Symmetric message */
    OFPT_ECHO_REPLY = 3, /* Symmetric message */
    OFPT_EXPERIMENTER = 4, /* Symmetric message */
    /* Switch configuration messages. */
    OFPT_FEATURES_REQUEST = 5, /* Controller/switch message */
    OFPT_FEATURES_REPLY = 6, /* Controller/switch message */
    OFPT_GET_CONFIG_REQUEST = 7, /* Controller/switch message */
    OFPT_GET_CONFIG_REPLY = 8, /* Controller/switch message */
    OFPT_SET_CONFIG = 9, /* Controller/switch message */
    /* Asynchronous messages. */
    OFPT_PACKET_IN = 10, /* Async message */
    OFPT_FLOW_REMOVED = 11, /* Async message */
    OFPT_PORT_STATUS = 12, /* Async message */
    /* Controller command messages. */
    OFPT_PACKET_OUT = 13, /* Controller/switch message */
    OFPT_FLOW_MOD = 14, /* Controller/switch message */
    OFPT_GROUP_MOD = 15, /* Controller/switch message */
    OFPT_PORT_MOD = 16, /* Controller/switch message */
    OFPT_TABLE_MOD = 17, /* Controller/switch message */
    /* Multipart messages. */
    OFPT_MULTIPART_REQUEST = 18, /* Controller/switch message */
    OFPT_MULTIPART_REPLY = 19, /* Controller/switch message */
    /* Barrier messages. */
    OFPT_BARRIER_REQUEST = 20, /* Controller/switch message */
    OFPT_BARRIER_REPLY = 21, /* Controller/switch message */
    /* Queue Configuration messages. */
    OFPT_QUEUE_GET_CONFIG_REQUEST = 22, /* Controller/switch message */
    OFPT_QUEUE_GET_CONFIG_REPLY = 23, /* Controller/switch message */
    /* Controller role change request messages. */
    OFPT_ROLE_REQUEST = 24, /* Controller/switch message */
    OFPT_ROLE_REPLY = 25, /* Controller/switch message */
    /* Asynchronous message configuration. */
    OFPT_GET_ASYNC_REQUEST = 26, /* Controller/switch message */
    OFPT_GET_ASYNC_REPLY = 27, /* Controller/switch message */
    OFPT_SET_ASYNC = 28, /* Controller/switch message */
    /* Meters and rate limiters configuration messages. */
    OFPT_METER_MOD = 29, /* Controller/switch message */
};

/* OFPT_HELLO. This message includes zero or more hello elements having
* variable size. Unknown elements types must be ignored/skipped, to allow
* for future extensions. */
struct ofp_hello {
    struct ofp_header header;
    /* Hello element list */
    // struct ofp_hello_elem_header elements[0];
};
OFP_ASSERT(sizeof(struct ofp_hello) == 8);


#endif  // __OFMESSAGE_HPP__