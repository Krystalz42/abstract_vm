//
// Created by Alexandre ROULIN on 17/10/2018.
//

#include <AvmException.hpp>

#include "AvmException.hpp"

/** Parsing **/

AvmException::Parsing::Parsing(char const *what) noexcept
		: _what(what) {

}

AvmException::Parsing::Parsing(const AvmException::Parsing &e) noexcept
		: _what(e._what) {

}

const char *AvmException::Parsing::what() const noexcept {
	return _what;
}

/** StackError **/

AvmException::StackError::StackError(char const *what) noexcept
		: _what(what) {

}

AvmException::StackError::StackError(const AvmException::StackError &e) noexcept
		: _what(e._what) {

}


const char *AvmException::StackError::what() const noexcept {
	return _what;
}

/** Overflow **/

AvmException::Overflow::Overflow(char const *what) noexcept
		: _what(what) {

}

AvmException::Overflow::Overflow(const AvmException::Overflow &e) noexcept
		: _what(e._what) {

}

const char *AvmException::Overflow::what() const noexcept {
	return _what;
}

/** Undeflow**/

AvmException::Underflow::Underflow(char const *what) noexcept
		: _what(what) {

}

AvmException::Underflow::Underflow(const AvmException::Underflow &e) noexcept
		: _what(e._what) {

}


const char *AvmException::Underflow::what() const noexcept {
	return _what;
}

/** AvmError **/

AvmException::AvmError::AvmError(char const *what) noexcept
		: _what(what) {

}

AvmException::AvmError::AvmError(const AvmException::AvmError &e) noexcept
		: _what(e._what) {

}


const char *AvmException::AvmError::what() const noexcept {
	return _what;
}

/** Runtime **/

AvmException::Runtime::Runtime(char const *what) noexcept
		: _what(what) {

}


AvmException::Runtime::Runtime(const AvmException::Runtime &e) noexcept
		: _what(e._what) {

}

const char *AvmException::Runtime::what() const noexcept {
	return _what;
}
