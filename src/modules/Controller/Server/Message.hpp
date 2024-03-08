#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>

class Message {
    uint16_t m_workerId;
    uint16_t m_sessionId;
public:
    Message(uint16_t _workerId, uint16_t _sessionId, std::string _msg);
    Message(std::string _msg);
    Message(Message& _message);
    Message();

    uint16_t GetWorker();
    uint16_t GetSession();
};


#endif  // __MESSAGE_HPP__