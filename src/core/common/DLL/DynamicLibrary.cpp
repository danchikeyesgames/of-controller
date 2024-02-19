#include "DynamicLibrary.hpp"

#ifndef _WIN32
#include "linux/unix_dynamic_lib.hpp"
#endif  // _WIN32

DynamicLibrary::DynamicLibrary(std::string _name) : m_name(_name) {
    m_path = m_name + ".so";
    m_LIB_so = CreateDynamicLibrary(m_name);
}

DynamicLibrary::~DynamicLibrary() {
    DestroyDynamicLibrary(m_LIB_so);
}