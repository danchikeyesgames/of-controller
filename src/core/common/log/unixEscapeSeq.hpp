#ifndef _LOG_UNIX_ESCAPE_SEQ_HPP_
#define _LOG_UNIX_ESCAPE_SEQ_HPP_

#include "colorscheme.hpp"

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


#endif  // _LOG_UNIX_ESCAPE_SEQ_HPP_