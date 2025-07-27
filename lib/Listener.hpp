#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "../lib/Error.hpp"
#include "IPollable.hpp"
#include <memory>
#include <optional>
#include <sys/socket.h>

class Server;

class Listener : public IPollable {
  public:
	Listener();
	Listener(Server *server_instance, std::string &host, std::string &port);
	Listener(const Listener &cpy) noexcept(false) = delete;
	Listener(Listener &&rhs) noexcept(false) = delete;
	Listener &operator=(const Listener &rhs) noexcept(false) = delete;
	~Listener();

	[[nodiscard]] int                  get_fd(void) const override;
	[[nodiscard]] std::optional<Error> handle_poll(void) noexcept override;
	[[nodiscard]] bool                 resolve_addr(
	                    struct sockaddr_storage *result, std::string const &host
	                ) noexcept;
	[[nodiscard]] std::optional<Error> listen() noexcept;

  protected:
	int         _fd;
	Server     *_server_instance;
	std::string _host;
	std::string _port;
};

#endif // !_LISTENER_H_
