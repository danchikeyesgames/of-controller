#ifndef _LOG_LOGGER_HPP_
#define _LOG_LOGGER_HPP_

#include "colorscheme.hpp"

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
        ColorSchemeBase* m_colorScheme;
    protected:
        Log(eLogLevel);
    public:
        static Log& Instance();
        bool SetColorScheme(eColorMode _colorMode);
};


#endif  // _LOG_LOGGER_HPP_