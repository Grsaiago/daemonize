#include "../lib/Server.hpp"

Server *Server::_instance = nullptr;

Server *Server::get_instance() noexcept {
	if (Server::_instance == nullptr) {
		Server::_instance = new(std::nothrow) Server();
	}
	return (Server::_instance);
}

Server::Server() noexcept(false) : _epoll_fd(-1) {
	this->_epoll_fd = epoll_create(3);
	if (this->_epoll_fd == -1) {
		throw std::logic_error(strerror(errno));
	}
	return;
}

Server::~Server() noexcept(false) {
	if (this->_epoll_fd != -1) {
		close(this->_epoll_fd);
	}
	return;
}

std::optional<Error>	Server::add_new_client(Client &new_client) noexcept {
	(void)new_client;
	return (std::nullopt);
}

std::optional<Error>	Server::listen_and_serve() noexcept {
	return (std::nullopt);
}
