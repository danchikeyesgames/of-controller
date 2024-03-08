#include "Dispatcher.hpp"

#include <thread>
#include <functional>

#include "common/log/logger.hpp"

void Dispatcher::MainLoop() {
    Log::Instance().Print(eLogLevel::eWarning, "MainLoop");
    while (true) {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_cvmutex.wait(lk);

        Command* command = m_queue.front();
        command->Process();

        m_queue.pop();
    }
}

void Dispatcher::Start() {
    std::function<void(void)> f_mainThread = std::bind(&Dispatcher::MainLoop, this);

    Log::Instance().Print(eLogLevel::eWarning, "Start thread");

    m_pth = new std::thread(f_mainThread);
    Log::Instance().Print(eLogLevel::eWarning, "threads end");
}

void Dispatcher::AddCommand(Command* _cmd) {
    std::unique_lock<std::mutex> lk(m_mutex);

    m_queue.push(_cmd);

    m_cvmutex.notify_one();
}

EchoCommandHandler::EchoCommandHandler(Message _msg, void* _ofMsg) : Command() {
    msg = _msg;
    ofMsg = _ofMsg;
}

void EchoCommandHandler::Process() {
    Log::Instance().Print(eLogLevel::eWarning, "process message");
    msg.SendMessage(ofMsg);
}