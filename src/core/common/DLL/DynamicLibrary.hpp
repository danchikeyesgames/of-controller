#ifndef __DYNAMICLIBRARY_HPP__
#define __DYNAMICLIBRARY_HPP__

#include <string>

class DynamicLibrary {
    std::string m_name;
    std::string m_path;
    void* m_LIB_so;

public:
    DynamicLibrary(std::string _name);
    ~DynamicLibrary();
};


#endif  // __DYNAMICLIBRARY_HPP__