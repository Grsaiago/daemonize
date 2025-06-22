#include "../../lib/logging/Logger.hpp"

Logger *Logger::_instance = nullptr;

Logger::Logger(LogLevel level, std::unique_ptr<LogHandler> handler)
    : handler(std::move(handler)), level(level) {}

Logger::~Logger() {
	if (Logger::_instance == nullptr) {
		return;
	}
	delete Logger::_instance;
	return;
}

void Logger::init_with_level(
    LogLevel level, std::unique_ptr<LogHandler> handler
) noexcept {
	Logger::_instance = new Logger(level, std::move(handler));
	return;
}

// TODO: Tem que puxar o level de uma env
void Logger::init_with_env_level(std::unique_ptr<LogHandler> handler) noexcept {
	LogLevel level = LogLevel::INFO;

	Logger::_instance = new Logger(level, std::move(handler));
	return;
}

void Logger::debug(
    std::string message, std::string file, unsigned int line, std::string caller
) noexcept {
	(void)line;
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::DEBUG) {
		Logger::_instance->handler->debug_handler(
		    "[DEBUG] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + message
		);
	}
	return;
}

void Logger::info(
    std::string message, std::string file, unsigned int line, std::string caller
) noexcept {
	(void)line;
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::INFO) {
		Logger::_instance->handler->info_handler(
		    "[INFO] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + message
		);
	}
	return;
}

void Logger::warn(
    std::string message, std::string file, unsigned int line, std::string caller
) noexcept {
	(void)line;
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::WARN) {
		Logger::_instance->handler->warn_handler(
		    "[WARN] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + message
		);
	}
	return;
}

void Logger::error(
    std::string message, std::string file, unsigned int line, std::string caller
) noexcept {
	(void)line;
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::ERROR) {
		Logger::_instance->handler->error_handler(
		    "[ERROR] " + file + "::" + caller + "::" + std::to_string(line) +
		    ": " + message
		);
	}
	return;
}
