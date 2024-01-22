#include "unix_escaped_seq.hpp"

#ifndef _WIN32

#include <cstdlib>
#include <cstring>

static bool isTerm256Supported = false;

static const char* cTERMENV = std::getenv("TERM");
static const char* c256Color = "256color";

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
static const char* const cColorRed256     = "\033[01;38;05;196m";
static const char* const cColorYellow256  = "\033[01;38;05;226m";
static const char* const cColorGreen256   = "\033\033[01;38;05;46m";
static const char* const cColorPurple256  = "\033[\033[01;38;05;129m";

static const char* const cDarkColorRed256    = "\033[01;38;05;88m";
static const char* const cDarkColorYellow256 = "\033[01;38;05;100m";
static const char* const cDarkColorGreen256  = "\033[01;38;05;22m";
static const char* const cDarkColorPurple256 = "\033[01;38;05;53m";


bool CheckTermSupport256()
{
    isTerm256Supported = std::strstr(cTERMENV, c256Color) == NULL ? false : true;
    return isTerm256Supported;
}

const char* GetColorDefault() {
    return isTerm256Supported ? cColorStandart256 : cColorStandart;
}

const char* GetColorRed() {
    return isTerm256Supported ? cColorRed256 : cColorRed;
}

const char* GetColorYellow() {
    return isTerm256Supported ? cColorYellow256 : cColorYellow;
}

const char* GetColorGreen() {
    return isTerm256Supported ? cColorGreen256 : cColorGreen;
}

const char* GetColorPurple(){
    return isTerm256Supported ? cColorPurple256 : cColorPurple;
}

const char* GetColorDarkRed() {
    return isTerm256Supported ? cDarkColorRed256 : cDarkColorRed;
}

const char* GetColorDarkYellow() {
    return isTerm256Supported ? cDarkColorYellow256 : cDarkColorYellow;
}

const char* GetColorDarkGreen() {
    return isTerm256Supported ? cDarkColorGreen256 : cDarkColorGreen;
}

const char* GetColorDarkPurple() {
    return isTerm256Supported ? cDarkColorPurple256 : cDarkColorPurple;
}

#endif  // _WIN32