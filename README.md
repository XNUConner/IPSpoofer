# IPSpoofer
C code to spoof the source IP of a UDP datagram, more info [here](https://dev.to/conner). <br />
Binary sends a single 1500 byte datagram with a spoofed ip defined in `src/main.c` to a destination IP, `argv[1]` <br />
Compatibility: Linux, FreeBSD, OpenBSD <br />
Compilation: `make src/main` <br />
Usage: `./src/main <destination ip>` <br />
Configuration: edit `src/main.c` <br />

### Technical details
1. `src/main.c` opens a raw UNIX socket, and provides the kernel with manually constructed UDP/IP protocol stack headers. <br />
2. The IP header is constructed with a *spoofed* IP. <br />
3. UDP header is constructed with configurable ports, although a UDP header is not necessary, but utilized in `netcat` testing. <br />
4. Datagram is constructed using `memcpy()` calls. <br />
5. Socket is opened to represent the destination IP. <br />
6. Datagram is repeatedly sent to destination host with a 1 second delay. <br />
7. `SIGTERM` *(ctrl+c)* is used to end the process gracefully. <br />

NOTE: The `sleep(1)` function in the `sendto()` for loop can be removed from `src/main.c` in order to packet flood the destination IP. <br />
Certain DDOS attacks can be amplified via spoofed IP packet headers, see [this cloudflare article](https://www.cloudflare.com/learning/ddos/dns-amplification-ddos-attack/).
