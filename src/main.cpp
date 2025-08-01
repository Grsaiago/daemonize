#include "../lib/DaemonManager.hpp"
#include "../lib/Server.hpp"
#include "../lib/logging/Logger.hpp"
#include "../lib/logging/TinTinReporter.hpp"
#include <exception>
#include <iostream>
#include <memory>
#include <new>

int main() {
	Logger::init_with_level(LogLevel::INFO, std::make_unique<TinTinReporter>());
	std::string                    host = "0.0.0.0";
	std::string                    port = "4242";
	Server                        *server = nullptr;
	std::unique_ptr<DaemonManager> daemon_manager = nullptr;
	std::string                    input;

	try {
		daemon_manager = std::make_unique<DaemonManager>();
		server = Server::install_new_default_server(host, port);
	} catch (const std::exception &err) {
		Err(err.what());
		return EXIT_FAILURE;
	}

	Info("Essa string aqui");
	std::getline(std::cin, input);

	std::string message = "Starting server on " + host + ":" + port;
	if (auto result = server->listen_and_serve(message); result.has_value()) {
		Err("failed to start server: %s", result.value().reason.c_str());
		delete server;
	}
	delete server;
	return EXIT_SUCCESS;
}
