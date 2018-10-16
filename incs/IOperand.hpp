//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_IOPERAND_HPP
#define AVM_IOPERAND_HPP

#include <avm.hpp>
#include <string>

class IOperand {
public:
	virtual int getPrecision() const = 0;

	virtual eOperandType getType() const = 0;

	virtual IOperand const *operator+(IOperand const &) const= 0;

	virtual IOperand const *operator-(IOperand const &)const = 0;

	virtual IOperand const *operator*(IOperand const &)const = 0;

	virtual IOperand const *operator/(IOperand const &) const= 0;

	virtual IOperand const *operator%(IOperand const &)const = 0;

	virtual std::string const &toString() const = 0;

	virtual ~IOperand() {};
};

#endif //AVM_IOPERAND_HPP
