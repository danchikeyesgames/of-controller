#include <cstring>
#include <string>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "common/log/logger.hpp"

#define PATH_WORKER "/home/danchik/Desktop/rep/of-controller/src/modules/Controller/Server/Worker.elf"
#define ADDRESS "mysocket"

#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL; /* размещается при первом вызове */

static int send_fd(int fd, int fd_to_send);

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

    // UNIX sockets
    std::vector<int> socketClient(threads);
    int i, d, len, ca_len;
	struct sockaddr_un sa, ca;



    if ((d = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("server: socket");
        Log::Instance().Print(eLogLevel::eError, "unix server: socket");
        exit(EXIT_FAILURE);
    }

    sa.sun_family = AF_UNIX;
	strcpy(sa.sun_path, ADDRESS);

    unlink(ADDRESS);
    len = sizeof (sa.sun_family) + strlen (sa.sun_path);

    if (bind(d, (const sockaddr *) &sa, len) == -1) {
        close(d);
        Log::Instance().Print(eLogLevel::eError, "unix server: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(d, 10) == -1) {
        close(d);
        Log::Instance().Print(eLogLevel::eError, "unix server: listen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < threads; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            Log::Instance().Print(eLogLevel::eError, "failed call fork()");
            return 1;
        } else if (pid > 0) {
            int newfd = accept(d, NULL, 0);
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

    // INET sockets

    int socketServerfd;
    struct addrinfo hints, *servinfo;
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

    Log::Instance().Print(eLogLevel::eDebug, "MainProc: OK");

    int count = 0;
    char buffer[4096] = {0};

    while (true) {
        int OutFd = accept4(socketServerfd, NULL, 0, SOCK_CLOEXEC);
        snprintf(buffer, 4096, "%d", OutFd);       

        Log::Instance().Print(eLogLevel::eDebug, "%s", buffer);
        long sz = send_fd(socketClient[count], OutFd);
        if (sz < 0) {
            perror("send");
        }
        Log::Instance().Print(eLogLevel::eDebug, "sz: %li", sz);
        memset(buffer, 0, sizeof(buffer));
        count = (count + 1) % threads;
    }

    return 0;
}

static int send_fd(int fd, int fd_to_send) {
    struct iovec iov[1];
    struct msghdr msg;
    char buf[2]; /* 2-байтный протокол send_fd()/recv_fd() */

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    if (fd_to_send < 0) {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send; /* ненулевое значение означает ошибку */
        if (buf[1] == 0)
        buf[1] = 1; /* протокол преобразует в -256 */
    } else {
        if (cmptr == NULL && (cmptr = (cmsghdr *) malloc(CONTROLLEN)) == NULL)
            return(-1);
        cmptr->cmsg_level = SOL_SOCKET;
        cmptr->cmsg_type = SCM_RIGHTS;
        cmptr->cmsg_len = CONTROLLEN;
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN;
        *(int *)CMSG_DATA(cmptr) = fd_to_send; /* записать дескриптор */
        buf[1] = 0; /* нулевое значение означает отсутствие ошибки */
    }

    buf[0] = 0; /* нулевой байт – флаг для recv_fd() */
    if (sendmsg(fd, &msg, 0) != 2)
        return(-1);
    return(0);
}