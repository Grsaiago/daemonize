#ifndef _DAEMON_MANAGER_H_
# define _DAEMON_MANAGER_H_

# include "../lib/Error.hpp"
# include <optional>
# include <cstdio>
# include <cstring>
# include <cerrno>
# include <unistd.h>
# include <fcntl.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <string>
# include <stdexcept>

class DaemonManager {
public:
	DaemonManager() noexcept(false);
	DaemonManager(const DaemonManager &cpy) noexcept(false) = delete;
	~DaemonManager() noexcept(false);

	DaemonManager &operator=(const DaemonManager &rhs) noexcept(false) = delete;

	[[nodiscard]] int		get_lockfile_fd() const noexcept;

	[[nodiscard]] static bool		lockfile_exists() noexcept;
	[[nodiscard]] std::optional<Error>	daemonize(void) const noexcept;
	static const std::string	lockfile_path;
	static const std::string	lockfile_name;
	static const std::string	lockfile_fullpath;
private:
	int					_lockfile_fd;

	[[nodiscard]] std::optional<Error>	open_lockfile();
	[[nodiscard]] std::optional<Error>	close_lockfile();
};

#endif // !_DAEMON_MANAGER_H_
