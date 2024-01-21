#ifndef _UNIX_ESCAPED_SEQ_HPP_
#define _UNIX_ESCAPED_SEQ_HPP_

#ifndef _WIN32

bool CheckTermSupport256();

const char* GetColorDefault();
const char* GetColorRed();
const char* GetColorYellow();
const char* GetColorGreen();
const char* GetColorPurple();

const char* GetColorDarkRed();
const char* GetColorDarkYellow();
const char* GetColorDarkGreen();
const char* GetColorDarkPurple();

#define STANDART GetColorDefault()
#define RED GetColorRed()
#define YELLOW GetColorYellow()
#define GREEN GetColorGreen()
#define PURPLE GetColorPurple()

#define DARK_RED GetColorDarkRed()
#define DARK_YELLOW GetColorDarkYellow()
#define DARK_GREEN GetColorDarkGreen()
#define DARK_PURPLE GetColorDarkPurple()


#endif  // _WIN32
#endif  // _UNIX_ESCAPED_SEQ_HPP_