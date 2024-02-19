#ifndef __UNIX_DYNAMIC_LIB_HPP__
#define __UNIX_DYNAMIC_LIB_HPP__

#include <string>

void* CreateDynamicLibrary(std::string _name);
void  DestroyDynamicLibrary(void* _lib);

#endif  // __UNIX_DYNAMIC_LIB_HPP__