#include "../lib/Server.hpp"
#include <cstdlib>
#include <new>

int main(void) {
	Server *ptr = new(std::nothrow) Server();
	if (ptr == nullptr) {
		return (EXIT_FAILURE);
	}

	std::cout << "lockfile path: " << ptr->lockfile_path << std::endl;
	std::cout << "lockfile name: " << ptr->lockfile_name << std::endl;
}
