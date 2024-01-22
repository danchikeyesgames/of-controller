#ifndef _COLORSCHEME_HPP_
#define _COLORSCHEME_HPP_

#include <cstddef>
#include <cstdint>

#include <map>
#include <string>

#define cMaxEscapedStr 30

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
    TermColor();
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
    
    static StandartColorScheme* CreateStandartColorScheme();
};

class MultiColorScheme : public ColorSchemeBase {

    public:

    MultiColorScheme(eColorMode);

    static MultiColorScheme* CreateMultiColorScheme();
};

class UserColorScheme : public ColorSchemeBase {

    public:

    UserColorScheme(eColorMode);

    static UserColorScheme* CreateUserColorScheme();
};

bool InitialColorSchemes();
const ColorSchemeBase* GetColorScheme(eColorMode _colorMode);



#endif  // _COLORSCHEME_HPP_