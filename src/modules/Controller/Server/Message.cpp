#include "Message.hpp"

#include "common/log/logger.hpp"

#include <sys/socket.h>

#define MAX_LENTH_PACKET 4096

Message::Message(uint16_t _workerId, uint16_t _sessionId, size_t _length) : m_workerId(_workerId), m_sessionId(_sessionId), m_length(_length) {}

Message::Message(std::string _msg) : m_workerId(0), m_sessionId(0) {}

Message::Message(Message& _message) : m_workerId(_message.m_workerId), m_sessionId(_message.m_sessionId), m_session(_message.m_session) {}

Message::Message() {}

uint16_t Message::GetWorker() {
    return m_workerId;
}

uint16_t Message::GetSession() {
    return m_sessionId;
}

void Message::SetSession(std::vector<int> _session) {
    m_session = _session;
    Log::Instance().Print(eLogLevel::eDebug, "sz m_session %u", m_session.size());
}

void Message::SendMessage(void* _struct) {
    Message msg(m_workerId, m_sessionId, m_length);

    Log::Instance().Print(eLogLevel::eDebug, "da: %u-%u", m_workerId, m_sessionId);
    Log::Instance().Print(eLogLevel::eDebug, "da: %d", m_session[m_workerId]);

    send(m_session[m_workerId], &msg, sizeof(msg), 0);
    send(m_session[m_workerId], _struct, 8, 0);

    free(_struct);
}