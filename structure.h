#include <stdint.h>
#include <netinet/in.h>

struct ethernet_hdr /*only for Ethernet II*/
{
    uint8_t  dest_mac_addr[6];        /* destination ethernet address 6byte */
    uint8_t  src_mac_addr[6];        /* source ethernet address 6byte*/
    uint16_t ether_type;            /* protocol : 2byte*/
};


struct ipv4_hdr
{
    uint8_t    ip_version_ihl;        /* version 4bit + ihl 4bit*/
    uint8_t    ip_tos;                /* type of service (dscp + ecn)*/
    uint16_t   ip_len;                /* total length */
    uint16_t   ip_id;                 /* identification */
    uint16_t   ip_offset;             /* flags + fragment offset*/ 
    uint8_t    ip_ttl;              /* time to live */
    uint8_t    ip_p;                /* protocol */
    uint16_t   ip_sum;              /* header checksum */
    struct in_addr ip_src, ip_dst;   /* source and dest address */
};


struct tcp_hdr
{
    uint16_t src_port;       /* source port */
    uint16_t dest_port;       /* destination port */
    uint32_t seq_num;          /* sequence number */
    uint32_t ack_num;          /* acknowledgement number */
    uint8_t  tcp_offset_reserved;         /* data offset, reserved */
    uint8_t  th_flags;       /* control flags */
    uint16_t th_win;         /* window */
    uint16_t th_sum;         /* checksum */
    uint16_t th_urp;         /* urgent pointer */
};