#ifndef _SERVER_H_
#define _SERVER_H_

#include "../lib/Client.hpp"
#include "../lib/Error.hpp"
#include "../lib/Listener.hpp"
#include <array>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <optional>
#include <sys/epoll.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

class Server {
  public:
	[[nodiscard]] static Server *get_instance(void) noexcept;
	~Server() noexcept(false);

	[[nodiscard]] std::optional<Error> listen_and_serve(
	    std::string &start_message
	) noexcept;
	[[nodiscard]] std::optional<Error> add_new_client(
	    Client &new_client
	) noexcept;
	static Server *install_new_default_server(
	    std::string &host, std::string &port
	) noexcept;

  private:
	Server(const Server &cpy) noexcept(false) = delete;
	Server() noexcept(false);
	Server &operator=(const Server &rhs) = delete;
	Server(Listener &_listener) noexcept(false) = delete;

	[[nodiscard]] std::optional<Error> event_loop(void) noexcept;

	int                                  _epoll_fd;
	std::array<std::optional<Client>, 3> _clients;
	Listener                            *_listener;
	static Server                       *_instance;
};

#endif // !_SERVER_H_
