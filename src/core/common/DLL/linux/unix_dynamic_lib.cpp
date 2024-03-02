#include "unix_dynamic_lib.hpp"

#include "common/log/logger.hpp"

#include <dlfcn.h>

void* CreateDynamicLibrary(std::string _name) {
    std::string pathOfLib = _name + ".so";
    void* lib_ptr = nullptr;
    
    lib_ptr = dlopen(pathOfLib.c_str(), RTLD_LAZY);

    if (dlerror() != NULL) {
        Log::Instance().Print(eLogLevel::eWarning, "failed load '%s' library", pathOfLib.c_str());
        lib_ptr = nullptr;
    }

    return lib_ptr;
}

void DestroyDynamicLibrary(void* _lib) {
    if (_lib != nullptr) dlclose(_lib);
}