#include "../lib/Server.hpp"

const std::string Server::lockfile_path = std::string("/var/lock/");
const std::string Server::lockfile_name = Server::lockfile_path + std::string("matt_daemon.lock");

Server::Server(): _lockfile_fd(-1), _epoll_fd(-1) {}

Server::~Server() {}
