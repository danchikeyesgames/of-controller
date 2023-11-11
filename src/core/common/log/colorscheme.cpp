#include "colorscheme.hpp"

ColorSchemeBase* s_colorScheme[eColorMode::eMaxColorMode] = {nullptr};

ColorSchemeBase::ColorSchemeBase(eColorMode _colorMode) : m_colorMode(_colorMode) {}

bool ColorSchemeBase::StringEscaped(std::string& _str, const std::string& _key) {
    auto iter = m_colorMap.find(_key.c_str());
    if (iter != m_colorMap.end())
        return false;

    std::string tmpStr = iter->second.color;
    tmpStr += _str;
    tmpStr += "]";

    _str.clear();
    _str = std::move(tmpStr);
    return true;
};

bool ColorSchemeBase::RegisterColorScheme() {
    if (s_colorScheme[(uint32_t) m_colorMode] != nullptr) {
        return false;
    }

    s_colorScheme[(uint32_t) m_colorMode] = this;
    return true;
}

