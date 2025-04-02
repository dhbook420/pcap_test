#include <stdio.h>
#include <stdint.h>

void parse_packet (const uint8_t* packet);
void print_mac(uint8_t *mac_addr);
void print_ip(uint32_t ip_addr);
void print_data(uint8_t *data_ptr, int len);