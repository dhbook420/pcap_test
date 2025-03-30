#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include "structure.h"



void usage() {
	printf("syntax: pcap-test <interface>\n");
	printf("sample: pcap-test wlan0\n");
}

typedef struct {
	char* dev_;
} Param;

Param param = {
	.dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
	if (argc != 2) {
		usage();
		return false;
	}
	param->dev_ = argv[1];
	return true;
}

int main(int argc, char* argv[]) {
	if (!parse(&param, argc, argv))
		return -1;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
	if (pcap == NULL) {
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
		return -1;
	}

	printf("%s dev\n", param.dev_);
	while (true) {
		struct pcap_pkthdr* header;
		const uint8_t* packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		//pcap 	 : session handler
		//header : pointer to structure that holds metadata about packet
		//			(time sniffed, packet length, lenght of specific portion)
		//packet : pointer to real data 
		
		if (res == 0) continue;
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}
		printf("%u bytes captured\n", header->caplen);

		struct ethernet_hdr *eth = (struct ethernet_hdr *)packet;
		struct ipv4_hdr *ip = (struct ipv4_hdr *)(packet + sizeof(struct ethernet_hdr));
		struct tcp_hdr *tcp = (struct tcp_hdr *)(packet + sizeof(struct ethernet_hdr) + ip->ip_len);

		printf("ether type : %x\n", eth->ether_type);
		printf("ip len : %x\n", ip->ip_len);
		printf("src_port : %x\n", tcp->src_port);
	}

	pcap_close(pcap);
}
