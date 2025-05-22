#ifndef _LISTENER_H_
# define _LISTENER_H_

# include "APollable.hpp"
# include <iostream>

class Listener: public APollable {
public:
	Listener();
	~Listener();

	int get_fd(void) const override;
private:
	int	_fd;
};

#endif // !_LISTENER_H_
