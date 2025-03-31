#include <stdio.h>
#include <arpa/inet.h>
#include "structure.h"
#include "utils.h"

void parse_packet (const uint8_t* packet)
{
    struct ethernet_hdr *eth = (struct ethernet_hdr *)packet;
    struct ipv4_hdr *ip = (struct ipv4_hdr *)(packet + sizeof(struct ethernet_hdr));
    struct tcp_hdr *tcp = (struct tcp_hdr *)(packet + sizeof(struct ethernet_hdr) + sizeof(struct ipv4_hdr));

    if (eth->ether_type != 8)
        return;
    if (ip->ip_protocol != 6)
    {
        
        return;
    }
        
    printf("Source MAC address       : ");
    print_mac(eth->src_mac_addr);
    printf("Destination MAC address  : ");
    print_mac(eth->dest_mac_addr);

    printf("Source IP address        : ");
    print_ip(ntohl(ip->ip_src));
    printf("Destination IP address   : ");
    print_ip(ntohl(ip->ip_dst));
    printf("Source Port Number       : %d\n", ntohs(tcp->src_port));
    printf("Destinamtion Port number : %d\n", ntohs(tcp->dest_port));
}

void print_mac(uint8_t *mac_addr)
{
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac_addr[0],mac_addr[1],mac_addr[2],
        mac_addr[3],mac_addr[4],mac_addr[5]);
}
void print_ip(uint32_t ip_addr)
{
    for(int i = 0; i < 4; i++)
    {
        printf("%d", (ip_addr >> (8 * (3-i))) & 0xff);
        if (i != 3)
            printf(".");
    }
    printf("\n");
}





