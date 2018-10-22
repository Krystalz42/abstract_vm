//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_AVMMODELS_HPP
#define AVM_AVMMODELS_HPP

//Create models data


#include <avm.hpp>
#include <IOperand.hpp>
#include <map>
#include <regex>

class AvmFactory {
private:
	typedef IOperand const *(AvmFactory::*function)(std::string const &) const;

	std::map<eOperandType, function> const createData();

	std::map<eOperandType, function> const _data;

	IOperand const *createInt8(std::string const &value) const;

	IOperand const *createInt16(std::string const &value) const;

	IOperand const *createInt32(std::string const &value) const;

	IOperand const *createFloat(std::string const &value) const;

	IOperand const *createDouble(std::string const &value) const;

	template<typename U>
	void checkOverflow(U value, eOperandType type) const;

public:
	AvmFactory();

	IOperand const *createOperand(eOperandType type, std::string const &value) const;
};

#endif //AVM_AVMMODELS_HPP
