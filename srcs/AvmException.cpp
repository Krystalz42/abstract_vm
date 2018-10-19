//
// Created by Alexandre ROULIN on 17/10/2018.
//
//
#include <AvmException.hpp>

/** Parsing **/

AvmException::Parsing::Parsing(char const *what) noexcept
		: std::invalid_argument(what),
		  _what(what) {
}

AvmException::Parsing::Parsing(AvmException::Parsing const &e) noexcept
		: std::invalid_argument(e._what),
		  _what(e._what) {

}

AvmException::Parsing &
AvmException::Parsing::operator=(const AvmException::Parsing &e) {
	if (this != &e) {
		_what = e._what;
	}
	return *this;
}

/** StackError **/

AvmException::StackError::StackError(char const *what) noexcept
		: std::logic_error(what),
		  _what(what) {

}

AvmException::StackError::StackError(AvmException::StackError const &e) noexcept
		: std::logic_error(e._what),
		  _what(e._what) {

}


/** Overflow **/

AvmException::Overflow::Overflow(char const *what) noexcept
		: std::overflow_error(what),
		  _what(what) {

}

AvmException::Overflow::Overflow(const AvmException::Overflow &e) noexcept
		: std::overflow_error(e._what),
		  _what(e._what) {

}

AvmException::Overflow &
AvmException::Overflow::operator=(const AvmException::Overflow &e) {
	if (this != &e) {
		_what = e._what;
	}
	return *this;
}

/** Undeflow**/

AvmException::Underflow::Underflow(char const *what) noexcept
		: std::underflow_error(what),
		  _what(what) {

}

AvmException::Underflow::Underflow(const AvmException::Underflow &e) noexcept
		: std::underflow_error(e._what),
		  _what(e._what) {

}

AvmException::Underflow &
AvmException::Underflow::operator=(const AvmException::Underflow &e) {
	if (this != &e) {
		_what = e._what;
	}
	return *this;
}

/** AvmError **/

AvmException::AvmError::AvmError(char const *what) noexcept
		: _what(what) {

}

AvmException::AvmError::AvmError(const AvmException::AvmError &e) noexcept
		: _what(e._what) {

}

AvmException::AvmError &
AvmException::AvmError::operator=(const AvmException::AvmError &e) {
	if (this != &e) {
		_what = e._what;
	}
	return *this;
}

/** Runtime **/

AvmException::Runtime::Runtime(char const *what) noexcept
		: std::runtime_error(what),
		  _what(what) {

}


AvmException::Runtime::Runtime(const AvmException::Runtime &e) noexcept
		: std::runtime_error(e._what),
		  _what(e._what) {

}

AvmException::Runtime &
AvmException::Runtime::operator=(const AvmException::Runtime &e) {
	if (this != &e) {
		_what = e._what;
	}
	return *this;
}