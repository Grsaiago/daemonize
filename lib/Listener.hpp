#ifndef _LISTENER_H_
# define _LISTENER_H_

# include "IPollable.hpp"
# include <iostream>

class Listener: public IPollable {
public:
	Listener();
	Listener(const Listener &cpy);
	~Listener();

	Listener &operator=(const Listener &rhs);

	int	get_fd(void) const override;
	int	handle_poll(void) noexcept override;
private:
	int	_fd;
};

#endif // !_LISTENER_H_
