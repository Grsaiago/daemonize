#ifndef _APOLLABLE_H_
# define _APOLLABLE_H_

class IPollable {
public:
	IPollable() = default;
	virtual ~IPollable() = default;
	virtual int	get_fd(void) const = 0;
	virtual int	handle_poll(void) = 0;
};

#endif // !_APOLLABLE_H_
