#include "LibConnection.hpp"

void LibConnection::Initialize() {
    DynamicLibrary controller("controller");

    m_libRegistered.push_back(controller);
}