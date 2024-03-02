#include "ModuleBase.hpp"

std::map<std::string, ModuleBase*> ModuleRegistry::s_registeredModules;

ModuleBase::ModuleBase(std::string _name) {
    ModuleRegistry::RegisterModule(_name, this);
}

void ModuleRegistry::RegisterModule(std::string _name, ModuleBase* _module) {
    s_registeredModules[_name] = _module;
}

std::map<std::string, ModuleBase*>::iterator ModuleRegistry::GetBeginIter() {
   std::map<std::string, ModuleBase*>::iterator iter = s_registeredModules.begin();
   return iter;
}

std::map<std::string, ModuleBase*>::iterator ModuleRegistry::GetEndIter() {
   std::map<std::string, ModuleBase*>::iterator iter = s_registeredModules.begin();
   return iter;
}