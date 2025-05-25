#include "../lib/Listener.hpp"

Listener::Listener(): _fd(-1) {}

Listener::~Listener() {}

int	Listener::get_fd() const {
	return (this->_fd);
}

int	Listener::handle_poll(void) noexcept {
	return (0);
}
