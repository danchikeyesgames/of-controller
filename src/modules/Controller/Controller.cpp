#include "Controller.hpp"

#include "common/log/logger.hpp"

#include "Server/OfServer.hpp"
#include "Dispatcher.hpp"

#include <new>

struct Controller::ControllerImpl {
    OfServer* m_ofServer;
    ModuleBase* m_parentModule;
    Dispatcher m_dispatcher;

    ControllerImpl(ModuleBase* _module);
    void Run();

    static ControllerImpl*  CreateControllerImpl(ModuleBase* _module);
    static OfServer*        CreateOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread);

private:
    static ControllerImpl* NewControllerImpl(ModuleBase* _module) throw();
    static ControllerImpl* ConstructControllerImpl(ModuleBase* _module) noexcept;

    static OfServer* NewOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread) throw();
    static OfServer* ConstructOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread) noexcept;
};

Controller::ControllerImpl::ControllerImpl(ModuleBase* _module) : m_parentModule(_module) {}

struct Controller::ControllerImpl* Controller::ControllerImpl::NewControllerImpl(ModuleBase* _module) throw() {
    return new ControllerImpl(_module);
}

struct Controller::ControllerImpl* Controller::ControllerImpl::ConstructControllerImpl(ModuleBase* _module) noexcept {
    try
    {
        ControllerImpl* instance = NewControllerImpl(_module);
        return instance;
    }
    catch(std::bad_alloc& bad)
    {
        Log::Instance().Print(eLogLevel::eFail, "Failed to allocate memory: %s", bad.what());
        std::exit(EXIT_FAILURE);
    }
}

OfServer* Controller::ControllerImpl::NewOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread) throw() {
    return new OfServer(_port, _nthread, _ipAddr);
}

OfServer* Controller::ControllerImpl::ConstructOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread) noexcept {
    try
    {
        OfServer* instance = NewOfServer(_ipAddr, _port, _nthread);
        return instance;
    }
    catch(std::bad_alloc& bad)
    {
        Log::Instance().Print(eLogLevel::eFail, "Failed to allocate memory: %s", bad.what());
        std::exit(EXIT_FAILURE);
    }
}

struct Controller::ControllerImpl* Controller::ControllerImpl::CreateControllerImpl(ModuleBase* _module) {
    return ConstructControllerImpl(_module);
}

OfServer* Controller::ControllerImpl::CreateOfServer(const std::string& _ipAddr, uint16_t _port, uint16_t _nthread) {
    return ConstructOfServer(_ipAddr, _port, _nthread);
}

void Controller::ControllerImpl::Run() {
    Log::Instance().Print(eLogLevel::eInfo, "Dispatcher Start");
    m_dispatcher.Start();

    Log::Instance().Print(eLogLevel::eInfo, "Module Controller: Start OFServer");
    m_ofServer->StartServer();

    Log::Instance().Print(eLogLevel::eInfo, "Module Controller: AsyncEvent");
    m_ofServer->AsyncEvent(m_dispatcher);
}



Controller::Controller() : ModuleBase("controller") {
    Log::Instance().Print(eLogLevel::eInfo, "Constructor");
    m_controllerImpl = ControllerImpl::CreateControllerImpl(this);
}

void Controller::Init() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Init");
    m_controllerImpl->m_ofServer = ControllerImpl::CreateOfServer("0.0.0.0", 6633, 2);
}

void Controller::Start() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller Start");
    m_controllerImpl->Run();
}

void Controller::Shutdown() {
    Log::Instance().Print(eLogLevel::eInfo, "Module Controller ShutDown");
}

static volatile Controller sv_instance;
