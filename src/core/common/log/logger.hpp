#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include "colorscheme.hpp"

#include <new>
#include <string>

enum class eLogLevel {
    eDebug = 0,
    eInfo,
    eWarning,
    eError,
    eFail
};

class Log {

    eLogLevel m_logLevel;
    ColorSchemeBase* m_colorScheme;
    std::map<eLogLevel, std::string> m_logLevelHeaderMap;
    std::map<eLogLevel, eLogColor> m_logLevelColorMap;

    static Log* m_instance;

    protected:

    Log();

    private:

    static bool InstanceExist() noexcept;
    static void NewAllocateMemory() noexcept;
    static Log* CreateLog() throw();

    public:

    static Log& Instance() noexcept;
    
    bool Initialize(eLogLevel _logLevel, eColorMode _colorMode) noexcept;
    bool Print(eLogLevel _logLevel, const char* _format, ...) noexcept;
};



#endif  // _LOGGER_HPP_