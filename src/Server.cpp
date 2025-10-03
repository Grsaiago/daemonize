#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include <array>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <optional>
#include <sys/epoll.h>

static void signal_handler(int signum) noexcept;

Server *Server::_instance = nullptr;

Server *Server::install_new_default_server(
    const std::string &host, const std::string &port
) {
	if (Server::_instance == nullptr) {
		Server::_instance = new Server(host, port);
	}
	return (Server::_instance);
}

Server *Server::get_instance(void) noexcept {
	if (Server::_instance == nullptr) {
		Server::_instance = new (std::nothrow) Server("127.0.0.1", "4242");
	}
	return (Server::_instance);
}

const std::array<std::optional<Client>, 3> &Server::get_clients(
    void
) const noexcept {
	return this->_clients;
}

Server::Server(const std::string &host, const std::string &port) noexcept(false)
    : _should_run(true), _epoll_fd(-1), _clients(), _listener() {
	this->_listener = new Listener(this, host, port);
	return;
}

Server::~Server() noexcept(false) {
	if (this->_epoll_fd != -1) {
		close(this->_epoll_fd);
	}
	delete this->_listener;
	return;
}

std::optional<Error> Server::listen_and_serve(
    std::string &start_message
) noexcept {
	struct epoll_event listener_events_of_interest =
	    this->_listener->get_events_of_interest();
	this->_epoll_fd = epoll_create(4);
	if (this->_epoll_fd == -1) {
		return (std::optional<Error>(strerror(errno)));
	}
	if (std::optional<Error> listen_return = this->_listener->listen();
	    listen_return.has_value()) {
		Err("error on listener listen call: %s", listen_return->reason.c_str());
		return (std::optional<Error>(listen_return->reason));
	}
	if (epoll_ctl(
	        this->_epoll_fd, EPOLL_CTL_ADD, this->_listener->get_fd(),
	        &listener_events_of_interest
	    ) == -1) {
		Err("error on adding listener to epoll instance: %s", strerror(errno));
		return (std::optional<Error>(strerror(errno)));
	}
	Info(start_message.c_str());
	return (this->event_loop());
}

int Server::get_active_client_count(void) const noexcept {
	int count = 0;
	for (auto &it : this->_clients) {
		if (it.has_value()) {
			count++;
		}
	}
	return (count);
}

std::optional<Error> Server::add_new_client(int new_client) noexcept {
	if (this->get_active_client_count() >= 3) {
		return (std::optional<Error>("maximum number of clients reached"));
	}
	for (auto &it : this->_clients) {
		if (it.has_value()) {
			continue;
		}
		it.emplace(new_client);
		struct epoll_event client_events_of_interest =
		    it.value().get_events_of_interest();
		if (epoll_ctl(
		        this->_epoll_fd, EPOLL_CTL_ADD, it.value().get_fd(),
		        &client_events_of_interest
		    ) == -1) {
			Err("error on adding new client to epoll instance: %s",
			    strerror(errno));
			it.reset();
			return (std::optional<Error>(strerror(errno)));
		}
		Debug(
		    "new client added, current active clients: %d",
		    this->get_active_client_count()
		);
		return (std::nullopt);
	}
	return (std::nullopt);
}

std::optional<Error> Server::remove_client(int pos) noexcept {
	if (pos < 0 || pos >= 3) {
		return std::optional<Error>(
		    "out of range position for deleting client"
		);
	}
	std::optional<Client> &marked_for_deletion = this->_clients[pos];
	if (!marked_for_deletion.has_value()) {
		return std::optional<Error>(
		    "the position passed for deletion currently has no active Client"
		);
	}
	if (epoll_ctl(
	        this->_epoll_fd, EPOLL_CTL_DEL, marked_for_deletion->get_fd(), NULL
	    ) == -1) {
		Err("failed to delete Client at position %d: %s", pos, strerror(errno));
	}
	marked_for_deletion.reset();
	return (std::nullopt);
}

void Server::install_signal_handlers() noexcept {
	std::signal(SIGTERM, signal_handler);
	return;
}

void Server::set_should_run(bool val) noexcept {
	this->_should_run = val;
	return;
}

std::optional<Error> Server::event_loop(void) noexcept {
	int                  ev_count = 0;
	struct epoll_event  *ev = nullptr;
	std::optional<Error> err;

	while (this->_should_run) {
		Debug("checking/waiting for new events");
		ev_count = epoll_wait(
		    this->_epoll_fd, this->_pollables.data(), this->_pollables.size(),
		    -1
		);
		if (ev_count == -1) {
			if (errno == EINTR) {
				continue;
			}
			Err("error on checking/waiting for new events", strerror(errno));
			return (std::optional<Error>(strerror(errno)));
		}
		Debug("new events received, starting handle loop");
		for (int i = 0; i < ev_count; i++) {
			ev = &this->_pollables[i];

			Debug("handling event on position [%d]", i);
			err = reinterpret_cast<IPollable *>(ev->data.ptr)->handle_poll(*ev);
			if (err.has_value()) {
				Err("error calling handle_poll in epoll_event: %s",
				    err->reason.c_str());
				return (err);
			}
		}
	}
	Info("Shutting down server gracefully");
	return (std::nullopt);
}

static void signal_handler(int signum) noexcept {
	switch (signum) {
	case (SIGTERM):
		Server::get_instance()->set_should_run(false);
		Info("received SIGTERM, starting graceful shutdown");
		break;
	default:
		Err("received unexpected signal %s", strsignal(signum));
	}
	return;
}
