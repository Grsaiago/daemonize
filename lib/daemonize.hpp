#include "Error.hpp"
#include <optional>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

std::optional<Error>	daemonize(void) noexcept;
