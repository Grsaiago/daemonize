#ifndef _SERVER_H_
# define _SERVER_H_

# include "../lib/Listener.hpp"
# include "../lib/Client.hpp"
# include <array>
# include <memory>
# include <cstdio>
# include <fcntl.h>
# include <cerrno>
# include "../lib/Error.hpp"

class Server {
public:
	Server();
	Server(const Server &cpy);
	~Server();

	Server &operator=(const Server &rhs);

	int	get_lockfile_fd() const;

	static const std::string lockfile_path;
	static const std::string lockfile_name;
	static const std::string lockfile_fullpath;
private:
	int					_lockfile_fd;
	int					_epoll_fd;
	std::array<std::unique_ptr<Client>, 3>	_clients;
	Listener				_listener;

	Result<int>	open_lockfile();
	void		delete_lockfile();
	int		lock_lockfile() const;
	int		unlock_lockfile() const;
};

#endif // !_SERVER_H_
