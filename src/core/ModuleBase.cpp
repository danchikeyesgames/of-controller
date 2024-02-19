#include "ModuleBase.hpp"

ModuleBase::ModuleBase(std::string _name) {
    ModuleRegistry::RegisterModule(_name, this);
}

void ModuleRegistry::RegisterModule(std::string _name, ModuleBase* _module) {
    s_registeredModules[_name] = _module;
}