#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include <cerrno>
#include <cstring>
#include <optional>
#include <sys/epoll.h>

Server *Server::_instance = nullptr;

Server *Server::install_new_default_server(
    std::string &host, std::string &port
) noexcept {
	if (Server::_instance == nullptr) {
		Server::_instance = new (std::nothrow) Server();
	}
	Server::_instance->_listener = new Listener(Server::_instance, host, port);
	return (Server::_instance);
}

Server *Server::get_instance(void) noexcept {
	if (Server::_instance == nullptr) {
		Server::_instance = new (std::nothrow) Server();
	}
	return (Server::_instance);
}

Server::Server() noexcept(false) : _epoll_fd(-1), _clients(), _listener() {
	std::string host = "0.0.0.0";
	std::string port = "4242";
	this->_listener = new Listener(this, host, port);
	return;
}

Server::~Server() noexcept(false) {
	if (this->_epoll_fd != -1) {
		close(this->_epoll_fd);
	}
	return;
}

std::optional<Error> Server::add_new_client(Client &new_client) noexcept {
	(void)new_client;
	return (std::nullopt);
}

std::optional<Error> Server::listen_and_serve(
    std::string &start_message
) noexcept {
	this->_epoll_fd = epoll_create(5);
	if (this->_epoll_fd == -1) {
		return (std::optional<Error>(strerror(errno)));
	}
	if (std::optional<Error> listen_return = this->_listener->listen();
	    listen_return.has_value()) {
		return (std::optional<Error>(listen_return->reason));
	}
	return (std::nullopt);

	Info(start_message.c_str());
	return (this->event_loop());
}

std::optional<Error> Server::event_loop(void) noexcept {
	return (std::nullopt);
}
