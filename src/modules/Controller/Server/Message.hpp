#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>
#include <vector>

class Message {
    uint16_t m_workerId;
    uint16_t m_sessionId;
    size_t m_length;
    std::vector<int> m_session;
public:
    Message(uint16_t _workerId, uint16_t _sessionId, size_t _length);
    Message(std::string _msg);
    Message(Message& _message);
    Message();

    uint16_t GetWorker();
    uint16_t GetSession();
    void SetSession(std::vector<int> _session);
    void SendMessage(void* _struct);
};


#endif  // __MESSAGE_HPP__