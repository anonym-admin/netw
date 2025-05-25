#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define MAX_SIZE    1024

int main(int argc, char* argv[]) 
{
    int listen_sockfd;
    int client_sockfd;
    struct sockaddr_in server_addr;
    
    // Create listen socket.
    if((listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket error: ");
        return -1;   
    }

    // Set server IP address and port number
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));   
    bind(listen_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Listen
    listen(listen_sockfd, SOMAXCONN);

    printf("Server Running...\n");

    while(1) {
        char buf[MAX_SIZE] = {0,};
        int length = 0;

        // Accept
        struct sockaddr_in client_addr;
        int addr_len = sizeof(client_addr);
        client_sockfd = accept(listen_sockfd, (struct sockaddr*)&client_addr, &addr_len);

        printf("New Client Connect: %s\n", inet_ntoa(client_addr.sin_addr));

        if((length = read(client_sockfd, buf, MAX_SIZE)) <= 0) {
            close(client_sockfd);
            continue;
        }

        if(write(client_sockfd, buf, MAX_SIZE) <= 0) {
            perror("write error: ");
            close(client_sockfd);
        }
        
        close(client_sockfd);
    }

    close(listen_sockfd);
    return 0;
}