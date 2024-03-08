#include "Message.hpp"

#include <cstring>
#include <string>
#include <map>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/un.h>

#include "common/log/logger.hpp"

#define ADDRESS "mysocket"

#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL; /* размещается при первом вызове */

static int recv_fd(int fd);

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

    // Connect MainProc

    struct sockaddr_un sa;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("client: socket");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: socket", id);
        exit(EXIT_FAILURE);
    }

    sa.sun_family = AF_UNIX;
	strcpy(sa.sun_path, ADDRESS);
    size_t len = sizeof ( sa.sun_family) + strlen ( sa.sun_path);

    Log::Instance().Print(eLogLevel::eDebug, "[%u] Worker: CONNECT...", id);
    if (connect(sockfd, (const sockaddr *) &sa, len) == -1) {
        close(sockfd);
        perror("client: connect");
        Log::Instance().Print(eLogLevel::eError, "[%u] client: connect", id);
        exit(EXIT_FAILURE);
    }

    Log::Instance().Print(eLogLevel::eInfo, "[%u] Worker: OK", id);

    uint16_t s_id = 2;
    char buffer[4096] = {0};
    std::map<uint16_t, int> ConnectionSession;
    std::map<int, uint16_t> TransformFdtoId;
    ConnectionSession[0] = sockfd;
    ConnectionSession[1] = sockServFd;

    TransformFdtoId[sockfd] = ConnectionSession[0];
    TransformFdtoId[sockServFd] = ConnectionSession[1];

    int efd = epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event ev, *events;
    events = new struct epoll_event[1024];

    for (int i = 0; i < ConnectionSession.size(); ++i) {
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = ConnectionSession[i];
        if (epoll_ctl(efd, EPOLL_CTL_ADD, ConnectionSession[i], &ev) < 0) {
            Log::Instance().Print(eLogLevel::eError, "[%u] client: epoll_ctl", id);
            exit(EXIT_FAILURE);
        }
    }

    while (true) {
        uint16_t nfds = epoll_wait(efd, events, 1024, -1);

        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == ConnectionSession[0]) {
                int newSessionFd = recv_fd(ConnectionSession[0]);
                Log::Instance().Print(eLogLevel::eInfo, "recv: '%d'", newSessionFd);

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = newSessionFd;

                if (epoll_ctl(efd, EPOLL_CTL_ADD, newSessionFd, &ev) < 0) {
                    Log::Instance().Print(eLogLevel::eError, "[%u] client: epoll_ctl", id);
                    if (errno == EBADF) {
                        Log::Instance().Print(eLogLevel::eError, "EBADF");
                    }
                    if (errno == EPERM) {
                        Log::Instance().Print(eLogLevel::eError, "EPERM");
                    }
                    if (errno == EINVAL) {
                        Log::Instance().Print(eLogLevel::eError, "EINVAL");
                    }
                    if (errno == ENOMEM) {
                        Log::Instance().Print(eLogLevel::eError, "ENOMEM");
                    }
                    exit(EXIT_FAILURE);
                }
                Log::Instance().Print(eLogLevel::eInfo, "[%u] New Session '%u': '%d'", id, s_id, newSessionFd);
                ConnectionSession[s_id] = newSessionFd;
                TransformFdtoId[newSessionFd] = s_id;
                ++s_id;
            } else {
                Log::Instance().Print(eLogLevel::eInfo, "[%u] Proc Switch", id);
                recv(events[i].data.fd, buffer, 4096, 0);
                Log::Instance().Print(eLogLevel::eInfo, "[%u] recv: '%s'", id, buffer);
                
                uint16_t tmpId = TransformFdtoId[events[i].data.fd];
                Message msg(id, tmpId, buffer);

                send(ConnectionSession[1], (void *) &msg, sizeof(msg), 0);

                memset(buffer, 0, sizeof(buffer));
            }
        }
    }

    return 0;
}

static int recv_fd(int fd) {
    int newfd, nr, status;
    char *ptr;
    char buf[2];
    struct iovec iov[1];
    struct msghdr msg;
    status = -1;

    for ( ; ; ) {
        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;

        if (cmptr == NULL && (cmptr = (cmsghdr *) malloc(CONTROLLEN)) == NULL)
            return(-1);
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN;

        if ((nr = recvmsg(fd, &msg, 0)) < 0) {
            printf("ошибка вызова функции recvmsg");
        } else if (nr == 0) {
            printf("соединение закрыто сервером");
            return(-1);
        }

        /*
        * Проверить, являются ли два последних байта нулевым байтом
        * и кодом ошибки. Нулевой байт должен быть предпоследним,
        * а код ошибки - последним байтом в буфере.
        * Нулевой код ошибки означает, что мы должны принять дескриптор.
        */
        for (ptr = buf; ptr < &buf[nr]; ) {
            if (*ptr++ == 0) {
                if (ptr != &buf[nr-1])
                    printf("нарушение формата сообщения");

                status = *ptr & 0xFF; /* предотвратить расширение знакового бита */
                if (status == 0) {
                    if (msg.msg_controllen != CONTROLLEN)
                        printf("получен код 0, но отсутствует fd");
                    newfd = *(int *)CMSG_DATA(cmptr);
                } else {
                    newfd = -status;
                }
                nr -= 2;
            }
        }

        if (nr > 0)
            return(-1);

        if (status >= 0) /* доставлены заключительные данные */
            return(newfd); /* дескриптор или код ошибки */
    }
}