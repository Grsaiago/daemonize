#ifndef _LOGHANDLER_H_
#define _LOGHANDLER_H_

#include "LogTypes.hpp"

class LogHandler {
  public:
	LogHandler() = default;
	virtual ~LogHandler() = default;

	virtual void debug_handler(LogEvent event) noexcept = 0;
	virtual void info_handler(LogEvent event) noexcept = 0;
	virtual void warn_handler(LogEvent event) noexcept = 0;
	virtual void error_handler(LogEvent event) noexcept = 0;
};

#endif // !_LOGHANDLER_H_
