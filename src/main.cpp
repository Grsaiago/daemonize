#include "../lib/DaemonManager.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include "../lib/logging/TinTinReporter.hpp"
#include <exception>
#include <memory>
#include <new>

int main(void) {
	Logger::init_with_level(LogLevel::INFO, std::make_unique<TinTinReporter>());
	std::string    input;
	DaemonManager *daemon_manager;

	try {
		daemon_manager = new (std::nothrow) DaemonManager();
	} catch (std::exception &err) {
		Err(err.what());
		return (EXIT_FAILURE);
	}

	std::getline(std::cin, input);

	delete (daemon_manager);
	return (EXIT_SUCCESS);
}
