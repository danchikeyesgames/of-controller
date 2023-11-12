#include "colorscheme.hpp"

#ifndef _WIN32
#include "unixEscapeSeq.hpp"
#endif  // _WIN32

#include <cstdlib>
#include <cstring>

ColorSchemeBase* s_colorScheme[eColorMode::eMaxColorMode] = {nullptr};

bool InitialColorScheme() {
    StandartScheme* standart = new StandartScheme;
    MultiScheme*    multi    = new MultiScheme;
    PartialScheme*  partial  = new PartialScheme;
    UserScheme*     user     = new UserScheme;

    if (standart->RegisterColorScheme() &&
        multi->RegisterColorScheme() &&
        partial->RegisterColorScheme() &&
        user->RegisterColorScheme()) {

        return true;
    }

    return false;
}

ColorSchemeBase* GetColorScheme(eColorMode _colorMode) {
    return s_colorScheme[(uint32_t) _colorMode];
}

ColorSchemeBase::ColorSchemeBase(eColorMode _colorMode) : m_colorMode(_colorMode) {}

bool ColorSchemeBase::StringEscaped(std::string& _str, const std::string& _key) {
    auto iter = m_colorMap.find(_key.c_str());
    if (iter != m_colorMap.end())
        return false;

    std::string tmpStr = iter->second.color;
    tmpStr += _str;

    _str.clear();
    _str = std::move(tmpStr);
    return true;
};

const eColorMode& ColorSchemeBase::GetColorMode() {
    return m_colorMode;
}

bool ColorSchemeBase::RegisterColorScheme() {
    if (s_colorScheme[(uint32_t) m_colorMode] != nullptr) {
        return false;
    }

    s_colorScheme[(uint32_t) m_colorMode] = this;
    return true;
}


StandartScheme::StandartScheme() : ColorSchemeBase(eColorMode::eStandartMode) {
    ColorTerm debug;
    ColorTerm info;
    ColorTerm warning;
    ColorTerm error;
    ColorTerm fail;

    strncpy(debug.color,   STANDART, COLOR_MAX_SYM);
    strncpy(info.color,    STANDART, COLOR_MAX_SYM);
    strncpy(warning.color, STANDART, COLOR_MAX_SYM);
    strncpy(error.color,   STANDART, COLOR_MAX_SYM);
    strncpy(fail.color,    STANDART, COLOR_MAX_SYM);

    m_colorMap["debug"]   = debug;
    m_colorMap["info"]    = info;
    m_colorMap["warning"] = warning;
    m_colorMap["error"]   = error;
    m_colorMap["fail"]    = fail;
}

bool StandartScheme::StringEscaped(std::string& _str, const std::string& _key) {
    return ColorSchemeBase::StringEscaped(_str, _key);
}

MultiScheme::MultiScheme() : ColorSchemeBase(eColorMode::eMultiMode) {
    ColorTerm debug;
    ColorTerm info;
    ColorTerm warning;
    ColorTerm error;
    ColorTerm fail;

    strncpy(debug.color,   PURPLE,   COLOR_MAX_SYM);
    strncpy(info.color,    STANDART, COLOR_MAX_SYM);
    strncpy(warning.color, YELLOW,   COLOR_MAX_SYM);
    strncpy(error.color,   RED,      COLOR_MAX_SYM);
    strncpy(fail.color,    RED,      COLOR_MAX_SYM);

    m_colorMap["debug"]   = debug;
    m_colorMap["info"]    = info;
    m_colorMap["warning"] = warning;
    m_colorMap["error"]   = error;
    m_colorMap["fail"]    = fail;
}

bool MultiScheme::StringEscaped(std::string& _str, const std::string& _key) {
    return ColorSchemeBase::StringEscaped(_str, _key);
}

PartialScheme::PartialScheme() : ColorSchemeBase(eColorMode::ePartialMode) {
    ColorTerm debug;
    ColorTerm info;
    ColorTerm warning;
    ColorTerm error;
    ColorTerm fail;

    strncpy(debug.color,   STANDART, COLOR_MAX_SYM);
    strncpy(info.color,    GREEN,    COLOR_MAX_SYM);
    strncpy(warning.color, RED,      COLOR_MAX_SYM);
    strncpy(error.color,   RED,      COLOR_MAX_SYM);
    strncpy(fail.color,    RED,      COLOR_MAX_SYM);

    m_colorMap["debug"]   = debug;
    m_colorMap["info"]    = info;
    m_colorMap["warning"] = warning;
    m_colorMap["error"]   = error;
    m_colorMap["fail"]    = fail;
}

bool PartialScheme::StringEscaped(std::string& _str, const std::string& _key) {
    return ColorSchemeBase::StringEscaped(_str, _key);
}

UserScheme::UserScheme() : ColorSchemeBase(eColorMode::eUserMode) {
    ColorTerm debug;
    ColorTerm info;
    ColorTerm warning;
    ColorTerm error;
    ColorTerm fail;

    strncpy(debug.color,   PURPLE,   COLOR_MAX_SYM);
    strncpy(info.color,    STANDART, COLOR_MAX_SYM);
    strncpy(warning.color, YELLOW,   COLOR_MAX_SYM);
    strncpy(error.color,   RED,      COLOR_MAX_SYM);
    strncpy(fail.color,    RED,      COLOR_MAX_SYM);

    m_colorMap["debug"]   = debug;
    m_colorMap["info"]    = info;
    m_colorMap["warning"] = warning;
    m_colorMap["error"]   = error;
    m_colorMap["fail"]    = fail;
}

bool UserScheme::StringEscaped(std::string& _str, const std::string& _key) {
    return ColorSchemeBase::StringEscaped(_str, _key);
}

