#include "../lib/Server.hpp"

int main(void) {
	Server		*ptr;
	std::string	input;

	ptr = new(std::nothrow) Server();
	if (ptr == nullptr) {
		return (EXIT_FAILURE);
	}

	std::getline(std::cin, input);

	delete ptr;
}
