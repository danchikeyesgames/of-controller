#include "OfServer.hpp"

#include "common/log/logger.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define PATH_MAINPROC "/home/danchik/Desktop/rep/of-controller/src/modules/Controller/Server/MainProc.elf"

OfServer::OfServer(uint16_t _port, uint16_t _nthreads, std::string _ipv4) : m_port(_port), m_nthreads(_nthreads), m_ipv4(_ipv4) {}

void OfServer::StartServer() {
    pid_t pid = fork();

    if (pid == -1) {
        Log::Instance().Print(eLogLevel::eError, "failed call fork()");
        return;
    } else if (pid > 0) {
    } else {
        Log::Instance().Print(eLogLevel::eDebug, "I am child %d of %d", getpid(), getppid());
        if (execl(PATH_MAINPROC, PATH_MAINPROC, "6600", NULL) == -1) {
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

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("P> Exit code = %d\n", WEXITSTATUS(status));
    }
}