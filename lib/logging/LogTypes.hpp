#ifndef _LOG_TYPES_H_
#define _LOG_TYPES_H_

#include <ctime>
#include <string>

enum class LogLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 };

struct LogEvent {
	time_t       timestamp;
	std::string  file;
	unsigned int line;
	std::string  caller;
	std::string  message;
};
#endif // !_LOG_TYPES_H_
