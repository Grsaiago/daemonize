#include "../../lib/logging/TinTinReporter.hpp"

TinTinReporter::TinTinReporter() : LogHandler() {}

TinTinReporter::~TinTinReporter() {}

void TinTinReporter::debug_handler(std::string message) noexcept {
	(void)message;
	return;
}

void TinTinReporter::info_handler(std::string message) noexcept {
	(void)message;
	return;
}

void TinTinReporter::warn_handler(std::string message) noexcept {
	(void)message;
	return;
}

void TinTinReporter::error_handler(std::string message) noexcept {
	(void)message;
	return;
}
