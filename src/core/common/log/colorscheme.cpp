#include "colorscheme.hpp"

#include "unix_escaped_seq.hpp"

#include <cstdio>
#include <cstring>

const uint16_t cMaxEscapedStr = 30;

static const ColorSchemeBase* sc_colorModes[(size_t) eColorMode::eMaxColorMode] = {nullptr};

bool InitialColorSchemes()
{
    StandartColorScheme* standartColor = nullptr;
    MultiColorScheme* multiColor = nullptr;
    UserColorScheme* userColor = nullptr;

    try
    {
        standartColor   = new StandartColorScheme(eColorMode::eStandartMode);
        multiColor      = new MultiColorScheme(eColorMode::eMultiMode);
        userColor       = new UserColorScheme(eColorMode::eUserMode);
    }
    catch(std::bad_alloc& bad)
    {
        std::printf("Failed to allocate memory: %s\n", bad.what());
        return false;
    }

    if (standartColor->RegisterColorScheme() && multiColor->RegisterColorScheme() && userColor->RegisterColorScheme())
    {
        printf("Color schemes registered succssesfully\n");
        return true;
    }

    printf("Failed to register color schemes\n");
    return false;
}

TermColor::TermColor(const char* _colorStr)
{
    std::memcpy(color, _colorStr, cMaxEscapedStr);
}

const ColorSchemeBase* GetColorScheme(eColorMode _colorMode)
{
    return sc_colorModes[(size_t) _colorMode];
}

ColorSchemeBase::ColorSchemeBase(eColorMode _colorMode) : m_colorMode(_colorMode)
{}

bool ColorSchemeBase::RegisterColorScheme()
{
    if (sc_colorModes[(size_t) m_colorMode] != nullptr)
    {
        return false;
    }

    sc_colorModes[(size_t) m_colorMode] = this;
    return true;
}

std::string ColorSchemeBase::ColoredText(const std::string& _text, eLogColor _logColor)
{
    TermColor& termColor = m_loggerColorScheme[_logColor];

    std::string coloredBuffer;
    std::string colorTerm = termColor.color;

    coloredBuffer = colorTerm + _text;
    return coloredBuffer;
}

StandartColorScheme::StandartColorScheme(eColorMode _colorMode) : ColorSchemeBase(_colorMode)
{
    m_loggerColorScheme[eLogColor::eDebugColor]     = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eInfoColor]      = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eWarningColor]   = TermColor(PURPLE);
    m_loggerColorScheme[eLogColor::eErrorColor]     = TermColor(RED);
    m_loggerColorScheme[eLogColor::eFailColor]      = TermColor(RED);
}

MultiColorScheme::MultiColorScheme(eColorMode _colorMode) : ColorSchemeBase(_colorMode)
{
    m_loggerColorScheme[eLogColor::eDebugColor]     = TermColor(DARK_GREEN);
    m_loggerColorScheme[eLogColor::eInfoColor]      = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eWarningColor]   = TermColor(PURPLE);
    m_loggerColorScheme[eLogColor::eErrorColor]     = TermColor(DARK_RED);
    m_loggerColorScheme[eLogColor::eFailColor]      = TermColor(YELLOW);
}

UserColorScheme::UserColorScheme(eColorMode _colorMode) : ColorSchemeBase(_colorMode)
{
    m_loggerColorScheme[eLogColor::eDebugColor]     = TermColor(DARK_GREEN);
    m_loggerColorScheme[eLogColor::eInfoColor]      = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eWarningColor]   = TermColor(PURPLE);
    m_loggerColorScheme[eLogColor::eErrorColor]     = TermColor(DARK_RED);
    m_loggerColorScheme[eLogColor::eFailColor]      = TermColor(YELLOW);
}