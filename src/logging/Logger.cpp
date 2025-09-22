#include "../../lib/logging/Logger.hpp"
#include "../../lib/logging/logging_utils.hpp"

std::unique_ptr<Logger> Logger::_instance = nullptr;

Logger::Logger(LogLevel level, std::unique_ptr<LogHandler> handler)
    : handler(std::move(handler)), level(level) {}

Logger::~Logger() {}

void Logger::init_with_level(
    LogLevel level, std::unique_ptr<LogHandler> handler
) noexcept {
	auto ptr = new Logger(level, std::move(handler));
	Logger::_instance = std::unique_ptr<Logger>(ptr);
	return;
}

// TODO: Tem que puxar o level de uma env
void Logger::init_with_env_level(std::unique_ptr<LogHandler> handler) noexcept {
	LogLevel level = LogLevel::INFO;
	auto     ptr = new Logger(level, std::move(handler));

	Logger::_instance = std::unique_ptr<Logger>(ptr);
	return;
}

void Logger::debug(
    time_t timestamp, std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr ||
	    Logger::_instance->level > LogLevel::DEBUG) {
		return;
	}

	va_start(vlist, message);
	std::string formatted_message = get_formatted_message(message, vlist);
	va_end(vlist);
	struct LogEvent ev = {
	    .timestamp = timestamp,
	    .file = file,
	    .line = line,
	    .caller = caller,
	    .message = formatted_message,
	};

	Logger::_instance->handler->debug_handler(ev);
	return;
}

void Logger::info(
    time_t timestamp, std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr ||
	    Logger::_instance->level > LogLevel::INFO) {
		return;
	}

	va_start(vlist, message);
	std::string formatted_message = get_formatted_message(message, vlist);
	va_end(vlist);
	struct LogEvent ev = {
	    .timestamp = timestamp,
	    .file = file,
	    .line = line,
	    .caller = caller,
	    .message = formatted_message,
	};

	Logger::_instance->handler->info_handler(ev);
	return;
}

void Logger::warn(
    time_t timestamp, std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr ||
	    Logger::_instance->level > LogLevel::WARN) {
		return;
	}

	va_start(vlist, message);
	std::string formatted_message = get_formatted_message(message, vlist);
	va_end(vlist);
	struct LogEvent ev = {
	    .timestamp = timestamp,
	    .file = file,
	    .line = line,
	    .caller = caller,
	    .message = formatted_message,
	};

	Logger::_instance->handler->warn_handler(ev);
	return;
}

void Logger::error(
    time_t timestamp, std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr ||
	    Logger::_instance->level > LogLevel::ERROR) {
		return;
	}

	va_start(vlist, message);
	std::string formatted_message = get_formatted_message(message, vlist);
	va_end(vlist);
	struct LogEvent ev = {
	    .timestamp = timestamp,
	    .file = file,
	    .line = line,
	    .caller = caller,
	    .message = formatted_message,
	};

	Logger::_instance->handler->error_handler(ev);
	return;
}
