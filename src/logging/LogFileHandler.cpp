#include "../../lib/logging/LogFileHandler.hpp"
#include <ctime>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

LogFileHandler::LogFileHandler(std::string filename) : LogHandler(), _fd(-1) {
	// Ensure parent directory exists
	std::filesystem::path filepath(filename);
	std::filesystem::create_directories(filepath.parent_path());

	this->_fd = open(
	    filename.c_str(),
	    O_CREAT                 // create the file
	        | O_APPEND          // do not truncate the file
	        | O_NONBLOCK        // not block on trying to acquire lock
	        | O_WRONLY,         // open the file in write only
	    S_IWUSR | S_IRUSR       // User permission to read and write
	        | S_IRGRP | S_IROTH // Others and Group have read permission
	);
	if (this->_fd < 0) {
		throw std::logic_error("Unable to open file" + filename);
	}
}

LogFileHandler::~LogFileHandler() {
	if (_fd != -1) {
		close(_fd);
	}
}

void LogFileHandler::debug_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[DEBUG] " + event.file +
	    "::" + event.caller + "::" + std::to_string(event.line) + ": " +
	    event.message + "\n"
	);
	write(this->_fd, final_message.c_str(), final_message.length());
	return;
}

void LogFileHandler::info_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[INFO] " + event.file +
	    "::" + event.caller + "::" + std::to_string(event.line) + ": " +
	    event.message + "\n"
	);
	write(this->_fd, final_message.c_str(), final_message.length());
	return;
}

void LogFileHandler::warn_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[WARN] " + event.file +
	    "::" + event.caller + "::" + std::to_string(event.line) + ": " +
	    event.message + "\n"
	);
	write(this->_fd, final_message.c_str(), final_message.length());
	return;
}

void LogFileHandler::error_handler(LogEvent event) noexcept {
	std::tm *tm_info = std::localtime(&event.timestamp);
	char     time_buff[20];

	if (tm_info == nullptr) {
		std::cerr << "Error: localtime returned nullptr" << std::endl;
		return;
	}
	std::strftime(time_buff, sizeof(time_buff), "%Y-%m-%dT%H:%M:%S", tm_info);

	std::string final_message(
	    std::string("[") + time_buff + "] " + "[ERROR] " + event.file +
	    "::" + event.caller + "::" + std::to_string(event.line) + ": " +
	    event.message + "\n"
	);
	write(this->_fd, final_message.c_str(), final_message.length());
	return;
}
