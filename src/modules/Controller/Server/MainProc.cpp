#include <cstring>
#include <string>

#include <unistd.h>
#include <sys/wait.h>

#include "common/log/logger.hpp"

#define PATH_WORKER "/home/danchik/Desktop/rep/of-controller/src/modules/Controller/Server/Worker.elf"

int main(int argc, char* argv[]) {
    std::string programName;
    std::string portLocalNet;
    std::string threadCount;;
    uint16_t port = 0;
    uint16_t threads = 0;
    
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

    for (int i = 0; i < threads; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            Log::Instance().Print(eLogLevel::eError, "failed call fork()");
            return 1;
        } else if (pid > 0) {
            continue;
        } else {
            Log::Instance().Print(eLogLevel::eError, "I am child %d of %d\n", getpid(), getppid());
            if (execl(PATH_WORKER, portLocalNet.c_str(), NULL) == -1) {
                Log::Instance().Print(eLogLevel::eError, "failed execl()");
                return 1;
            }
        }
    }


    Log::Instance().Print(eLogLevel::eDebug, "MainProc: OK");

    return 0;
}