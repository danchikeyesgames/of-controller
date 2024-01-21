#ifndef _COLORSCHEME_HPP_
#define _COLORSCHEME_HPP_

#include <cstddef>
#include <cstdint>

#include <map>
#include <string>

enum class eColorMode {
    eStandartMode = 0,
    eMultiMode,
    eUserMode,
    eMaxColorMode
};

enum class eLogColor {
    eDebugColor = 0,
    eInfoColor,
    eWarningColor,
    eErrorColor,
    eFailColor
};

struct TermColor {
    char color[cMaxEscapedStr];

    TermColor(const char* _colorStr);
};

class ColorSchemeBase {
    eColorMode m_colorMode;

    protected:

    std::map<eLogColor, TermColor> m_loggerColorScheme;
    
    public:

    ColorSchemeBase(eColorMode);
    bool RegisterColorScheme();
    std::string ColoredText(const std::string& _text, eLogColor _logColor);
};

class StandartColorScheme : public ColorSchemeBase {

    public:

    StandartColorScheme(eColorMode);
};

class MultiColorScheme : public ColorSchemeBase {

    public:

    MultiColorScheme(eColorMode);
};

class UserColorScheme : public ColorSchemeBase {

    public:

    UserColorScheme(eColorMode);
};

bool InitialColorSchemes();
const ColorSchemeBase* GetColorScheme(eColorMode _colorMode);



#endif  // _COLORSCHEME_HPP_