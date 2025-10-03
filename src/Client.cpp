#include "../lib/Client.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include <optional>
#include <sys/socket.h>

Client::Client(int fd) : _fd(fd) {}

Client::~Client() {
	if (this->_fd > 0) {
		shutdown(this->_fd, SHUT_RDWR);
	}
	return;
}

int Client::get_fd() const noexcept { return (this->_fd); }

// construtor de move
Client::Client(Client &&other) noexcept : _fd(other._fd) { other._fd = -1; }

std::optional<Error> Client::handle_poll(struct epoll_event ev) noexcept {
	auto        server = Server::get_instance();
	char        read_buffer[1024];
	std::string user_message;

	if (ev.events & (EPOLLRDHUP)) {
		Info("a client disconected");
		auto err = server->remove_client(this->get_position());
		if (err.has_value()) {
			Err("failed to remove client: %s", err->reason.c_str());
			return (std::optional<Error>("failed to remove client"));
		}
	} else if (ev.events & (EPOLLIN)) {
		Debug("a client is ready to read");
		memset(read_buffer, 0, sizeof(read_buffer));
		user_message.clear();
		while (true) {
			auto bytes_read =
			    recv(this->get_fd(), read_buffer, sizeof(read_buffer) - 1, 0);
			if (bytes_read > 0) {
				user_message.append(read_buffer, bytes_read);
				if (bytes_read <
				    static_cast<ssize_t>(sizeof(read_buffer) - 1)) {
					break;
				} else if (bytes_read == 0) {
					Info("client disconnected");
					auto err = server->remove_client(this->get_position());
					if (err.has_value()) {
						Err("failed to remove client: %s", err->reason.c_str());
						return (
						    std::optional<Error>("failed to remove client")
						);
					}
					return (std::nullopt);
				} else {
					if (errno == EAGAIN || errno == EWOULDBLOCK) {
						break;
					} else {
						Err("recv failed: %s", strerror(errno));
						auto err = server->remove_client(this->get_position());
						if (err.has_value()) {
							Err("failed to remove client: %s",
							    err->reason.c_str());
							return (
							    std::optional<Error>("failed to remove client")
							);
						}
						return (std::nullopt);
					}
				}
			}
		}
		if (user_message[user_message.length() - 1] == '\n') {
			user_message.pop_back();
		}
		if (user_message == "quit") {
			Info("Client requested quit");
			server->set_should_run(false);
			return (std::nullopt);
		}
		Info(user_message.c_str());
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
