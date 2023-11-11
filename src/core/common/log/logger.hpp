#ifndef _LOG_LOGGER_HPP_
#define _LOG_LOGGER_HPP_

#include "unixEscapeSeq.hpp"

enum eLogLevel {
    eDebug = 0,
    eInfo,
    eWarning,
    eError,
    eFail
};

class Log {
    private:
        eLogLevel  m_logLevel;
        eColorMode m_colorMode;
    protected:
        Log();
    public:
        static Log* Instance();
};


#endif  // _LOG_LOGGER_HPP_