#include <stdio.h>
#include "structure.h"

void parse_packet (const uint8_t* packet)
{
    struct ethernet_hdr *eth = (struct ethernet_hdr *)packet;
    struct ipv4_hdr *ip = (struct ipv4_hdr *)(packet + sizeof(struct ethernet_hdr));
    struct tcp_hdr *tcp = (struct tcp_hdr *)(packet + sizeof(struct ethernet_hdr) + sizeof(struct ipv4_hdr));

    printf("%x\n", packet);
    if (eth->ether_type != 8)
        return;
    if (ip->ip_protocol != 6)
    {
        printf("size : %ld %ld %ld ", sizeof(struct ethernet_hdr),sizeof(struct ipv4_hdr),sizeof(struct tcp_hdr));
        printf("protocol : %x\n", ip->ip_protocol);
        return;
    }
        
    printf("src mac : %02x:%02x:%02x:%02x:%02x:%02x\n",
            eth->src_mac_addr[0], eth->src_mac_addr[1], eth->src_mac_addr[2],
            eth->src_mac_addr[3], eth->src_mac_addr[4], eth->src_mac_addr[5]);

    printf("dst mac : %02x:%02x:%02x:%02x:%02x:%02x\n",
       eth->dest_mac_addr[0], eth->dest_mac_addr[1], eth->dest_mac_addr[2],
       eth->dest_mac_addr[3], eth->dest_mac_addr[4], eth->dest_mac_addr[5]);
    printf("src_ip : %x\n", ip->ip_src);
    printf("src_ip : %x\n", ip->ip_dst);
    printf("src_port : %x\n", tcp->src_port);
    printf("src_port : %x\n", tcp->dest_port);
}





