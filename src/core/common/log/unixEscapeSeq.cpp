#ifndef _WIN32

#include "unixEscapeSeq.hpp"

#include <cstdlib>
#include <cstring>

static const char* const cTERM = std::getenv("TERM");
static const char* const cColors = "256color";

static bool isTermMode256;

/* usual term mode */

static const char* const cColorStandart= "\033[39m";
static const char* const cColorRed     = "\033[91m";
static const char* const cColorYellow  = "\033[93m";
static const char* const cColorGreen   = "\033[92m";
static const char* const cColorPurple  = "\033[95m";

static const char* const cDarkColorRed    = "\033[31m";
static const char* const cDarkColorYellow = "\033[33m";
static const char* const cDarkColorGreen  = "\033[32m";
static const char* const cDarkColorPurple = "\033[35m";

/* 256 color term mode */

static const char* const cColorStandart256= "\033[39m";
static const char* const cColorRed256     = "\033[91m";
static const char* const cColorYellow256  = "\033[93m";
static const char* const cColorGreen256   = "\033[92m";
static const char* const cColorPurple256  = "\033[95m";

static const char* const cDarkColorRed256    = "\033[31m";
static const char* const cDarkColorYellow256 = "\033[33m";
static const char* const cDarkColorGreen256  = "\033[32m";
static const char* const cDarkColorPurple256 = "\033[35m";


bool CheckTermSupport256() {
    isTermMode256 = (strstr(cTERM, cColors) == NULL ? false : true);
    return isTermMode256;
}

const char* GetColorDefault() {
    return isTermMode256 ? cColorStandart256 : cColorStandart;
}

const char* GetColorRed() {
    return isTermMode256 ? cColorRed256 : cColorRed;
}

const char* GetColorYellow() {
    return isTermMode256 ? cColorYellow256 : cColorYellow;
}

const char* GetColorGreen() {
    return isTermMode256 ? cColorGreen256 : cColorGreen;
}

const char* GetColorPurple(){
    return isTermMode256 ? cColorPurple256 : cColorPurple;
}

const char* GetColorDarkRed() {
    return isTermMode256 ? cDarkColorRed256 : cDarkColorRed;
}

const char* GetColorDarkYellow() {
    return isTermMode256 ? cDarkColorYellow256 : cDarkColorYellow;
}

const char* GetColorDarkGreen() {
    return isTermMode256 ? cDarkColorGreen256 : cDarkColorGreen;
}

const char* GetColorDarkPurple() {
    return isTermMode256 ? cDarkColorPurple256 : cDarkColorPurple;
}

#endif  // _WIN32