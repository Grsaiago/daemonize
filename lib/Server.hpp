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
# include <string>
# include <sys/epoll.h>

class Server {
public:
	[[nodiscard]]	static Server *const	get_instance() noexcept;
	~Server() noexcept(false);

	[[nodiscard]] int		get_lockfile_fd() const;

	static const std::string	lockfile_path;
	static const std::string	lockfile_name;
	static const std::string	lockfile_fullpath;

	[[nodiscard]] static bool		lockfile_exists() noexcept;
	[[nodiscard]] std::optional<Error>	listen_and_serve() noexcept;
private:
	Server(const Server &cpy) noexcept(false);
	Server() noexcept(false);
	Server &operator=(const Server &rhs);

	int					_lockfile_fd;
	int					_epoll_fd;
	std::array<std::optional<Client>, 3>	_clients;
	Listener				_listener;
	static Server				*_instance;

	[[nodiscard]] std::optional<Error>	open_lockfile();
	[[nodiscard]] std::optional<Error>	close_lockfile();
};

#endif // !_SERVER_H_
