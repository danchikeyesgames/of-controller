#include "LibConnection.hpp"

#include "common/log/logger.hpp"

void LibConnection::Initialize() {
    DynamicLibrary controller("controller");

    if (controller.IsOpenned())
        m_libRegistered.push_back(controller);
}