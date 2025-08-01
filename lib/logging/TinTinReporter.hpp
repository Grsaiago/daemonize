#ifndef _TIN_TIN_REPORTER_H_
#define _TIN_TIN_REPORTER_H_

#include "LogHandler.hpp"

class TinTinReporter : public LogHandler {
  public:
	TinTinReporter();
	~TinTinReporter();

	void debug_handler(LogEvent event) noexcept override;
	void info_handler(LogEvent event) noexcept override;
	void warn_handler(LogEvent event) noexcept override;
	void error_handler(LogEvent event) noexcept override;
};

#endif // !_TIN_TIN_REPORTER_H_
