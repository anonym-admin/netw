#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define MAX_SIZE    1024

int main() 
{
    int client_sockfd;
    struct sockaddr_in client_sockaddr;
    char buf[MAX_SIZE] = {0,};
    int length = 0;

    if((client_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        assert(0);
    }

    // Connect
    memset(&client_sockaddr, 0, sizeof(client_sockaddr));
    client_sockaddr.sin_family = AF_INET;
    client_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    client_sockaddr.sin_port = htons(8080);
    
    if(-1 == connect(client_sockfd, (struct sockaddr*)&client_sockaddr, sizeof(client_sockaddr))) {
        perror("connect error: ");
        return -1;
    }

    read(0, buf, MAX_SIZE);

    if(write(client_sockfd, buf, MAX_SIZE) <= 0) {
        perror("write error: ");
        return -1;
    }

    if((length = read(client_sockfd, buf, MAX_SIZE)) <= 0) {
        perror("read error: ");
        return -1;
    }

    buf[length + 1] = '\0';
    printf("read: %s\n", buf);
    
    close(client_sockfd);
    return 0;
}