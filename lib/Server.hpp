#ifndef _SERVER_H_
# define _SERVER_H_

# include "../lib/Listener.hpp"
# include "../lib/Client.hpp"
# include "../lib/Error.hpp"
# include <array>
# include <optional>
# include <cstdio>
# include <cstring>
# include <cerrno>
# include <unistd.h>
# include <fcntl.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/epoll.h>

class Server {
public:
	[[nodiscard]]	static Server *const	get_instance() noexcept;
	~Server() noexcept(false);

	[[nodiscard]] uint8_t		get_active_clients() const noexcept;

	[[nodiscard]] std::optional<Error>	listen_and_serve() noexcept;
	[[nodiscard]] std::optional<Error>	add_new_client(Client &new_client) noexcept;
private:
	Server(const Server &cpy) noexcept(false);
	Server() noexcept(false);
	Server &operator=(const Server &rhs);

	int					_epoll_fd;
	std::array<std::optional<Client>, 3>	_clients;
	uint8_t					_active_clients;
	Listener				_listener;
	static Server				*_instance;
};

#endif // !_SERVER_H_
