#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LogHandler.hpp"
#include <memory>
#include <string>

#define Debug(msg) (Logger::debug(msg, __FILE__, __LINE__, __func__))
#define Info(msg) (Logger::info(msg, __FILE__, __LINE__, __func__))
#define Warn(msg) (Logger::warn(msg, __FILE__, __LINE__, __func__))
#define Error(msg) (Logger::error(msg, __FILE__, __LINE__, __func__))

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

	static std::unique_ptr<Logger> _instance;

	static void debug(
	    std::string message, std::string file, unsigned int line,
	    std::string caller
	) noexcept;
	static void info(
	    std::string message, std::string file, unsigned int line,
	    std::string caller
	) noexcept;
	static void warn(
	    std::string message, std::string file, unsigned int line,
	    std::string caller
	) noexcept;
	static void error(
	    std::string message, std::string file, unsigned int line,
	    std::string caller
	) noexcept;

  private:
	Logger(LogLevel level, std::unique_ptr<LogHandler> handler);
};

#endif // !_LOGGER_H_
