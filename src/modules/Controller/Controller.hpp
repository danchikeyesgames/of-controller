#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "api/Module.hpp"

class Controller : ModuleBase {
    std::string m_name = "controller";
public:
    void Init() override;
    void Start() override;
    void Shutdown() override;

    Controller();
};


#endif  // __CONTROLLER_HPP__