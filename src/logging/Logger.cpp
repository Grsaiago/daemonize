#include "../../lib/logging/Logger.hpp"
#include <memory>
Logger *Logger::_instance = nullptr;

Logger::Logger(LogLevel level, std::unique_ptr<LogHandler> handler)
	: handler(handler), level(level) {}

Logger::~Logger() {
	if (Logger::_instance == nullptr) {
		return;
	}
	delete Logger::_instance;
	return;
}

void Logger::init_with_level(LogLevel level, LogHandler &handler) noexcept {
	Logger::_instance = new Logger(level, handler);
	return;
}

// TODO: Tem que puxar o level de uma env
void Logger::init_with_env_level(LogHandler &handler) noexcept {
	LogLevel level = LogLevel::INFO;

	Logger::_instance = new Logger(level, handler);
	return;
}

void Logger::debug(std::string message) noexcept {
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::DEBUG) {
		Logger::_instance->handler.info_handler(message);
	}
	return;
}

void Logger::info(std::string message) noexcept {
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::INFO) {
		Logger::_instance->handler.info_handler(message);
	}
	return;
}

void Logger::warn(std::string message) noexcept {
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::WARN) {
		Logger::_instance->handler.info_handler(message);
	}
	return;
}

void Logger::error(std::string message) noexcept {
	if (Logger::_instance == nullptr) {
		return;
	}
	if (Logger::_instance->level >= LogLevel::ERROR) {
		Logger::_instance->handler.info_handler(message);
	}
	return;
}
