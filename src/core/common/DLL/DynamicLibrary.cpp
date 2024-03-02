#include "DynamicLibrary.hpp"

#ifndef _WIN32
#include "linux/unix_dynamic_lib.hpp"
#endif  // _WIN32

#include "common/log/logger.hpp"

DynamicLibrary::DynamicLibrary(std::string _name) : m_name(_name) {
    m_path = m_name + ".so";
    m_LIB_so = CreateDynamicLibrary(m_name);
}

void DynamicLibrary::DestroyLib() {
    DestroyDynamicLibrary(m_LIB_so);
}

DynamicLibrary::~DynamicLibrary() { }

bool DynamicLibrary::IsOpenned() {
    return m_LIB_so == nullptr ? false : true;
}