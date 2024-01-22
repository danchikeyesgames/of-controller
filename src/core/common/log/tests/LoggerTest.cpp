#include <iostream>

#include "common/log/logger.hpp"

int main()
{
    if (!Log::Instance().Initialize(eLogLevel::eDebug, eColorMode::eMultiMode))
    {
        std::printf("failed\n");
    }

    Log::Instance().Print(eLogLevel::eDebug, "debug text");
    Log::Instance().Print(eLogLevel::eInfo, "info text");
    Log::Instance().Print(eLogLevel::eWarning, "warning text");
    Log::Instance().Print(eLogLevel::eError, "error text");
    Log::Instance().Print(eLogLevel::eFail, "fail text");

    return 0;
}