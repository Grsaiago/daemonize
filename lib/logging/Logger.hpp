#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LogHandler.hpp"
#include "LogTypes.hpp"
#include "logging_utils.hpp"
#include <cstdarg>
#include <memory>
#include <string>

#define Debug(msg, ...)                                                        \
	(Logger::debug(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__))

#define Info(msg, ...)                                                         \
	(Logger::info(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__))

#define Warn(msg, ...)                                                         \
	(Logger::warn(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__))

#define Err(msg, ...)                                                          \
	(Logger::error(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__))

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

	static std::unique_ptr<Logger> _instance;

	static void debug(
	    std::string file, unsigned int line, std::string caller,
	    std::string message, ...
	) noexcept;
	static void info(
	    std::string file, unsigned int line, std::string caller,
	    std::string message, ...
	) noexcept;
	static void warn(
	    std::string file, unsigned int line, std::string caller,
	    std::string message, ...
	) noexcept;
	static void error(
	    std::string file, unsigned int line, std::string caller,
	    std::string message, ...
	) noexcept;

  private:
	Logger(LogLevel level, std::unique_ptr<LogHandler> handler);
};

#endif // !_LOGGER_H_
