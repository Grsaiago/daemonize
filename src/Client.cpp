#include "../lib/Client.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include <optional>

Client::Client(int fd) : _fd(fd) {}

Client::~Client() {}

int Client::get_fd() const noexcept { return (this->_fd); }

std::optional<Error> Client::handle_poll(struct epoll_event ev) noexcept {
	auto server = Server::get_instance();

	if (ev.events & (EPOLLRDHUP)) {
		Info("a client disconected");
		auto err = server->remove_client(this->get_position());
		if (err.has_value()) {
			Err("failed to remove client: %s", err->reason.c_str());
			return (std::optional<Error>("failed to remove client"));
		}
	}
	return (std::nullopt);
}

int Client::get_position() const noexcept {
	auto server = Server::get_instance();
	for (auto i = 0; i < 3; i++) {
		if (this->get_fd() == server->get_clients().at(i)->_fd) {
		}
		return (i);
	}
	return (-1);
}

struct epoll_event Client::get_events_of_interest(void) const noexcept {
	struct epoll_event ev{};

	ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLRDHUP;
	ev.data.ptr = const_cast<Client *>(this);
	return ev;
}
