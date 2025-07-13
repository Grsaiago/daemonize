#include "../lib/DaemonManager.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include "../lib/logging/TinTinReporter.hpp"
#include <exception>
#include <memory>
#include <new>

int main() {
	Logger::init_with_level(LogLevel::INFO, std::make_unique<TinTinReporter>());
	std::string    input;
	DaemonManager *daemon_manager = nullptr;

	try {
		daemon_manager = new DaemonManager();
	} catch (const std::exception &err) {
		Err(err.what());
		return EXIT_FAILURE;
	}

	Info("Essa string aqui");
	std::getline(std::cin, input);

	delete daemon_manager;
	return EXIT_SUCCESS;
}
