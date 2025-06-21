#ifndef _TIN_TIN_REPORTER_H_
#define _TIN_TIN_REPORTER_H_

#include "LogHandler.hpp"

class TinTinReporter : public LogHandler {
  public:
	TinTinReporter();
	~TinTinReporter();

	void debug_handler(std::string message) noexcept override;
	void info_handler(std::string message) noexcept override;
	void warn_handler(std::string message) noexcept override;
	void error_handler(std::string message) noexcept override;
};

#endif // !_TIN_TIN_REPORTER_H_
