#include "../lib/Client.hpp"
#include <optional>

Client::Client(int fd) : _fd(fd) {}

Client::~Client() {}

int Client::get_fd() const noexcept { return (this->_fd); }

std::optional<Error> Client::handle_poll(struct epoll_event ev) noexcept {
	(void)ev;
	return (std::nullopt);
}

struct epoll_event Client::get_events_of_interest(void) const noexcept {
	struct epoll_event ev{};

	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.ptr = const_cast<Client *>(this);
	return ev;
}
