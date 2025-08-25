#ifndef _APOLLABLE_H_
#define _APOLLABLE_H_

#include "Error.hpp"
#include <optional>
#include <sys/epoll.h>

class IPollable {
  public:
	IPollable() = default;
	virtual ~IPollable() = default;
	virtual int                get_fd(void) const noexcept = 0;
	virtual struct epoll_event get_events_of_interest(void) const noexcept = 0;
	virtual std::optional<Error> handle_poll(struct epoll_event ev) = 0;
};

#endif // !_APOLLABLE_H_
