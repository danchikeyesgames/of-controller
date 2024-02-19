
#pragma once

#include <string>
#include <map>

class ModuleBase {
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
public:
    ModuleBase(std::string _name);
};

class ModuleRegistry {
    static std::map<std::string, ModuleBase*> s_registeredModules;
public:
    static void RegisterModule(std::string _name, ModuleBase* _module);
};