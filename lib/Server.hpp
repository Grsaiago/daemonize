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
# include <string>

class Server {
public:
	Server() noexcept(false);
	Server(const Server &cpy) noexcept(false);
	~Server() noexcept(false);

	Server &operator=(const Server &rhs);

	[[nodiscard]] int	get_lockfile_fd() const;

	static const std::string lockfile_path;
	static const std::string lockfile_name;
	static const std::string lockfile_fullpath;

	[[nodiscard]] static std::optional<Error>	daemonize(void) noexcept;
private:
	int					_lockfile_fd;
	int					_epoll_fd;
	std::array<std::optional<Client>, 3>	_clients;
	Listener				_listener;

	[[nodiscard]] std::optional<Error>	open_lockfile();
	[[nodiscard]] std::optional<Error>	close_lockfile();
};

#endif // !_SERVER_H_
