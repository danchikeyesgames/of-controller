#include <cstring>
#include <string>
#include <map>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "OFMessage.hpp"

int main() {
    int sockfd, sockServFd;
    struct addrinfo hints, *servinfo2, *servinfo;
    int ret;

    // Connect to OFServer

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((ret = getaddrinfo("0.0.0.0", "6633", &hints, &servinfo2)) != 0) {
        printf("%s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    if ((sockServFd = socket(servinfo2->ai_family, servinfo2->ai_socktype, servinfo2->ai_protocol)) == -1) {
        perror("client: socket");
        printf("[+] client: socket\n");
        exit(EXIT_FAILURE);
    }

    printf("[+] Worker: CONNECT...\n");
    if (connect(sockServFd, servinfo2->ai_addr, servinfo2->ai_addrlen) == -1) {
        close(sockServFd);
        perror("client: connect");
        printf("[+] client: connect\n");
        exit(EXIT_FAILURE);
    }

    ofp_header* hder = new ofp_header;
    hder->type = OFPT_HELLO;
    int sz = send(sockServFd, (void* ) hder, sizeof(hder), 0);

    void* mmm = malloc(sizeof(ofp_header));
    recv(sockServFd, mmm, sizeof(ofp_header), 0);
    
    printf("[+] i recv message\n");

    ofp_header* echo = new ofp_header;
    echo->type = OFPT_ECHO_REQUEST;
    sz = send(sockServFd, echo, sizeof(echo), 0);

    void* mmm1 = malloc(sizeof(ofp_header));
    recv(sockServFd, mmm1, sizeof(ofp_header), 0);

    printf("[+] i recv message\n");

    char buffer[4096] = {0};
    while (true) {
        recv(sockServFd, buffer, 4096, 0);
        printf("[+] %s\n", buffer);
    }

}