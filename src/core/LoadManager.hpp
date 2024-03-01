#ifndef __LOADMANAGER_HPP__
#define __LOADMANAGER_HPP__

#include "ModuleBase.hpp"

#include "common/DLL/LibConnection.hpp"

#include <unordered_map>
#include <string>
#include <thread>

// TODO:
// wrap modules to namespace

enum class ModuleState {
    REGISTERED,
    INITIALIZE,
    RUN,
    SHUTDOWN,
    UNKNOWN
};

enum class LoaderState {
    INITIALIZING,
    STARTING,
    RUNNING,
    SHUTDOWNING,
    UNKNOWN
};

struct ModuleInfo {
    // TODO:
    // use smart pointer
    ModuleBase* m_module;
    ModuleState m_state;

    ModuleInfo();
    ModuleInfo(ModuleBase* _module);

    void Init();
    void Run();
};

class LoadManager {
    std::unordered_map<std::string, ModuleInfo> m_modules;
    std::map<std::string, std::thread*> m_threads;

    LibConnection m_dlibs;

    LoaderState m_state;

public:
    LoadManager();

    void InitServices();
    void StartWork();
};

#endif  // __LOADMANAGER_HPP__