#ifndef _RESULT_H_
#define _RESULT_H_
#include <string>

class Error {
  public:
	Error(std::string reason) : reason(reason) {}
	const std::string reason;
};

#endif // _RESULT_H_
