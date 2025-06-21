#ifndef _LOGHANDLER_H_
#define _LOGHANDLER_H_

#include <string>

class LogHandler {
  public:
	LogHandler() = default;
	virtual ~LogHandler() = default;

	virtual void debug_handler(std::string message) noexcept = 0;
	virtual void info_handler(std::string message) noexcept = 0;
	virtual void warn_handler(std::string message) noexcept = 0;
	virtual void error_handler(std::string message) noexcept = 0;
};

#endif // !_LOGHANDLER_H_
