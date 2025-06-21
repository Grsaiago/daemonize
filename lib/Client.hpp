#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "IPollable.hpp"
#include <optional>

class Client : public IPollable {
  public:
	Client() = delete;
	Client(int fd);
	Client(const Client &cpy);
	~Client();

	Client &operator=(const Client &rhs);

	int get_fd(void) const noexcept override;
	std::optional<Error> handle_poll(void) noexcept override;

  private:
	int _fd;
};

#endif // !_CLIENT_H_
