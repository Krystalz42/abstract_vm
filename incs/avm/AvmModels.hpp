//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_AVMMODELS_HPP
#define AVM_AVMMODELS_HPP

//Create models data

#include <IOperand.hpp>
#include <Operand.hpp>
#include <map>

class AvmModels {
private:
	typedef IOperand const *(AvmModels::*function)(std::string const &) const;

	const std::map<eOperandType, function> createData();

	std::map<eOperandType, function> const		_data;

	IOperand const *createInt8(std::string const &value) const;

	IOperand const *createInt16(std::string const &value) const;

	IOperand const *createInt32(std::string const &value) const;

	IOperand const *createFloat(std::string const &value) const;

	IOperand const *createDouble(std::string const &value) const;

public:
	AvmModels();

	IOperand const *
	createOperand(eOperandType type, std::string const &value) const;

};

#endif //AVM_AVMMODELS_HPP
