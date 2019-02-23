#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8877
#define MAXLEN 1024

int main() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0))<0) {
        perror("Error creating socket\n");
        exit(EXIT_FAILURE);
    }
    if ((bind(sock, (struct sockaddr*)&addr, sizeof(addr)))<0) {
        perror("Error binding socket\n");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in client;
    int client_len = 0;
    
    char buffer[MAXLEN];
    int n;
    while (1) {
        n = recvfrom(sock, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&client, &client_len);
        sendto(sock, buffer, n, 0, (struct sockaddr*)&client, client_len);
    }
}
    
