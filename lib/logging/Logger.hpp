#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LogHandler.hpp"
#include "LogTypes.hpp"
#include <cstdarg>
#include <ctime>
#include <memory>
#include <string>

#define Debug(msg, ...)                                                        \
	(Logger::debug(                                                            \
	    std::time(0), __FILE__, __LINE__, __func__, msg, ##__VA_ARGS__         \
	))

#define Info(msg, ...)                                                         \
	(Logger::info(                                                             \
	    std::time(0), __FILE__, __LINE__, __func__, msg, ##__VA_ARGS__         \
	))

#define Warn(msg, ...)                                                         \
	(Logger::warn(                                                             \
	    std::time(0), __FILE__, __LINE__, __func__, msg, ##__VA_ARGS__         \
	))

#define Err(msg, ...)                                                          \
	(Logger::error(                                                            \
	    std::time(0), __FILE__, __LINE__, __func__, msg, ##__VA_ARGS__         \
	))

class Logger {
  public:
	Logger() = delete;
	Logger(const Logger &cpy) = delete;
	~Logger();
	Logger &operator=(const Logger &rhs) = delete;

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
	    time_t timestamp, std::string file, unsigned int line,
	    std::string caller, std::string message, ...
	) noexcept;
	static void info(
	    time_t timestamp, std::string file, unsigned int line,
	    std::string caller, std::string message, ...
	) noexcept;
	static void warn(
	    time_t timestamp, std::string file, unsigned int line,
	    std::string caller, std::string message, ...
	) noexcept;
	static void error(
	    time_t timestamp, std::string file, unsigned int line,
	    std::string caller, std::string message, ...
	) noexcept;

  private:
	Logger(LogLevel level, std::unique_ptr<LogHandler> handler);
};

#endif // !_LOGGER_H_
