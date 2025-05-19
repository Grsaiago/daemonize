#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>

class Server {
public:
	Server();
	~Server();

	int	get_lockfile_fd() const;
	void	set_lockfile_fd(int new_fd);

	static const std::string lockfile_path;
	static const std::string lockfile_name;
private:
	int	lockfile_fd;

	int	open_lockfile();
	void	delete_lockfile();
	int	lock_lockfile() const;
	int	unlock_lockfile() const;
};

#endif // !SERVER_HPP
