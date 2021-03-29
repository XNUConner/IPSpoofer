#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/udp.h>
#include<arpa/inet.h>

void signalCatch(int socket);

int main(int argc, char** argv) {
    // Ensure proper usage
	if(argc != 2) {
		fprintf(stderr, "ERROR: destination IP not supplied.\n");
		return -1;
	}

	// Configuration
	char* dest_addr = argv[1];
	uint16_t dest_port = 9000;
	char* src_addr = "1.2.3.4";
	uint16_t src_port = 1234;

	uint16_t packet_size = 1500; // max is your wifi, eth or loopback device's MTU.

	// Create raw socket (requires root uid)
	int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(s == -1) {
		perror("ERROR: failed to create socket");
		return -1;
	}

    // Capture ctrl+c
    signal(SIGINT, signalCatch);

    // Calculate data length and create data buffer
	uint16_t datalen = packet_size - ( sizeof(struct ip) + sizeof(struct udphdr)); // sizeof() will always be 20 & 8 respectively.
	unsigned char data[datalen];
    if(packet_size < sizeof(struct ip) + sizeof(struct udphdr) + 1) {
        fprintf(stderr, "ERROR: packet_size must be >= 29\n");
        return -1;
    }
}

void signalCatch(int socket) {
    printf("\nClosing socket.\n");
    close(socket);
    exit(0);
}
