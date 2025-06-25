#include "../../lib/logging/logging_utils.hpp"

std::string get_formatted_message(std::string fmessage, va_list args) {
	va_list args_cpy;
	int     total_len;

	va_copy(args_cpy, args);
	total_len = vsnprintf(NULL, 0, fmessage.c_str(), args_cpy);
	std::vector<char> message_buffer(total_len + 1);
	va_end(args_cpy);

	va_copy(args_cpy, args);
	total_len = vsnprintf(
	    message_buffer.data(), message_buffer.size(), fmessage.c_str(), args_cpy
	);
	va_end(args_cpy);

	return (std::string(message_buffer.begin(), message_buffer.end()));
}
