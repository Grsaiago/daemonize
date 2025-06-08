#include "../lib/Server.hpp"
#include "../lib/DaemonManager.hpp"
#include <new>

int main(void) {
	std::string	input;
	DaemonManager *const daemon_manager = new(std::nothrow) DaemonManager();

	if (daemon_manager == nullptr) {
		std::cerr << "Failed to create the daemon manager" << std::endl;
	}

	std::getline(std::cin, input);

	delete (daemon_manager);
	return (EXIT_SUCCESS);
}
