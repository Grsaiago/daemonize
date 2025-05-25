#include "../lib/Server.hpp"

const std::string Server::lockfile_path = std::string("/var/lock/");
const std::string Server::lockfile_name = std::string("matt_daemon.lock");
const std::string Server::lockfile_fullpath = Server::lockfile_path + Server::lockfile_name;

Server::Server(): _lockfile_fd(-1), _epoll_fd(-1) {
	this->open_lockfile();
}

Server::~Server() {}

int	Server::get_lockfile_fd() const {
	return (this->_lockfile_fd);
}

Result<int>	Server::open_lockfile() {
	int	lock_fd;

	lock_fd = open(Server::lockfile_fullpath.c_str(), O_CREAT, O_EXCL, O_RDWR);
	if (lock_fd < 0) {
		if (errno == EEXIST) {

		} else {
			return (Result<int>::Err("file already exists"));
		}
	}
	return (Result<int>::Ok(lock_fd));
}

void	Server::delete_lockfile() {

}

int	Server::lock_lockfile() const {

}

int	Server::unlock_lockfile() const {

}
