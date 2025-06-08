#include "../lib/Server.hpp"

const std::string Server::lockfile_path = std::string("/var/lock/");
const std::string Server::lockfile_name = std::string("matt_daemon.lock");
const std::string Server::lockfile_fullpath = Server::lockfile_path + Server::lockfile_name;
Server *Server::_instance = nullptr;

Server *const	Server::get_instance() noexcept {
	if (Server::_instance == nullptr) {
		Server::_instance = new(std::nothrow) Server();
	}
	return (Server::_instance);
}

Server::Server() noexcept(false) : _lockfile_fd(-1), _epoll_fd(-1) {
	auto result = this->open_lockfile();
	if (result.has_value()) {
		throw std::logic_error(result.value().reason);
	}

	this->_epoll_fd = epoll_create(3);
	if (this->_epoll_fd == -1) {
		throw std::logic_error(strerror(errno));
	}
	return;
}

/*
 * Checks if the lockfile exists
 * */
bool	Server::lockfile_exists() noexcept {
	return (access(Server::lockfile_fullpath.c_str(), F_OK) == 0);
}

Server::~Server() noexcept(false) {
	auto result = this->close_lockfile();
	if (result.has_value()) {
		throw std::logic_error(result.value().reason);
	}
	if (this->_epoll_fd != -1) {
		close(this->_epoll_fd);
	}
	return;
}

int	Server::get_lockfile_fd() const {
	return (this->_lockfile_fd);
}

std::optional<Error>	Server::open_lockfile() {
	// create file
	this->_lockfile_fd = open(
		Server::lockfile_fullpath.c_str(),
		O_CREAT // create the file
		| O_EXCL // error if the file already exists
		| O_NONBLOCK // not block on trying to acquire lock
		| O_WRONLY, // open the file in write only
		S_IWUSR | S_IRUSR // User permission to read and write */
		| S_IRGRP | S_IROTH // Others and Group have read permission */
	);
	if (this->_lockfile_fd < 0) {
		if (errno == EEXIST) {
			return (std::optional<Error>("file already exists"));
		} else {
			return (std::optional<Error>(strerror(errno)));
		}
	}
	//lock file
	if (flock(this->_lockfile_fd, LOCK_EX | LOCK_NB) < 0) {
		if (errno == EWOULDBLOCK) {
			return (std::optional<Error>("the lock is already in place by another instance of Server"));
		}
		return (std::optional<Error>(strerror(errno)));
	}
	// write my pid in the file
	std::string	pid = std::to_string(getpid());
	write(this->_lockfile_fd, pid.c_str(), pid.length());
	return (std::nullopt);
}

std::optional<Error>	Server::close_lockfile() {
	if (this->_lockfile_fd < 0) {
		return (std::optional<Error>("this Server instance doesn't have a handle to the file"));
	}
	// try to unlock file
	if (flock(this->_lockfile_fd, LOCK_UN | LOCK_NB) < 0) {
		if (errno == EWOULDBLOCK) {
			return (std::optional<Error>("cannot unlock file: lock is in place by another instance of Server"));
		}
		return (std::optional<Error>(strerror(errno)));
	}
	// delete the file
	if (unlink(Server::lockfile_fullpath.c_str()) != 0) {
		return (std::optional<Error>(strerror(errno)));
	}
	return (std::nullopt);
}

std::optional<Error>	Server::listen_and_serve() noexcept {

	return (std::nullopt);
}
