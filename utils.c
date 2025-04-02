#include <stdio.h>
#include <arpa/inet.h>
#include "structure.h"
#include "utils.h"

void parse_packet (const uint8_t* packet)
{
    struct ethernet_hdr *eth = (struct ethernet_hdr *)packet;
    struct ipv4_hdr *ip = (struct ipv4_hdr *)(packet + sizeof(struct ethernet_hdr));

    int ip_hdr_len = ((ip->ip_version_len) & 0x0f) << 2;
    struct tcp_hdr *tcp = (struct tcp_hdr *)((const uint8_t*)ip + ip_hdr_len);

    //data offset = (first 4bit of tcp_offset_reserved) x 4 
    int tcp_hdr_len = (((tcp->tcp_offset_reserved) & 0xf0) >> 4) << 2;
    uint8_t *data_ptr = (uint8_t *)((const uint8_t *)tcp + tcp_hdr_len);

    //check ethertype as IPv4 & tcp protocol 
    if (ntohs(eth->ether_type) != 0x0800)
        return;
    if (ip->ip_protocol != 6)
        return;
    
    printf("===================Header===================\n");
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
    printf("============================================\n");

    int data_len = ntohs(ip->tot_len) - ip_hdr_len - tcp_hdr_len;
    print_data(data_ptr, data_len);
    
    
    printf("\n\n\n");
}

void print_mac(uint8_t *mac_addr)
{
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n", 
        mac_addr[0],mac_addr[1],mac_addr[2],
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

void print_data(uint8_t *data_ptr, int len)
{
    if (len > 20)
        len = 20;
    

    printf("\nHexamedical Data (%d bytes) :\n", len);
    for (int i = 0; i < len; i ++)
    {
        printf("%02x ", (uint8_t)*(data_ptr + i));
    }
}




