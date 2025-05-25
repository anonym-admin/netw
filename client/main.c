#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>

int main() 
{
    int sockfd;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        assert(0);
    }


    return 0;
}