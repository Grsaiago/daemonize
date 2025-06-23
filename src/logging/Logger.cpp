#include "../../lib/logging/Logger.hpp"

std::unique_ptr<Logger> Logger::_instance = nullptr;

Logger::Logger(LogLevel level, std::unique_ptr<LogHandler> handler)
    : handler(std::move(handler)), level(level) {}

Logger::~Logger() {
	if (Logger::_instance == nullptr) {
		return;
	}
	return;
}

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
    std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr) {
		return;
	}

	va_start(vlist, message);
	if (Logger::_instance->level <= LogLevel::DEBUG) {
		std::string formatted_message = get_formatted_message(message, vlist);
		Logger::_instance->handler->debug_handler(
		    "[INFO] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + formatted_message
		);
	}
	return;
}

void Logger::info(
    std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr) {
		return;
	}

	va_start(vlist, message);
	if (Logger::_instance->level <= LogLevel::INFO) {
		std::string formatted_message = get_formatted_message(message, vlist);
		Logger::_instance->handler->info_handler(
		    "[INFO] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + formatted_message
		);
	}
	return;
}

void Logger::warn(
    std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr) {
		return;
	}

	va_start(vlist, message);
	if (Logger::_instance->level <= LogLevel::WARN) {
		std::string formatted_message = get_formatted_message(message, vlist);
		Logger::_instance->handler->warn_handler(
		    "[INFO] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + formatted_message
		);
	}
	return;
}

void Logger::error(
    std::string file, unsigned int line, std::string caller,
    std::string message, ...
) noexcept {
	va_list vlist;

	if (Logger::_instance == nullptr) {
		return;
	}

	va_start(vlist, message);
	if (Logger::_instance->level <= LogLevel::ERROR) {
		std::string formatted_message = get_formatted_message(message, vlist);
		Logger::_instance->handler->error_handler(
		    "[INFO] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + formatted_message
		);
	}
	return;
}
