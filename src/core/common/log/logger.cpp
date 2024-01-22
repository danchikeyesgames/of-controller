#include "logger.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

const uint16_t cMaxPrintSymbols = 120;
const char* cPrintedOutputStyle = "%-10s : %s";
const size_t cLengthPrintedOutputStyle = 13;
constexpr size_t cLengthInforamtionMessage = cMaxPrintSymbols - cLengthPrintedOutputStyle;

Log* Log::m_instance = nullptr;

Log::Log()
{}

bool Log::InstanceExist() noexcept
{
    return m_instance ? true : false;
}

void Log::NewAllocateMemory() noexcept
{
    try
    {
        m_instance = CreateLog();
    } 
    catch(std::bad_alloc& bad)
    {
        std::printf("Failed to allocate memory: %s\n", bad.what());
        std::exit(EXIT_FAILURE);
    }
}

Log* Log::CreateLog() throw()
{
    return new Log();
}

Log& Log::Instance() noexcept
{
    if (!InstanceExist())
    {
        NewAllocateMemory();
    }

    return *m_instance;
}

bool Log::Initialize(eLogLevel _logLevel, eColorMode _colorMode) noexcept
{
    std::printf("Logger init\n");

    if (!InitialColorSchemes())
    {
        return false;
    }

    m_logLevel    = _logLevel;
    m_colorScheme = (ColorSchemeBase *) GetColorScheme(_colorMode);

    m_logLevelHeaderMap[eLogLevel::eDebug] = "DEBUG";
    m_logLevelHeaderMap[eLogLevel::eInfo] = "INFO";
    m_logLevelHeaderMap[eLogLevel::eWarning] = "WARNING";
    m_logLevelHeaderMap[eLogLevel::eError] = "ERROR";
    m_logLevelHeaderMap[eLogLevel::eFail] = "FAIL";

    m_logLevelColorMap[eLogLevel::eDebug] = eLogColor::eDebugColor;
    m_logLevelColorMap[eLogLevel::eInfo] = eLogColor::eInfoColor;
    m_logLevelColorMap[eLogLevel::eWarning] = eLogColor::eWarningColor;
    m_logLevelColorMap[eLogLevel::eError] = eLogColor::eErrorColor;
    m_logLevelColorMap[eLogLevel::eFail] = eLogColor::eFailColor;

    std::printf("Logger init succsessfully\n");
    return true;
}

bool Log::Print(eLogLevel _logLevel, const char* _format, ...) noexcept
{
    if (_logLevel < m_logLevel)
        return true;

    char printBuffer[cMaxPrintSymbols] = {'\0'};
    char printFormat[cLengthInforamtionMessage] = {'\0'};

    va_list vaList;
    va_start(vaList, _format);
    std::vsnprintf((char *) &printFormat, cLengthInforamtionMessage, _format, vaList);
    va_end(vaList);

    std::string logLevelStr = m_logLevelHeaderMap[_logLevel];
    std::snprintf((char *) &printBuffer, cMaxPrintSymbols, cPrintedOutputStyle, logLevelStr.c_str(), printFormat);

    eLogColor logColor = m_logLevelColorMap[_logLevel];
    std::string text = printBuffer;
    std::string coloredText = m_colorScheme->ColoredText(text, logColor);

    printf("%s\n", coloredText.c_str());
    return true;
}