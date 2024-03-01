
#pragma once

#include <string>
#include <map>

class ModuleBase {
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Shutdown() = 0;

    ModuleBase(std::string _name);
};

class ModuleRegistry {
    static std::map<std::string, ModuleBase*> s_registeredModules;
public:
    static void RegisterModule(std::string _name, ModuleBase* _module);
    static std::map<std::string, ModuleBase*>::iterator GetBeginIter();
    static std::map<std::string, ModuleBase*>::iterator GetEndIter();
};