#include "OfServer.hpp"

#include "common/log/logger.hpp"

#include "Message.hpp"
#include "../OFMessage.hpp"
#include "../Dispatcher.hpp"

#include <string>

#include <cstring>

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define PATH_MAINPROC "/home/danchik/Desktop/rep/of-controller/src/modules/Controller/Server/MainProc.elf"

OfServer::OfServer(uint16_t _port, uint16_t _nthreads, std::string _ipv4) : m_port(_port), m_nthreads(_nthreads), m_ipv4(_ipv4), m_sessions(_nthreads) {}

void OfServer::StartServer() {
    pid_t pid = fork();

    if (pid == -1) {
        Log::Instance().Print(eLogLevel::eError, "failed call fork()");
        return;
    } else if (pid > 0) {
    } else {
        Log::Instance().Print(eLogLevel::eDebug, "I am child %d of %d", getpid(), getppid());
        if (execl(PATH_MAINPROC, PATH_MAINPROC, "6633", NULL) == -1) {
            Log::Instance().Print(eLogLevel::eError, "failed execl():");
            
            if (errno == E2BIG) {
                Log::Instance().Print(eLogLevel::eError, "E2BIG");
            }

            if (errno == EACCES) {
                Log::Instance().Print(eLogLevel::eError, "EACCES");
            }

            if (errno == EMFILE) {
                Log::Instance().Print(eLogLevel::eError, "EMFILE");
            }

            if (errno == ENOENT) {
                Log::Instance().Print(eLogLevel::eError, "ENOENT");
            }

            if (errno == ENOEXEC) {
                Log::Instance().Print(eLogLevel::eError, "ENOEXEC");
            }

            if (errno == ENOMEM) {
                Log::Instance().Print(eLogLevel::eError, "ENOMEM");
            }
            exit(EXIT_FAILURE);
        }
    }

    Log::Instance().Print(eLogLevel::eDebug, "I am main Server %d of %d", getpid(), getppid());
    // int status;
    // waitpid(pid, &status, 0);

    // if (WIFEXITED(status)) {
    //     printf("P> Exit code = %d\n", WEXITSTATUS(status));
    // }

    int socketServerfd;
    struct addrinfo hints, *servinfo;
    
    int ret;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((ret = getaddrinfo(NULL, "6699", &hints, &servinfo)) != 0) {
        Log::Instance().Print(eLogLevel::eError, "%s", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    if ((socketServerfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("[Controller] server: socket");
        Log::Instance().Print(eLogLevel::eError, "[Controller] server: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketServerfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(socketServerfd);
        Log::Instance().Print(eLogLevel::eError, "[Controller] server: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(socketServerfd, 10) == -1) {
        close(socketServerfd);
        Log::Instance().Print(eLogLevel::eError, "[Controller] server: listen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m_nthreads; ++i) {
        int newfd = accept(socketServerfd, NULL, 0);
        m_sessions[i] = newfd;
        m_idMap[newfd] = i;
        Log::Instance().Print(eLogLevel::eDebug, "[Controller] ACCEPT");
    }
}

void OfServer::AsyncEvent(Dispatcher& _dispatcher) {
    int efd = epoll_create(1024);
    if (efd < 0) {
        Log::Instance().Print(eLogLevel::eError, "epoll_create");
        if (errno == ENOMEM) {
            Log::Instance().Print(eLogLevel::eError, "ENOMEM");
        }
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev, *events;
    events = new struct epoll_event[1024];

    for (int i = 0; i < m_nthreads; ++i) {
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = m_sessions[i];
        if (epoll_ctl(efd, EPOLL_CTL_ADD, m_sessions[i], &ev) < 0) {
            Log::Instance().Print(eLogLevel::eError, "[Controller] client: epoll_ctl");
            perror("::");
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
    }

    char buffer[4096] = {0};
    while (true) {
        Log::Instance().Print(eLogLevel::eInfo, "epoll_wait:");
        int32_t nfds = epoll_wait(efd, events, 1024, -1);
        if (nfds < 0) {
            Log::Instance().Print(eLogLevel::eError, "[Controller] client: epoll_wait");
            if (errno == EBADF) {
                Log::Instance().Print(eLogLevel::eError, "EBADF");
            }
            if (errno == EINVAL) {
                Log::Instance().Print(eLogLevel::eError, "EINVAL");
            }
            if (errno == EFAULT) {
                Log::Instance().Print(eLogLevel::eError, "EFAULT");
            }

            exit(EXIT_FAILURE);
        }

        Log::Instance().Print(eLogLevel::eInfo, "Activate epoll signal: %i", nfds);
        for (int i = 0; i < nfds; ++i) {
            //int numberBytes = recv(events[i].data.fd, buffer, 4096, 0);
            Log::Instance().Print(eLogLevel::eInfo, "recv messages %u", events[i].events);
            if (events[i].events == EPOLLIN) {
                Log::Instance().Print(eLogLevel::eInfo, "EPOLLIN");
                Message msg;
                void* buf_ = malloc(sizeof(struct ofp_header));
                int numberBytes = recv(events[i].data.fd, (void *) &msg, sizeof(msg), 0);
                numberBytes = recv(events[i].data.fd, (void *) buf_, sizeof(struct ofp_header), 0);

                Log::Instance().Print(eLogLevel::eDebug, "msg sz recv: [%d]", numberBytes);

                if (m_idMap.find(events[i].data.fd) == m_idMap.end()) {
                    Log::Instance().Print(eLogLevel::eInfo, "unregistered id and fd");
                    exit(EXIT_FAILURE);
                }

                ofp_header* header = (ofp_header *)buf_;

                Log::Instance().Print(eLogLevel::eDebug, "msg: [%u] [%u]", header->type, header->type);

                if (header->type == OFPT_HELLO) {
                    Log::Instance().Print(eLogLevel::eDebug, "msg: Hello");
                } else if (header->type == OFPT_ECHO_REQUEST) {
                    Log::Instance().Print(eLogLevel::eDebug, "msg: echo");
                    header->type = OFPT_ECHO_REPLY;
                }

                msg.SetSession(m_sessions);

                Command* handler = new EchoCommandHandler(msg, buf_);
                _dispatcher.AddCommand(handler);

                uint16_t tmpId = m_idMap[events[i].data.fd];
                Log::Instance().Print(eLogLevel::eInfo, "[%u]", tmpId);


                Log::Instance().Print(eLogLevel::eInfo, "[%u:%u]", msg.GetWorker(), msg.GetSession());
            }
            if (events[i].events == EPOLLOUT) {
                Log::Instance().Print(eLogLevel::eInfo, "EPOLLOUT");
            }
            if (events[i].events == EPOLLPRI) {
                Log::Instance().Print(eLogLevel::eInfo, "EPOLLPRI");
            }
            if (events[i].events == EPOLLERR) {
                Log::Instance().Print(eLogLevel::eInfo, "EPOLLERR");
            }
            if (events[i].events == EPOLLERR) {
                Log::Instance().Print(eLogLevel::eInfo, "EPOLLERR");
            }

            //Log::Instance().Print(eLogLevel::eInfo, "[%i] %s", events[i].data.fd, buffer);
            memset(buffer, 0, sizeof(buffer));
        }
    }
}