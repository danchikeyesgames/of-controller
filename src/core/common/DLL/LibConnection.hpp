#ifndef __LIBCONNECTION_HPP__
#define __LIBCONNECTION_HPP__

#include "DynamicLibrary.hpp"

#include <vector>

class LibConnection {
    std::vector<DynamicLibrary> m_libRegistered;

public:
    void Initialize();
};



#endif // __LIBCONNECTION_HPP__