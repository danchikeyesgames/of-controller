#ifndef __LOADMANAGER_HPP__
#define __LOADMANAGER_HPP__

#include "ModuleBase.hpp"

#include <unordered_map>
#include <string>

// TODO:
// wrap modules to namespace

enum class ModuleState {
    REGISTERED,
    INITIALIZE,
    START,
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
};

class LoadManager {
    std::unordered_map<std::string, ModuleInfo> m_modules; 

    LoaderState m_state;

public:
    LoadManager();

    void InitServices();
    void StartWork();
};

#endif  // __LOADMANAGER_HPP__