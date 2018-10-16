//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmModels.hpp>

/** Static **/
/** Constructor **/

AvmModels::AvmModels() : _data(createData()) {}

/** Public **/

IOperand const *AvmModels::createOperand(
		eOperandType const type,
		std::string const &value) const {
	return (this->*_data.at(type))(value);
}

/** Private **/

const std::map<eOperandType, AvmModels::function> AvmModels::createData() {
	std::map<eOperandType, AvmModels::function> _d;
	_d[INT_8] = &AvmModels::createInt8;
	_d[INT_16] = &AvmModels::createInt16;
	_d[INT_32] = &AvmModels::createInt32;
	_d[FLOAT] = &AvmModels::createFloat;
	_d[DOUBLE] = &AvmModels::createDouble;
	return _d;
}

IOperand const *AvmModels::createInt8(std::string const &value) const {
	return new Operand<int8_t>(value);
}

IOperand const *AvmModels::createInt16(std::string const &value) const {
	return new Operand<int16_t>(value);
}

IOperand const *AvmModels::createInt32(std::string const &value) const {
	return new Operand<int32_t>(value);
}

IOperand const *AvmModels::createFloat(std::string const &value) const {
	return new Operand<float>(value);
}

IOperand const *AvmModels::createDouble(std::string const &value) const {
	return new Operand<double>(value);
}



/** Operator **/
/** Destructor **/




