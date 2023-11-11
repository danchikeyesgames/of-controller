#ifndef _WIN32

#include "unixEscapeSeq.hpp"

#include <cstdlib>

static const char* TERM = std::getenv("TERM");

StandartScheme::StandartScheme() : ColorSchemeBase(eColorMode::eStandartMode) {

}


#endif  // _WIN32