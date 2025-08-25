#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "IPollable.hpp"
#include <optional>
#include <sys/epoll.h>

class Client : public IPollable {
  public:
	Client() = delete;
	Client(int fd);
	Client(const Client &cpy);
	~Client();

	Client &operator=(const Client &rhs);

	int                                get_fd(void) const noexcept override;
	[[nodiscard]] std::optional<Error> handle_poll(
	    struct epoll_event ev
	) noexcept override;
	[[nodiscard]] struct epoll_event get_events_of_interest(
	    void
	) const noexcept override;

  private:
	int _fd;
};

#endif // !_CLIENT_H_
