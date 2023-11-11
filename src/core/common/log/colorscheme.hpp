#ifndef _LOG_COLORSCHEME_HPP_
#define _LOG_COLORSCHEME_HPP_

#include <string>
#include <map>


#define COLOR_MAX_SYM 20

struct ColorTerm {
    char color[COLOR_MAX_SYM];
};

enum eColorMode {
    eStandartMode = 0,
    eMultiMode,
    ePartialMode,
    eUserMode,
    eMaxColorMode
};

class ColorSchemeBase {
    private:
        std::map<std::string, ColorTerm> m_colorMap;
        eColorMode m_colorMode;
    protected:

    public:
        ColorSchemeBase(eColorMode _colorMode);
        bool RegisterColorScheme();
        virtual bool StringEscaped(std::string &, const std::string &);
};

#endif  // _LOG_COLORSCHEME_HPP_