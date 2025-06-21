#include "../../lib/logging/TinTinReporter.hpp"

TinTinReporter::TinTinReporter() : LogHandler() {}

TinTinReporter::~TinTinReporter() {}

void TinTinReporter::debug_handler(std::string message) noexcept {
	std::cout << message << std::endl;
	return;
}

void TinTinReporter::info_handler(std::string message) noexcept {
	std::cout << message << std::endl;
	return;
}

void TinTinReporter::warn_handler(std::string message) noexcept {
	std::cout << message << std::endl;
	return;
}

void TinTinReporter::error_handler(std::string message) noexcept {
	std::cout << message << std::endl;
	return;
}
