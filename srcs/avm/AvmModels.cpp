//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmModels.hpp>
#include <Operand.hpp>
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
	return new Operand<int8_t>(INT_8, value);
}

IOperand const *AvmModels::createInt16(std::string const &value) const {
	return new Operand<int16_t>(INT_16, value);
}

IOperand const *AvmModels::createInt32(std::string const &value) const {
	return new Operand<int32_t>(INT_32, value);
}

IOperand const *AvmModels::createFloat(std::string const &value) const {
	return new Operand<float>(FLOAT, value);
}

IOperand const *AvmModels::createDouble(std::string const &value) const {
	return new Operand<double>(DOUBLE, value);
}



/** Operator **/
/** Destructor **/




