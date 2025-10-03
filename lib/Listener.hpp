#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "../lib/Error.hpp"
#include "IPollable.hpp"
#include <optional>
#include <sys/socket.h>

class Server;
class Client;

class Listener : public IPollable {
  public:
	Listener();
	Listener(
	    Server *server_instance, const std::string &host,
	    const std::string &port
	);
	Listener(const Listener &cpy) noexcept(false) = delete;
	Listener(Listener &&rhs) noexcept(false) = delete;
	Listener &operator=(const Listener &rhs) noexcept(false) = delete;
	~Listener();

	[[nodiscard]] int                  get_fd(void) const noexcept override;
	[[nodiscard]] std::optional<Error> handle_poll(
	    struct epoll_event ev
	) noexcept override;
	[[nodiscard]] struct epoll_event get_events_of_interest(
	    void
	) const noexcept override;
	[[nodiscard]] bool resolve_addr(
	    struct sockaddr_storage *result, std::string const &host
	) noexcept;

	[[nodiscard]] std::optional<Error> listen(void) noexcept;
	[[nodiscard]] int                  accept_new_client(void) noexcept;

  protected:
	int         _fd;
	Server     *_server_instance;
	std::string _host;
	std::string _port;
};

#endif // !_LISTENER_H_
