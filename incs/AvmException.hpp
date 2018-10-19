//
// Created by Alexandre ROULIN on 17/10/2018.
//

#ifndef AVM_AVMEXCEPTION_HPP
#define AVM_AVMEXCEPTION_HPP

#include <exception>
#include <stdexcept>

class AvmException {
public:
	class Parsing : virtual public std::invalid_argument {
	private:
		const char *_what;
	public:
		Parsing() = delete;

		Parsing(Parsing const &) noexcept;

		Parsing &operator=(Parsing const &);

		explicit Parsing(char const *what) noexcept;
	};

	class StackError : virtual public std::logic_error {
	private:
		const char *_what;
	public:
		StackError() = delete;

		StackError(StackError const &) noexcept;

		StackError &operator=(StackError const &);

		explicit StackError(char const *what) noexcept;

	};

	class AvmError : virtual public std::exception {
	private:
		const char *_what;
	public:
		AvmError(AvmError const &) noexcept;

		AvmError &operator=(AvmError const &);

		AvmError() = delete;


		explicit AvmError(char const *what) noexcept;

	};

class Overflow : virtual public std::overflow_error {
	private:
		const char *_what;
	public:
		Overflow() = delete;

		Overflow(Overflow const &) noexcept;

		Overflow &operator=(Overflow const &);

		explicit Overflow(char const *what) noexcept;

	};

	class Underflow : virtual public std::underflow_error {
	private:
		const char *_what;
	public:
		Underflow() = delete;

		Underflow(Underflow const &) noexcept;

		Underflow &operator=(Underflow const &);

		explicit Underflow(char const *what) noexcept;

	};
	class Runtime : virtual public std::runtime_error {
	private:
		const char *_what;
	public:
		Runtime() = delete;

		Runtime(Runtime const &) noexcept;

		Runtime &operator=(Runtime const &);

		explicit Runtime(char const *what) noexcept;

	};

};

#endif //AVM_AVMEXCEPTION_HPP
