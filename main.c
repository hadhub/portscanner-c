#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void print_man(void) {
    printf("---- Manual of Simple Port TCP Scanner ----\n");
    printf("- First argument  -> IP Address\n");
    printf("eg. \n");
    printf("    Single port scan (default port) : ./portscanner IP\n");
    printf("-----------------------------------------------------------\n");
}

int main(int argc, char* argv[]) {
    int default_ports[]     = {21,22,53,80,88,389,443,445,3389,5985,8080};
    int len                 = sizeof(default_ports) / sizeof(default_ports[0]);
    const char * ip_addr    = argv[1];
    if (argv[1] == NULL) {
        fprintf(stderr, "Error: Invalid arguments.\n");
        return 1;
    }
    int tcp_socket;
    struct sockaddr_in server_addr;
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    printf("[*] Scanning: %s \n", ip_addr);
    for (int i = 0; i < len; i++) {
        tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (tcp_socket < 0) {
            perror("Socket creation failed");
            continue;
        }
        server_addr.sin_port = htons(default_ports[i]);
        if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
            printf("[+] Port %d open\n", default_ports[i]);
            close(tcp_socket);
        }
    }
    return 0;
}
