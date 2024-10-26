#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void print_manual(void) {
    printf("---- Manual of Simple Port TCP Scanner ----\n");
    printf("- First argument  -> IP Address\n");
    printf("- Second argument -> Port number or range port \n");
    printf("Example :\n");
    printf("    Single port scan (1 port)   : ./portscanner IP 21\n");
    printf("    Scanning port range         : ./portscanner IP 21-1024\n");
    printf("    or\n");
    printf("    Scanning port range         : ./portscanner IP 1 1024\n");
    printf("-----------------------------------------------------------\n");
}

int main(int argc, char* argv[]) {
 
    if (argc < 3) {
        print_manual();
        return 1; 
    }
    
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Error: Invalid arguments.\n");
        return 1;
    }
    
    struct sockaddr_in server_addr;
    int tcp_socket;
    const char * ip_addr        = argv[1];
    const char * port_arg       = argv[2];
    unsigned short port         = atoi(port_arg);
    
    printf("[+] Scanning: %s...\n", ip_addr);
    printf("[+] Scan is running on: %d\n", port);
   
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (tcp_socket < 0) {
        printf("Cannot create the socket\n");
        return -1;
    }
    
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);

    if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Port is closed\n");
    } else {
        printf("Port %d open!\n",port);
    }

    return 0;
}
