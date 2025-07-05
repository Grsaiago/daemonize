#ifndef _SYSTEMD_REPORTER_H_
#define _SYSTEMD_REPORTER_H_

#include "LogHandler.hpp"

class SyslogReporter : public LogHandler {
  public:
	SyslogReporter();
	SyslogReporter(LogLevel level);
	~SyslogReporter();

	void debug_handler(LogEvent event) noexcept override;
	void info_handler(LogEvent event) noexcept override;
	void warn_handler(LogEvent event) noexcept override;
	void error_handler(LogEvent event) noexcept override;
};

#endif // !_SYSTEMD_REPORTER_H_
