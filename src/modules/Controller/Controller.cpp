#include "Controller.hpp"

#include "common/log/logger.hpp"

Controller::Controller() : ModuleBase("controller") {
    Log::Instance().Print(eLogLevel::eInfo, "Constructor");
}

void Controller::Init() {
    printf("hello mans\n");
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Init");
}

void Controller::Start() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Start");
}

void Controller::Shutdown() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller ShutDown");
}

static volatile Controller instance;
