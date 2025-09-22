#ifndef _LOGFILEHANDLER_H_
#define _LOGFILEHANDLER_H_

#include "LogTypes.hpp"
#include "LogHandler.hpp"

class LogFileHandler : public LogHandler {
  public:
	LogFileHandler() = delete;
	LogFileHandler(std::string filename);
	virtual ~LogFileHandler();

	virtual void debug_handler(LogEvent event) noexcept override;
	virtual void info_handler(LogEvent event) noexcept override;
	virtual void warn_handler(LogEvent event) noexcept override;
	virtual void error_handler(LogEvent event) noexcept override;
  private:
	int	_fd;
	std::string	filename;
};

#endif // !_LOGFILEHANDLER_H_
