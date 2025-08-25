#include "../lib/Listener.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <optional>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

Listener::Listener(
    Server *server_instance, const std::string &host, const std::string &port
)
    : _fd(-1), _server_instance(server_instance), _host(host), _port(port) {
	struct sockaddr_storage addr;
	socklen_t               addr_len;

	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd < 0) {
		throw std::runtime_error(
		    std::string("error opening the listener socket: ") +
		    std::strerror(errno)
		);
	}
	if (!this->resolve_addr(&addr, this->_host.c_str())) {
		throw std::runtime_error(
		    std::string("error opening the listener socket: ") +
		    std::strerror(errno)
		);
	}

	switch (addr.ss_family) {
	case (AF_INET):
		addr_len = sizeof(struct sockaddr_in);
		break;
	case (AF_INET6):
		addr_len = sizeof(struct sockaddr_in6);
		break;
	}
	if (bind(this->_fd, reinterpret_cast<struct sockaddr *>(&addr), addr_len) !=
	    0) {
		throw std::runtime_error(
		    std::string("error on binding listener socket: ") +
		    std::strerror(errno)
		);
	}
	return;
}

Listener::~Listener() {
	if (this->_fd != -1) {
		close(this->_fd);
		this->_fd = -1;
	}
}

bool Listener::resolve_addr(
    struct sockaddr_storage *result, std::string const &host
) noexcept {
	struct addrinfo const *it;
	struct addrinfo       *head;
	struct addrinfo        hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int getaddr_return =
	    getaddrinfo(host.c_str(), this->_port.c_str(), &hints, &head);
	if (getaddr_return != 0) {
		Err("getaddrinfo failed: %s", gai_strerror(getaddr_return));
		return (false);
	}
	for (it = head; it != NULL; it = it->ai_next) {
		if (it->ai_socktype == SOCK_STREAM &&
		    (it->ai_addrlen == sizeof(struct sockaddr_in) ||
		     it->ai_addrlen == sizeof(struct sockaddr_in6)) &&
		    (it->ai_family == AF_INET || it->ai_family == AF_INET6)) {
			switch (it->ai_family) {
			case (AF_INET):
				*reinterpret_cast<struct sockaddr_in *>(result) =
				    *reinterpret_cast<struct sockaddr_in *>(it->ai_addr);
				break;
			case (AF_INET6):
				*reinterpret_cast<struct sockaddr_in6 *>(result) =
				    *reinterpret_cast<struct sockaddr_in6 *>(it->ai_addr);
				break;
			}
			freeaddrinfo(head);
			return (true);
		}
	}
	Err("unable to find an available socket address");
	freeaddrinfo(head);
	return (false);
}

std::optional<Error> Listener::listen() noexcept {
	if (::listen(this->_fd, 100) != 0) {
		return std::optional<Error>(
		    std::string("error on listen call of listener socket: ") +
		    std::strerror(errno)
		);
	}
	return (std::nullopt);
}

int Listener::get_fd() const noexcept { return (this->_fd); }

std::optional<Error> Listener::handle_poll(struct epoll_event ev) noexcept {
	if (ev.events & EPOLLIN) {
		Info("Bateu um pollin aqui em");
	}
	return (std::nullopt);
}

struct epoll_event Listener::get_events_of_interest(void) const noexcept {
	struct epoll_event ev{};

	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = const_cast<void *>(reinterpret_cast<const void *>(this));
	return (ev);
}
