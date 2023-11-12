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
    ePartialMode,       // three color (red, green and standart)
    eUserMode,
    eMaxColorMode
};

class ColorSchemeBase {
    private:
        eColorMode m_colorMode;
    protected:
        std::map<std::string, ColorTerm> m_colorMap;
    public:
        ColorSchemeBase(eColorMode _colorMode);
        bool RegisterColorScheme();
        const eColorMode& GetColorMode();
        virtual bool StringEscaped(std::string &, const std::string &);
};

bool InitialColorScheme();
ColorSchemeBase* GetColorScheme(eColorMode _colorMode);

class StandartScheme : public ColorSchemeBase {
    public:
        StandartScheme();
        bool StringEscaped(std::string &, const std::string &) override;
};

class MultiScheme : public ColorSchemeBase {
    public:
        MultiScheme();
        bool StringEscaped(std::string &, const std::string &) override;
};

class PartialScheme : public ColorSchemeBase {
    public:
        PartialScheme();
        bool StringEscaped(std::string &, const std::string &) override;
};

class UserScheme : public ColorSchemeBase {
    public:
        UserScheme();
        bool StringEscaped(std::string &, const std::string &) override;
};

#endif  // _LOG_COLORSCHEME_HPP_