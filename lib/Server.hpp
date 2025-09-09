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

	[[nodiscard]] const std::array<std::optional<Client>, 3> &get_clients(
	    void
	) const noexcept;

	static Server *install_new_default_server(
	    const std::string &host, const std::string &port
	) noexcept;
	[[nodiscard]] std::optional<Error> listen_and_serve(
	    std::string &start_message
	) noexcept;
	[[nodiscard]] int get_active_client_count(void) const noexcept;
	[[nodiscard]] std::optional<Error> add_new_client(
	    Client &new_client
	) noexcept;
	[[nodiscard]] std::optional<Error> remove_client(int pos) noexcept;

  private:
	Server(const std::string &host, const std::string &port) noexcept(false);
	Server(const Server &cpy) noexcept(false) = delete;
	Server &operator=(const Server &rhs) = delete;
	Server(Listener &_listener) noexcept(false) = delete;

	[[nodiscard]] std::optional<Error> event_loop(void) noexcept;

	bool                                 _should_run;
	int                                  _epoll_fd;
	std::array<std::optional<Client>, 3> _clients;
	std::array<struct epoll_event, 4>    _pollables;
	Listener                            *_listener;
	static Server                       *_instance;
};

#endif // !_SERVER_H_
