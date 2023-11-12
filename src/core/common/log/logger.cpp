#include "logger.hpp"

Log::Log(eLogLevel _logLevel)  : m_logLevel(_logLevel) {
    if (InitialColorScheme() == false) {
        printf("Initial logger module failed\n");
        exit(EXIT_FAILURE);
    }

    if (SetColorScheme(eColorMode::eMultiMode) == false) {
        printf("Color scheme module failed\n");
        exit(EXIT_FAILURE);
    }
}

Log& Log::Instance() {
    static Log instance(eLogLevel::eDebug);
    
    return instance;
}

bool Log::SetColorScheme(eColorMode _colorMode) {
    m_colorScheme = GetColorScheme(_colorMode);

    return m_colorScheme == nullptr ? false : true; 
}
