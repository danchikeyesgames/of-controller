#ifndef __OF_SERVER__
#define __OF_SERVER__

#include <string>

class OfServer {
    uint16_t m_port;
    uint16_t m_nthreads;
    std::string m_ipv4;

public:
    OfServer(uint16_t _port, uint16_t _nthreads, std::string _ipv4);
    void StartServer();
};



#endif  // __OF_SERVER__