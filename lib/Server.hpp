#ifndef _SERVER_H_
# define _SERVER_H_

# include "../lib/Listener.hpp"
# include "../lib/Client.hpp"
# include <memory>
# include <vector>

class Server {
public:
	Server();
	~Server();

	int	get_lockfile_fd() const;
	void	set_lockfile_fd(int new_fd);

	static const std::string lockfile_path;
	static const std::string lockfile_name;
private:
	int					_lockfile_fd;
	int					_epoll_fd;
	std::vector<std::unique_ptr<Client>>	_clients;
	Listener				_listener;

	int	open_lockfile();
	void	delete_lockfile();
	int	lock_lockfile() const;
	int	unlock_lockfile() const;
};

#endif // !_SERVER_H_
