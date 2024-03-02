#include "LoadManager.hpp"

#include "common/log/logger.hpp"

#include <functional>

ModuleInfo::ModuleInfo() : m_module(nullptr), m_state(ModuleState::UNKNOWN) {}

ModuleInfo::ModuleInfo(ModuleBase* _module) : m_module(_module), m_state(ModuleState::REGISTERED) {}

void ModuleInfo::Init() {
    Log::Instance().Print(eLogLevel::eDebug, "deb");
    Log::Instance().Print(eLogLevel::eDebug, "%0#x", m_module);
    m_module->Init();
    m_state = ModuleState::INITIALIZE;
}

void ModuleInfo::Run() {
    m_module->Start();
    m_state = ModuleState::RUN;
}


LoadManager::LoadManager() : m_state(LoaderState::UNKNOWN) {}

void LoadManager::InitServices() {
    if (m_state != LoaderState::UNKNOWN) {
        Log::Instance().Print(eLogLevel::eError, "failed init services");
        return;
    }

    m_state = LoaderState::INITIALIZING;
    m_dlibs.Initialize();

    auto moduleIter = ModuleRegistry::GetBeginIter();
    auto endIter    = ModuleRegistry::GetEndIter();

    for (; moduleIter != endIter; ++moduleIter) {
        if (m_modules.find(moduleIter->first) != m_modules.end()) {
            Log::Instance().Print(eLogLevel::eWarning, "module '%s' has yet registered", moduleIter->first.c_str());
            continue;
        }

        Log::Instance().Print(eLogLevel::eDebug, "start");
        ModuleInfo moduleInfo(moduleIter->second);
        Log::Instance().Print(eLogLevel::eDebug, "1 %s", moduleIter->first.c_str());
        moduleInfo.Init();
        Log::Instance().Print(eLogLevel::eDebug, "2");
        Log::Instance().Print(eLogLevel::eInfo, "init module '%s'", moduleIter->first.c_str());
        m_modules[moduleIter->first] = moduleInfo;
    }
}

void LoadManager::StartWork() {
    if (m_state != LoaderState::INITIALIZING) {
        Log::Instance().Print(eLogLevel::eError, "failed starting services");
        return;
    }

    m_state = LoaderState::STARTING;

    auto moduleIter = m_modules.begin();
    auto endIter    = m_modules.end();
    
    for (; moduleIter != endIter; ++moduleIter) {
        if (m_modules.find(moduleIter->first) == m_modules.end()) {
            Log::Instance().Print(eLogLevel::eWarning, "module '%s' hasn't found", moduleIter->first.c_str());
            continue;
        }

        ModuleInfo moduleInfo = m_modules[moduleIter->first];
        std::function<void(void)> f_mainThread = std::bind(&ModuleInfo::Run, &moduleInfo);
        std::thread* th = new std::thread(f_mainThread);
        m_threads[moduleIter->first] = th;
        Log::Instance().Print(eLogLevel::eInfo, "run module '%s'", moduleIter->first.c_str());
    }

    m_state = LoaderState::RUNNING;
    Log::Instance().Print(eLogLevel::eInfo, "LoadManager change state to RUNNING");
}