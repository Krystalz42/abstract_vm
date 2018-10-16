//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include "IOperand.hpp"

template<typename T>
class Operand : virtual public IOperand {
private:
	Operand() = delete;
	T _value;
	std::string		_value_string;
public:
	Operand(std::string const &value);

	int getPrecision() const override;

	eOperandType getType() const override;

	const IOperand *operator+(IOperand const &operand) override;

	const IOperand *operator-(IOperand const &operand) override;

	const IOperand *operator*(IOperand const &operand) override;

	const IOperand *operator/(IOperand const &operand) override;

	const IOperand *operator%(IOperand const &operand) override;

	const std::string &toString() const override;
};

/** Static **/
/** Constructor **/

template<typename T>
Operand<T>::Operand(std::string const &value) : _value(std::stod(value)), _value_string(value) {
	//TODO Overflow Underflow
}

/** Public **/
template<typename T>
int Operand<T>::getPrecision() const {
	return 0;
}

template<typename T>
eOperandType Operand<T>::getType() const {
	return DOUBLE;
}

template<typename T>
const std::string &Operand<T>::toString() const {
	return _value_string;
}
/** Private **/
/** Operator **/

template<typename T>
const IOperand *Operand<T>::operator+(IOperand const &) {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator-(IOperand const &) {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator*(IOperand const &) {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator/(IOperand const &) {
	return nullptr;
}

template<typename T>
const IOperand *Operand<T>::operator%(IOperand const &) {
	return nullptr;
}

/** Destructor **/


#endif //AVM_OPERAND_HPP
