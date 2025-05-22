#ifndef _CLIENT_H_
# define _CLIENT_H_

# include "APollable.hpp"

class Client: public APollable {
public:
	Client() = delete;
	~Client();
	Client(int fd);

	int get_fd(void) const override;
private:
	int	_fd;
};

#endif // !_CLIENT_H_
