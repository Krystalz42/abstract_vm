//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include <avm/AvmModels.hpp>
#include <iostream>
#include "IOperand.hpp"

template<typename T>
class Operand : virtual public IOperand {
private:

	T _value;
	eOperandType _type;
	std::string _value_string;
	AvmModels am;

	Operand();

public:
	Operand(IOperand const *);

	Operand(eOperandType, std::string const &);

	int getPrecision() const override;

	eOperandType getType() const override;

	const IOperand *operator+(IOperand const &operand) const override;

	const IOperand *operator-(IOperand const &operand) const override;

	const IOperand *operator*(IOperand const &operand) const override;

	const IOperand *operator/(IOperand const &operand) const override;

	const IOperand *operator%(IOperand const &operand) const override;

	const std::string &toString() const override;
};

/** Static **/
/** Constructor **/

template<typename T>
Operand<T>::Operand(eOperandType type, std::string const &s)
		:    _value(std::stod(s)),
			 _type(type),
			 _value_string(s) {

}

template<typename T>
Operand<T>::Operand(IOperand const *io)
		: _value(std::stod(io->toString())),
		  _type(io->getType()),
		  _value_string(io->toString()) {

}

/** Public **/
template<typename T>
int Operand<T>::getPrecision() const {
	return 0;
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
	auto &e = static_cast<Operand<double>>(&io);
//	return am.createOperand(_type, std::to_string(_value + e._value));
}

template<typename T>
const IOperand *Operand<T>::operator-(IOperand const &) const {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator*(IOperand const &) const {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator/(IOperand const &) const {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator%(IOperand const &) const {
	return nullptr;
}


/** Destructor **/


#endif //AVM_OPERAND_HPP
