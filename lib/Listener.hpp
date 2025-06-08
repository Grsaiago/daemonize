#ifndef _LISTENER_H_
# define _LISTENER_H_

# include "IPollable.hpp"
# include "../lib/Error.hpp"
# include <iostream>
# include <optional>

class Listener: public IPollable {
public:
	Listener();
	Listener(const Listener &cpy) noexcept(false) = delete;
	~Listener();

	Listener &operator=(const Listener &rhs) noexcept(false) = delete;

	int			get_fd(void) const override;
	std::optional<Error>	handle_poll(void) noexcept override;
private:
	int	_fd;
};

#endif // !_LISTENER_H_
