#ifndef _SYSTEMD_REPORTER_H_
#define _SYSTEMD_REPORTER_H_

#include "LogHandler.hpp"
#include <iostream>

class SystemdReporter : public LogHandler {
  public:
	SystemdReporter();
	~SystemdReporter();

	void debug_handler(std::string message) noexcept override;
	void info_handler(std::string message) noexcept override;
	void warn_handler(std::string message) noexcept override;
	void error_handler(std::string message) noexcept override;
};

#endif // !_SYSTEMD_REPORTER_H_
