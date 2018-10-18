//
// Created by Alexandre ROULIN on 17/10/2018.
//

#ifndef AVM_AVMEXCEPTION_HPP
#define AVM_AVMEXCEPTION_HPP

#include <exception>

class AvmException {
public:
	class Parsing : virtual public std::exception {
	private:
		const char *_what;
	public:
		Parsing() = delete;

		Parsing(Parsing const &) noexcept;

		Parsing &operator=(Parsing const &) = delete;

		explicit Parsing(char const *what) noexcept;

		const char *what() const noexcept final;
	};

	class StackError : virtual public std::exception {
	private:
		const char *_what;
	public:
		StackError() = delete;

		StackError(StackError const &) noexcept;

		StackError &operator=(StackError const &) = delete;

		explicit StackError(char const *what) noexcept;

		const char *what() const noexcept final;
	};

	class AvmError : virtual public std::exception {
	private:
		const char *_what;
	public:
		AvmError(AvmError const &) noexcept;

		AvmError &operator=(AvmError const &) = delete;

		AvmError() = delete;


		explicit AvmError(char const *what) noexcept;

		const char *what() const noexcept final;
	};

	class Overflow : virtual public std::exception {
	private:
		const char *_what;
	public:
		Overflow() = delete;

		Overflow(Overflow const &) noexcept;

		Overflow &operator=(Overflow const &) = delete;

		explicit Overflow(char const *what) noexcept;

		const char *what() const noexcept final;
	};

	class Underflow : virtual public std::exception {
	private:
		const char *_what;
	public:
		Underflow() = delete;

		Underflow(Underflow const &) noexcept;

		Underflow &operator=(Underflow const &) = delete;

		explicit Underflow(char const *what) noexcept;

		const char *what() const noexcept final;
	};
	class Runtime : virtual public std::exception {
	private:
		const char *_what;
	public:
		Runtime() = delete;

		Runtime(Runtime const &) noexcept;

		Runtime &operator=(Runtime const &) = delete;

		explicit Runtime(char const *what) noexcept;

		const char *what() const noexcept final;
	};

};

#endif //AVM_AVMEXCEPTION_HPP
