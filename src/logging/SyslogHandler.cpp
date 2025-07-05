#include "../../lib/logging/SyslogHandler.hpp"
#include <sys/syslog.h>

SyslogReporter::SyslogReporter() {
	openlog("matt_daemon", LOG_NDELAY | LOG_PID, LOG_USER);
}

SyslogReporter::~SyslogReporter() { closelog(); }

void SyslogReporter::debug_handler(LogEvent event) noexcept {
	syslog(LOG_DEBUG, "%s", event.message.c_str());
}

void SyslogReporter::info_handler(LogEvent event) noexcept {
	syslog(LOG_INFO, "%s", event.message.c_str());
}

void SyslogReporter::warn_handler(LogEvent event) noexcept {
	syslog(LOG_WARNING, "%s", event.message.c_str());
}

void SyslogReporter::error_handler(LogEvent event) noexcept {
	syslog(LOG_ERR, "%s", event.message.c_str());
}
