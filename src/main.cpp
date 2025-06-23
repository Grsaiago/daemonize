#include "../lib/DaemonManager.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include "../lib/logging/TinTinReporter.hpp"
#include <memory>
#include <new>

int main(void) {

	int i = 10;
	Info("Essa mensagem aqui não deveria aparecer e nem crashar");
	Logger::init_with_level(LogLevel::INFO, std::make_unique<TinTinReporter>());
	Info("Essa deveria aparecer %d", i);
	Debug("Essa não deveria ser capturada");
	return (EXIT_SUCCESS);
	std::string          input;
	DaemonManager *const daemon_manager = new (std::nothrow) DaemonManager();

	if (daemon_manager == nullptr) {
		std::cerr << "Failed to create the daemon manager" << std::endl;
	}

	std::getline(std::cin, input);

	delete (daemon_manager);
	return (EXIT_SUCCESS);
}
