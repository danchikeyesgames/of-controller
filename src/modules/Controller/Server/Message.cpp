#include "Message.hpp"

#include "common/log/logger.hpp"

#define MAX_LENTH_PACKET 4096

Message::Message(uint16_t _workerId, uint16_t _sessionId, std::string _msg) : m_workerId(_workerId), m_sessionId(_sessionId) {}

Message::Message(std::string _msg) : m_workerId(0), m_sessionId(0) {}

Message::Message(Message& _message) : m_workerId(_message.m_workerId), m_sessionId(_message.m_sessionId) {}

Message::Message() {}

uint16_t Message::GetWorker() {
    return m_workerId;
}

uint16_t Message::GetSession() {
    return m_sessionId;
}
