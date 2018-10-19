//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <avm/AvmFactory.hpp>
#include <iostream>
#include <cmath>
#include <regex>
#include "IOperand.hpp"
#include "AvmException.hpp"
#include <sstream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <limits.h>
#include <float.h>
#include <cstring>

extern std::ofstream f;

template<typename T>
class Operand : virtual public IOperand {
private:

	eOperandType _type;
	T _value;
	std::string _value_string;
	int _precision;
	AvmFactory am;

public:
	Operand() = delete;

	explicit Operand(IOperand const *);

	Operand(Operand const &o);

	Operand(eOperandType, std::string const &);

	int getPrecision() const final;

	eOperandType getType() const final;

	Operand &operator=(Operand const &rhs);

	bool operator==(IOperand const &rhs) const final;

	bool operator!=(IOperand const &rhs) const final;

	bool operator<(IOperand const &rhs) const final;

	bool operator>(IOperand const &rhs) const final;

	bool operator<=(IOperand const &rhs) const final;

	bool operator>=(IOperand const &rhs) const final;

	const IOperand *operator+(IOperand const &rhs) const final;

	const IOperand *operator-(IOperand const &rhs) const final;

	const IOperand *operator*(IOperand const &rhs) const final;

	const IOperand *operator/(IOperand const &rhs) const final;

	const IOperand *operator%(IOperand const &rhs) const final;

	const std::string &toString() const final;
};

/** Static **/
/** Constructor **/

template<typename T>
Operand<T>::Operand(eOperandType type, std::string const &s) :
		_type(type) {
	std::stringstream ss(std::stringstream::out);
	std::regex rgx(R"([0-9]+\.([0-9]*[1-9]))");
	std::smatch match;

	if (type < FLOAT) {
		_precision = 0;
		long long ll = std::stoll(s);
		_value = static_cast<T>(ll);
		ss << ll;
		_value_string = ss.str();
	} else {
		long double ld = static_cast<T>(std::stold(s));
		std::regex_search(s.begin(), s.end(), match, rgx);
		_precision = static_cast<int>(match[1].length());
		_value = static_cast<T>(ld);
		ss << std::fixed << std::setprecision(_precision) << ld;
		_value_string = ss.str();
	}
//	f << _value_string << "  " << _precision <<	"  " << _value<<std::endl;
}

template<typename T>
Operand<T>::Operand(IOperand const *rhs)
		:_type(rhs->getType()),
		 _value(std::stod(rhs->toString())),
		 _value_string(std::to_string(_value)),
		 _precision(rhs->getPrecision()) {
}


template<typename T>
Operand<T>::Operand(Operand const &o)
		: _value(o._value),
		  _type(o._type),
		  _value_string(o._value_string),
		  _precision(o._precision) {
	*this = o;
}

/** Public **/

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
const IOperand *Operand<T>::operator+(IOperand const &rhs) const {
	eOperandType final_type = (_type > rhs.getType() ? _type : rhs.getType());
	int final_precision =
			(rhs.getPrecision() > _precision ? rhs.getPrecision() : _precision);
	std::stringstream ss(std::ostringstream::out);

	if (final_type < FLOAT) {
		long long i = std::stoll(_value_string) + std::stoll(rhs.toString());
		ss << i;
	} else {
		long double d = std::stold(_value_string) + std::stold(rhs.toString());
		ss << std::fixed << std::setprecision(final_precision) << d;
	}
	return am.createOperand(final_type, ss.str());
}

template<typename T>
const IOperand *Operand<T>::operator-(IOperand const &rhs) const {
	eOperandType final_type = (_type > rhs.getType() ? _type : rhs.getType());
	int final_precision =
			(rhs.getPrecision() > _precision ? rhs.getPrecision() : _precision);
	std::stringstream ss(std::ostringstream::out);

	if (final_type < FLOAT) {
		long long i = std::stoll(_value_string) - std::stoll(rhs.toString());
		ss << i;
	} else {
		long double d = std::stold(_value_string) - std::stold(rhs.toString());
		ss << std::fixed << std::setprecision(final_precision) << d;
	}
	return am.createOperand(final_type, ss.str());
}

template<typename T>
const IOperand *Operand<T>::operator*(IOperand const &rhs) const {
	eOperandType final_type = (_type > rhs.getType() ? _type : rhs.getType());
	int final_precision =
			(rhs.getPrecision() > _precision ? rhs.getPrecision() : _precision);
	std::stringstream ss(std::ostringstream::out);

	if (final_type < FLOAT) {
		long long i = std::stoll(_value_string) * std::stoll(rhs.toString());
		ss << i;
	} else {
		long double d = std::stold(_value_string) * std::stold(rhs.toString());
		ss << std::fixed << std::setprecision(final_precision) << d;
	}
	return am.createOperand(final_type, ss.str());
}

template<typename T>
const IOperand *Operand<T>::operator/(IOperand const &rhs) const {
	eOperandType final_type = (_type > rhs.getType() ? _type : rhs.getType());
	int final_precision =
			(rhs.getPrecision() > _precision ? rhs.getPrecision() : _precision);
	std::stringstream ss(std::ostringstream::out);

	if (final_type < FLOAT) {
		if (std::stoll(rhs.toString()) == 0)
			throw AvmException::Runtime("div : divide by 0");
		long long i = std::stoll(_value_string) / std::stoll(rhs.toString());
		ss << i;
	} else {
		if (std::stold(rhs.toString()) == 0)
			throw AvmException::Runtime("div : divide by 0");
		long double d = std::stold(_value_string) / std::stold(rhs.toString());
		ss << std::fixed << std::setprecision(final_precision) << d;
	}
	return am.createOperand(final_type, ss.str());
}

template<typename T>
const IOperand *Operand<T>::operator%(IOperand const &rhs) const {
	eOperandType final_type = (_type > rhs.getType() ? _type : rhs.getType());
	int final_precision =
			(rhs.getPrecision() > _precision ? rhs.getPrecision() : _precision);
	std::stringstream ss(std::ostringstream::out);

	if (final_type < FLOAT) {
		if (std::stoll(rhs.toString()) == 0)
			throw AvmException::Runtime("mod : modulo by 0");
		long long i = std::stoll(_value_string) % std::stoll(rhs.toString());
		ss << i;
	} else {
		if (std::stold(rhs.toString()) == 0)
			throw AvmException::Runtime("mod : modulo by 0");
		long double d = std::fmod(std::stold(_value_string),
								  std::stold(rhs.toString()));
		ss << std::fixed << std::setprecision(final_precision) << d;
	}
	return am.createOperand(final_type, ss.str());
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
Operand<T> &Operand<T>::operator=(Operand const &rhs) {
	if (this != &rhs) {
		_value = rhs._value;
		_type = rhs._type;
		_value_string = rhs._value_string;
	}
	return *this;
}





/** Destructor **/


#endif //AVM_OPERAND_HPP
