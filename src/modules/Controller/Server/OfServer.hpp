#ifndef __OF_SERVER__
#define __OF_SERVER__

#include <string>
#include <vector>
#include <map>

class OfServer {
    uint16_t m_port;
    uint16_t m_nthreads;
    std::string m_ipv4;
    std::vector<int> m_sessions;
    std::map<int, uint16_t> m_idMap;

public:
    OfServer(uint16_t _port, uint16_t _nthreads, std::string _ipv4);
    void StartServer();
    void AsyncEvent();
};



#endif  // __OF_SERVER__