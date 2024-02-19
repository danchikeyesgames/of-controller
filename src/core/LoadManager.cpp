#include "LoadManager.hpp"

#include "common/log/logger.hpp"

ModuleInfo::ModuleInfo() : m_module(nullptr), m_state(ModuleState::UNKNOWN) {}

ModuleInfo::ModuleInfo(ModuleBase* _module) : m_module(_module), m_state(ModuleState::REGISTERED) {}

LoadManager::LoadManager() : m_state(LoaderState::UNKNOWN) {}