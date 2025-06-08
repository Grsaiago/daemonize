#include "../lib/DaemonManager.hpp"

const std::string DaemonManager::lockfile_path = std::string("/var/lock/");
const std::string DaemonManager::lockfile_name = std::string("matt_daemon.lock");
const std::string DaemonManager::lockfile_fullpath = DaemonManager::lockfile_path + DaemonManager::lockfile_name;

DaemonManager::DaemonManager() noexcept(false) {
	auto result = this->open_lockfile();
	if (result.has_value()) {
		throw std::logic_error(result.value().reason);
	}
}

DaemonManager::~DaemonManager() noexcept(false) {
	auto result = this->close_lockfile();
	if (result.has_value()) {
		throw std::logic_error(result.value().reason);
	}
}

std::optional<Error>	DaemonManager::open_lockfile() {
	// create file
	this->_lockfile_fd = open(
		DaemonManager::lockfile_fullpath.c_str(),
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

std::optional<Error>	DaemonManager::close_lockfile() {
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
	if (unlink(DaemonManager::lockfile_fullpath.c_str()) != 0) {
		return (std::optional<Error>(strerror(errno)));
	}
	return (std::nullopt);
}


int	DaemonManager::get_lockfile_fd() const noexcept {
	return this->_lockfile_fd;
}

bool	DaemonManager::lockfile_exists() noexcept {
	return (access(DaemonManager::lockfile_fullpath.c_str(), F_OK) == 0);
}

/*
 * Make the process a daemon as described in the chapter 37.2 (creating a daemon) of the "The Linux Programming Interface"
 * */
std::optional<Error>	DaemonManager::daemonize(void) const noexcept {
	int	dev_null_fd;

	switch (fork()) {
		case (0): break;
		case (-1): return std::optional<Error>(std::string("error on first fork:") + strerror(errno));
		default: exit(0);
	}
	if (setsid() == -1) {
		return std::optional<Error>(strerror(errno));
	}
	/* Ensure we're not session a leader with this second fork,
	 * in case of the process acquiries a device and so the acquired device
	 * is not set as the controlling terminal
	 */
	switch (fork()) {
		case (0): break;
		case (-1): return (std::optional<Error>(std::string("error on second fork:") + strerror(errno)));
		default: exit(0);
	}
	/*
	 * change the process' mask and it's cwd to "/"
	 * to avoid blocking the system from unmounting any dirs.
	 */
	umask(0);
	if (chdir("/") != 0) {
		return (std::optional<Error>(strerror(errno)));
	}
	/*
	 * Close all standard io fds and redirect them to /dev/null
	 */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	dev_null_fd = open("/dev/null", O_RDWR);
	if (dev_null_fd != 0) {
		return (std::optional<Error>(strerror(errno)));
	}
	if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) {
		return (std::optional<Error>(strerror(errno)));
	}
	if (dup2(STDOUT_FILENO, STDIN_FILENO) != STDIN_FILENO) {
		return (std::optional<Error>(strerror(errno)));
	}
	return (std::nullopt);
}
