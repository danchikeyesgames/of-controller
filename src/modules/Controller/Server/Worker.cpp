#include <cstring>
#include <string>
#include <map>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "common/log/logger.hpp"

int main(int argc, char* argv[]) {

    Log::Instance().Initialize(eLogLevel::eDebug, eColorMode::eMultiMode);
    Log::Instance().Print(eLogLevel::eInfo, "> I am child %d of %d", getpid(), getppid());

    std::string port = argv[1];
    std::string workerID = argv[2];

    uint16_t id = atoll(workerID.c_str());

    int sockfd, sockServFd;
    struct addrinfo hints, *servinfo2, *servinfo;
    int ret;

    // Connect to OFServer

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((ret = getaddrinfo("0.0.0.0", "6699", &hints, &servinfo2)) != 0) {
        Log::Instance().Print(eLogLevel::eError, "%s", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    if ((sockServFd = socket(servinfo2->ai_family, servinfo2->ai_socktype, servinfo2->ai_protocol)) == -1) {
        perror("client: socket");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: socket", id);
        exit(EXIT_FAILURE);
    }

    Log::Instance().Print(eLogLevel::eDebug, "[%u] Worker: CONNECT...", id);
    if (connect(sockServFd, servinfo2->ai_addr, servinfo2->ai_addrlen) == -1) {
        close(sockServFd);
        perror("client: connect");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: connect", id);
        exit(EXIT_FAILURE);
    }

    char HelloMsg[] = "Hello World";
    int sz = send(sockServFd, HelloMsg, sizeof(HelloMsg), 0);
    Log::Instance().Print(eLogLevel::eInfo, "[%u] sz:%d", id, sz);

    // Connect MainProc

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((ret = getaddrinfo("0.0.0.0", port.c_str(), &hints, &servinfo)) != 0) {
        Log::Instance().Print(eLogLevel::eError, "%s", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("client: socket");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: socket", id);
        exit(EXIT_FAILURE);
    }

    Log::Instance().Print(eLogLevel::eDebug, "[%u] Worker: CONNECT...", id);
    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sockfd);
        perror("client: connect");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: connect", id);
        exit(EXIT_FAILURE);
    }

    Log::Instance().Print(eLogLevel::eInfo, "[%u] Worker: OK", id);

    uint16_t s_id = 2;
    char buffer[4096] = {0};
    std::map<uint16_t, int> ConnectionSession;
    ConnectionSession[0] = sockfd;
    
    int efd = epoll_create(1024);
    struct epoll_event ev, *events;

    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = ConnectionSession[0];
    if (epoll_ctl(efd, EPOLL_CTL_ADD, ConnectionSession[0], &ev) < 0) {
        Log::Instance().Print(eLogLevel::eError, "[%u] client: epoll_ctl", id);
        exit(EXIT_FAILURE);
    }

    while (true) {
        uint16_t nfds = epoll_wait(efd, events, 1024, -1);

        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == ConnectionSession[0]) {
                int numberBytes = recv(ConnectionSession[0], buffer, 4096, 0);

                int newSessionFd = atoi(buffer);
                memset(buffer, 0, sizeof(buffer));
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = newSessionFd;
                if (epoll_ctl(efd, EPOLL_CTL_ADD, newSessionFd, &ev) < 0) {
                    Log::Instance().Print(eLogLevel::eError, "[%u] client: epoll_ctl", id);
                    exit(EXIT_FAILURE);
                }
                Log::Instance().Print(eLogLevel::eInfo, "[%u] New Session '%u': '%d'", id, s_id, newSessionFd);
                ConnectionSession[s_id] = newSessionFd;
                ++s_id;
            }
        else
            Log::Instance().Print(eLogLevel::eInfo, "Proc Switch");
        }
    }

    return 0;
}