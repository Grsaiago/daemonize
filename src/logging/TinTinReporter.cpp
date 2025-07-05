#include "../../lib/logging/TinTinReporter.hpp"
#include <iostream>

TinTinReporter::TinTinReporter() : LogHandler() {}

TinTinReporter::~TinTinReporter() {}

void TinTinReporter::debug_handler(LogEvent event) noexcept {
	std::string final_message = "[DEBUG] " + event.file + "::" + event.caller +
	                            "::" + std::to_string(event.line) + ": " +
	                            event.message;
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::info_handler(LogEvent event) noexcept {
	std::string final_message = "[INFO] " + event.file + "::" + event.caller +
	                            "::" + std::to_string(event.line) + ": " +
	                            event.message;
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::warn_handler(LogEvent event) noexcept {
	std::string final_message = "[WARN] " + event.file + "::" + event.caller +
	                            "::" + std::to_string(event.line) + ": " +
	                            event.message;
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::error_handler(LogEvent event) noexcept {
	std::string final_message = "[ERROR] " + event.file + "::" + event.caller +
	                            "::" + std::to_string(event.line) + ": " +
	                            event.message;
	std::cout << final_message << std::endl;
	return;
}
