#ifndef _DEBUG_UTILS_H
#define _DEBUG_UTILS_H

#include <cstdarg>
#include <string>

std::string get_formatted_message(std::string fmessage, va_list args);

#endif // !_DEBUG_UTILS_H
