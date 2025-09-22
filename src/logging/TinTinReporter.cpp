#include "../../lib/logging/TinTinReporter.hpp"
#include <ctime>
#include <iostream>
#include <string>

TinTinReporter::TinTinReporter() : LogHandler() {}

TinTinReporter::~TinTinReporter() {}

void TinTinReporter::debug_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[DEBUG] " + event.file + "::" +
	    event.caller + "::" + std::to_string(event.line) + ": " + event.message
	);
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::info_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[INFO] " + event.file + "::" +
	    event.caller + "::" + std::to_string(event.line) + ": " + event.message
	);
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::warn_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[WARN] " + event.file + "::" +
	    event.caller + "::" + std::to_string(event.line) + ": " + event.message
	);
	std::cout << final_message << std::endl;
	return;
}

void TinTinReporter::error_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[ERROR] " + event.file + "::" +
	    event.caller + "::" + std::to_string(event.line) + ": " + event.message
	);
	std::cout << final_message << std::endl;
	return;
}
