#include "../lib/Client.hpp"

Client::Client(int fd): _fd(fd) {}

Client::~Client() {}

int	Client::get_fd() const noexcept {
	return (this->_fd);
}

int	Client::handle_poll(void) noexcept {
	return 0;
}
