#include "LoadManager.hpp"

#include "common/log/logger.hpp"

int main()
{
    Log::Instance().Initialize(eLogLevel::eDebug, eColorMode::eMultiMode);

    LoadManager loadManager;

    loadManager.InitServices();
    loadManager.StartWork();

    Log::Instance().Print(eLogLevel::eInfo, "end process");

    while (true) {}
    return 0;
}