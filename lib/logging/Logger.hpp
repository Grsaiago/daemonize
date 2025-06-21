#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LogHandler.hpp"
#include <memory>
#include <string>

enum class LogLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 };

class Logger {
  public:
	~Logger();
	static void init_with_level(
	    LogLevel level, std::unique_ptr<LogHandler> handler
	) noexcept;

	static void init_with_env_level(
	    std::unique_ptr<LogHandler> handler
	) noexcept;

	std::unique_ptr<LogHandler> handler;
	LogLevel                    level;

	static Logger *_instance;
	static void    debug(std::string message) noexcept;
	static void    info(std::string message) noexcept;
	static void    warn(std::string message) noexcept;
	static void    error(std::string message) noexcept;

  private:
	Logger(LogLevel level, LogHandler &handler);
};

#endif // !_LOGGER_H_
