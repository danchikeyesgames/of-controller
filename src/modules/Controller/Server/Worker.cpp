
#include <unistd.h>
#include <sys/wait.h>

#include "common/log/logger.hpp"

int main(int argc, char* argv[]) {

    Log::Instance().Print(eLogLevel::eDebug, "I am child %d of %d\n", getpid(), getppid());

    return 0;
}