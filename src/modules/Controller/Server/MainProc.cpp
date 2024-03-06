#include <cstring>
#include <string>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>

#include "common/log/logger.hpp"

#define PATH_WORKER "/home/danchik/Desktop/rep/of-controller/src/modules/Controller/Server/Worker.elf"

int main(int argc, char* argv[]) {
    std::string programName;
    std::string portLocalNet;
    std::string threadCount;;
    uint16_t port = 0;
    uint16_t threads = 0;

    Log::Instance().Initialize(eLogLevel::eDebug, eColorMode::eMultiMode);

    Log::Instance().Print(eLogLevel::eDebug, "MainProc");

    if (argc == 2) {
        programName = argv[0];
        portLocalNet = argv[1];

        threads = 2;
        port = atoll(portLocalNet.c_str());
        if (port == 0) return 1;
    } else if (argc == 3) {
        programName = argv[0];
        portLocalNet = argv[1];
        threadCount = argv[2];

        threads = atoll(threadCount.c_str());
        port = atoll(portLocalNet.c_str());
    } else {
        Log::Instance().Print(eLogLevel::eError, "invalid args");
        return 1;
    }

    int socketServerfd;
    struct addrinfo hints, *servinfo;
    std::vector<int> socketClient(threads);
    int ret;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((ret = getaddrinfo(NULL, portLocalNet.c_str(), &hints, &servinfo)) != 0) {
        Log::Instance().Print(eLogLevel::eError, "%s", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    if ((socketServerfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("server: socket");
        Log::Instance().Print(eLogLevel::eError, "server: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketServerfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(socketServerfd);
        Log::Instance().Print(eLogLevel::eError, "server: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(socketServerfd, 10) == -1) {
        close(socketServerfd);
        Log::Instance().Print(eLogLevel::eError, "server: listen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < threads; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            Log::Instance().Print(eLogLevel::eError, "failed call fork()");
            return 1;
        } else if (pid > 0) {
            int newfd = accept(socketServerfd, NULL, 0);
            socketClient[i] = newfd;
            Log::Instance().Print(eLogLevel::eDebug, "MainProc: ACCEPT");
        } else {
            Log::Instance().Print(eLogLevel::eDebug, "I am child %d of %d", getpid(), getppid());
            char tmpBuffer[4096] = {0};
            snprintf(tmpBuffer, 4096, "%d", i);
            if (execl(PATH_WORKER, PATH_WORKER, portLocalNet.c_str(), tmpBuffer, NULL) == -1) {
                Log::Instance().Print(eLogLevel::eError, "failed execl()");
                return 1;
            }
        }
    }

    Log::Instance().Print(eLogLevel::eDebug, "MainProc: OK");

    int count = 0;
    char buffer[4096] = {0};

    while (true) {
        int OutFd = accept4(socketServerfd, NULL, 0, SOCK_CLOEXEC);
        snprintf(buffer, 4096, "%d", OutFd);       

        Log::Instance().Print(eLogLevel::eDebug, "%s", buffer);
        long sz = send(socketClient[count], buffer, 4096, 0);
        if (sz < 0) {
            perror("send");
        }
        Log::Instance().Print(eLogLevel::eDebug, "sz: %li", sz);
        memset(buffer, 0, sizeof(buffer));
        count = (count + 1) % threads;
    }

    return 0;
}