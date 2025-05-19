#include "../lib/Server.hpp"

const std::string Server::lockfile_path = std::string("/var/lock/");
const std::string Server::lockfile_name = Server::lockfile_path + std::string("matt_daemon.lock");

Server::Server() {}

Server::~Server() {}
