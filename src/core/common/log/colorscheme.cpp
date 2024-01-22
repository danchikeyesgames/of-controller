#include "colorscheme.hpp"

#include "linux/unix_escaped_seq.hpp"

#include <cstdio>
#include <cstring>

static const ColorSchemeBase* sc_colorModes[(size_t) eColorMode::eMaxColorMode] = {nullptr};

bool InitialColorSchemes()
{
    if (CheckTermSupport256())
    {
        std::printf("Terminal supported 256color\n");
    }

    StandartColorScheme* standartColor = nullptr;
    MultiColorScheme* multiColor = nullptr;
    UserColorScheme* userColor = nullptr;

    try
    {
        standartColor   = StandartColorScheme::CreateStandartColorScheme();
        multiColor      = MultiColorScheme::CreateMultiColorScheme();
        userColor       = UserColorScheme::CreateUserColorScheme();
    }
    catch(std::bad_alloc& bad)
    {
        std::printf("Failed to allocate memory: %s\n", bad.what());
        return false;
    }

    if (standartColor->RegisterColorScheme() && multiColor->RegisterColorScheme() && userColor->RegisterColorScheme())
    {
        printf("Colorschemes registered succsessfully\n");
        return true;
    }

    printf("Failed to register color schemes\n");
    return false;
}


const ColorSchemeBase* GetColorScheme(eColorMode _colorMode)
{
    return sc_colorModes[(size_t) _colorMode];
}

TermColor::TermColor(const char* _colorStr)
{
    std::memcpy(color, _colorStr, cMaxEscapedStr);
}

TermColor::TermColor()
{}

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

StandartColorScheme* StandartColorScheme::CreateStandartColorScheme()
{
    return new StandartColorScheme(eColorMode::eStandartMode);
}

MultiColorScheme::MultiColorScheme(eColorMode _colorMode) : ColorSchemeBase(_colorMode)
{
    m_loggerColorScheme[eLogColor::eDebugColor]     = TermColor(DARK_GREEN);
    m_loggerColorScheme[eLogColor::eInfoColor]      = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eWarningColor]   = TermColor(PURPLE);
    m_loggerColorScheme[eLogColor::eErrorColor]     = TermColor(DARK_RED);
    m_loggerColorScheme[eLogColor::eFailColor]      = TermColor(YELLOW);
}

MultiColorScheme* MultiColorScheme::CreateMultiColorScheme()
{
    return new MultiColorScheme(eColorMode::eMultiMode);
}

UserColorScheme::UserColorScheme(eColorMode _colorMode) : ColorSchemeBase(_colorMode)
{
    m_loggerColorScheme[eLogColor::eDebugColor]     = TermColor(DARK_GREEN);
    m_loggerColorScheme[eLogColor::eInfoColor]      = TermColor(STANDART);
    m_loggerColorScheme[eLogColor::eWarningColor]   = TermColor(PURPLE);
    m_loggerColorScheme[eLogColor::eErrorColor]     = TermColor(DARK_RED);
    m_loggerColorScheme[eLogColor::eFailColor]      = TermColor(YELLOW);
}

UserColorScheme* UserColorScheme::CreateUserColorScheme()
{
    return new UserColorScheme(eColorMode::eUserMode);
}