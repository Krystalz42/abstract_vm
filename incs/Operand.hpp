//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <avm/AvmModels.hpp>
#include <iostream>
#include <cmath>
#include <regex>
#include "IOperand.hpp"
#include "AvmException.hpp"

template<typename T>
class Operand : virtual public IOperand {
private:

	T _value;
	eOperandType _type;
	std::string const _value_string;
	int _precision;
	AvmModels am;


public:
	Operand() = delete;

	explicit Operand(IOperand const *);

	Operand(Operand const &o);

	Operand(eOperandType, std::string const &);

	int getPrecision() const final;

	eOperandType getType() const final;

	Operand &operator=(Operand const &io);

	bool operator==(IOperand const &rhs) const final;

	bool operator!=(IOperand const &rhs) const final;

	bool operator<(IOperand const &rhs) const final;

	bool operator>(IOperand const &rhs) const final;

	bool operator<=(IOperand const &rhs) const final;

	bool operator>=(IOperand const &rhs) const final;

	const IOperand *operator+(IOperand const &io) const final;

	const IOperand *operator-(IOperand const &io) const final;

	const IOperand *operator*(IOperand const &io) const final;

	const IOperand *operator/(IOperand const &io) const final;

	const IOperand *operator%(IOperand const &io) const final;

	const std::string &toString() const final;
};

/** Static **/
/** Constructor **/

template<typename T>
Operand<T>::Operand(eOperandType type, std::string const &s)
		:    _value(std::stod(s)),
			 _type(type),
			 _value_string(std::to_string(_value)) {
	std::regex rgx(R"([0-9]+\.([0-9]*[1-9]))");
	std::smatch match;

	if (std::regex_search(_value_string.begin(), _value_string.end(), match,
						  rgx))
		_precision = static_cast<int>(match[1].length());
	else
		_precision = 0;
}

template<typename T>
Operand<T>::Operand(IOperand const *io)
		: _value(std::stod(io->toString())),
		  _type(io->getType()),
		  _value_string(std::to_string(_value)),
		  _precision(io->getPrecision()) {
}


/** Public **/
template<typename T>
Operand<T>::Operand(Operand const &o)
		: _value(o._value),
		  _type(o._type),
		  _value_string(o._value_string),
		  _precision(o._precision) {
	*this = o;
}

template<typename T>
int Operand<T>::getPrecision() const {
	return _precision;
}

template<typename T>
eOperandType Operand<T>::getType() const {
	return _type;
}

template<typename T>
const std::string &Operand<T>::toString() const {
	return _value_string;
}
/** Private **/
/** Operator **/

template<typename T>
const IOperand *Operand<T>::operator+(IOperand const &io) const {
	double d = std::stod(io.toString()) + _value;
	return am.createOperand((_type > io.getType() ? _type : io.getType()),
							std::to_string(d));
}

template<typename T>
const IOperand *Operand<T>::operator-(IOperand const &io) const {
	double d = std::stod(io.toString()) - _value;
	return am.createOperand((_type > io.getType() ? _type : io.getType()),
							std::to_string(d));
}

template<typename T>
const IOperand *Operand<T>::operator*(IOperand const &io) const {
	double d = std::stod(io.toString()) * _value;
	return am.createOperand((_type > io.getType() ? _type : io.getType()),
							std::to_string(d));
}

template<typename T>
const IOperand *Operand<T>::operator/(IOperand const &io) const {
	if (_value == 0)
		throw AvmException::Runtime("div : divide by 0");
	double d = std::stod(io.toString()) / _value;
	return am.createOperand((_type > io.getType() ? _type : io.getType()),
							std::to_string(d));
}

template<typename T>
const IOperand *Operand<T>::operator%(IOperand const &io) const {
	if (_value == 0)
		throw AvmException::Runtime("mod : modulo by 0");
	return am.createOperand((_type > io.getType() ? _type : io.getType()),
							std::to_string(std::fmod(_value, std::stod(
									io.toString()))));
}

template<typename T>
bool Operand<T>::operator<(IOperand const &rhs) const {
	return _value < std::stod(rhs.toString());
}

template<typename T>
bool Operand<T>::operator>(IOperand const &rhs) const {
	return _value > std::stod(rhs.toString());
}

template<typename T>
bool Operand<T>::operator<=(IOperand const &rhs) const {
	return _value <= std::stod(rhs.toString());
}

template<typename T>
bool Operand<T>::operator>=(IOperand const &rhs) const {
	return _value >= std::stod(rhs.toString());
}

template<typename T>
bool Operand<T>::operator==(IOperand const &rhs) const {
	return _value == std::stod(rhs.toString());
}

template<typename T>
bool Operand<T>::operator!=(IOperand const &rhs) const {
	return _value != std::stod(rhs.toString());
}

template<typename T>
Operand<T> &Operand<T>::operator=(Operand const &io) {
	if (this != &io) {
		_value = io._value;
		_type = io._type;
		_value_string = io._value_string;
	}
	return *this;
}


/** Destructor **/


#endif //AVM_OPERAND_HPP
