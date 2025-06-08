#include "../lib/Client.hpp"
#include <optional>

Client::Client(int fd): _fd(fd) {}

Client::~Client() {}

int	Client::get_fd() const noexcept {
	return (this->_fd);
}

std::optional<Error>	Client::handle_poll(void) noexcept {
	return (std::nullopt);
}
