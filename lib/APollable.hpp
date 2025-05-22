#ifndef _APOLLABLE_H_
# define _APOLLABLE_H_


class APollable {
public:
	APollable() = default;
	virtual ~APollable() = default;
	virtual int	get_fd(void) const = 0;
};

#endif // !_APOLLABLE_H_
