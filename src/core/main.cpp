#include "LoadManager.hpp"

#include "common/log/logger.hpp"

int main()
{
    LoadManager loadManager;

    loadManager.InitServices();
    loadManager.StartWork();

    Log::Instance().Print(eLogLevel::eInfo, "end process");
    return 0;
}