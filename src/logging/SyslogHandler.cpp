#include "../../lib/logging/SyslogHandler.hpp"
#include <sys/syslog.h>

SyslogReporter::SyslogReporter() {
	openlog("matt_daemon", LOG_NDELAY | LOG_PID, LOG_USER);
	(void)setlogmask(LOG_INFO);
	return;
}

SyslogReporter::SyslogReporter(LogLevel level) {
	int syslog_level = 0;

	switch (level) {
	case LogLevel::DEBUG:
		syslog_level |= LOG_DEBUG;
		[[fallthrough]];
	case LogLevel::INFO:
		syslog_level |= LOG_INFO;
		[[fallthrough]];
	case LogLevel::WARN:
		syslog_level |= LOG_WARNING;
		[[fallthrough]];
	case LogLevel::ERROR:
		syslog_level |= LOG_ERR;
	}

	openlog("matt_daemon", LOG_NDELAY | LOG_PID, LOG_USER);
	(void)setlogmask(syslog_level);
	return;
}

SyslogReporter::~SyslogReporter() { closelog(); }

void SyslogReporter::debug_handler(LogEvent event) noexcept {
	syslog(LOG_DEBUG, "%s", event.message.c_str());
	return;
}

void SyslogReporter::info_handler(LogEvent event) noexcept {
	syslog(LOG_INFO, "%s", event.message.c_str());
	return;
}

void SyslogReporter::warn_handler(LogEvent event) noexcept {
	syslog(LOG_WARNING, "%s", event.message.c_str());
	return;
}

void SyslogReporter::error_handler(LogEvent event) noexcept {
	syslog(LOG_ERR, "%s", event.message.c_str());
	return;
}
