#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "../lib/Error.hpp"
#include "IPollable.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <sys/socket.h>

class Server;

class Listener : public IPollable {
  public:
	Listener() = delete;
	Listener(std::shared_ptr<Server> server_instance);
	Listener(const Listener &cpy) noexcept(false) = delete;
	Listener(Listener &&rhs) noexcept(false) = delete;
	Listener &operator=(const Listener &rhs) noexcept(false) = delete;
	~Listener();

	int                  get_fd(void) const override;
	std::optional<Error> handle_poll(void) noexcept override;
	static bool          resolve_addr(
	             struct sockaddr_storage *result, std::string const &host
	         ) noexcept;

  private:
	int                   _fd;
	std::weak_ptr<Server> _server_instance;
};

#endif // !_LISTENER_H_
