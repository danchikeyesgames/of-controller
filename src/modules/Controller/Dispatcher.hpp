#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include "Server/Message.hpp"
#include "OFMessage.hpp"

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

class Command {
public:
    virtual void Process() = 0;
};

class EchoCommandHandler : public Command {
    Message msg;
    void* ofMsg;
public:
    EchoCommandHandler(Message _msg, void* _ofMsg);

    void Process() override;
};

class Dispatcher {
    std::mutex m_mutex;
    std::condition_variable m_cvmutex;
    std::thread* m_pth;
    std::queue<Command*> m_queue;

public:
    void MainLoop();
    void Start();

    void AddCommand(Command* _cmd);
};



#endif  // __DISPATCHER_HPP__