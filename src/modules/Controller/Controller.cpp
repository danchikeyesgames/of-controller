#include "Controller.hpp"

#include "common/log/logger.hpp"

Controller::Controller() : ModuleBase(m_name) {}

void Controller::Init() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Init");
}

void Controller::Start() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Start");
}

void Controller::Shutdown() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller ShutDown");
}

static Controller instance;