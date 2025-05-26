#ifndef _RESULT_H_
# define _RESULT_H_
# include <string>


class Error {
public:
	Error(std::string reason) : reason(reason) {}
	const std::string	reason;
};

enum class ResultStates {
	Ok,
	Err
};

template <typename T>
class Result {
public:
	static Result	Ok(T value);
	static Result	Err(std::string reason);

	~Result();

	bool	is_ok(void) const noexcept;
	bool	is_err(void) const noexcept;
	T	get_ok() noexcept(false);
	Error	get_err() noexcept(false);
private:
	Result();
	ResultStates	current_state;
	union {
		T	ok;
		Error	err;
	} current_value;
};

#endif // _RESULT_H_
