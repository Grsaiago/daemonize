#include "../lib/Server.hpp"
#include "../lib/daemonize.hpp"

int main(void) {
	Server		*ptr;
	std::string	input;

	if (Server::lockfile_exists()) {
		std::cerr << "File already exists" << std::endl;
		return (EXIT_FAILURE);
	}
	ptr = Server::get_instance();
	if (ptr == nullptr) {
		return (EXIT_FAILURE);
	}

	std::getline(std::cin, input);

	delete ptr;
	return (EXIT_SUCCESS);
}
