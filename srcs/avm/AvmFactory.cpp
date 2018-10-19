//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmFactory.hpp>
#include <Operand.hpp>
#include <AvmException.hpp>

/** Static **/
/** Constructor **/

AvmFactory::AvmFactory() : _data(createData()) {
	std::string i_f(R"([0-9]+\.?[0-9]*)");
}

/** Public **/

IOperand const *AvmFactory::createOperand(
		eOperandType const type,
		std::string const &value) const {
	return (this->*_data.at(type))(value);
}

/** Private **/

const std::map<eOperandType, AvmFactory::function> AvmFactory::createData() {
	std::map<eOperandType, AvmFactory::function> _d;
	_d[INT_8] = &AvmFactory::createInt8;
	_d[INT_16] = &AvmFactory::createInt16;
	_d[INT_32] = &AvmFactory::createInt32;
	_d[FLOAT] = &AvmFactory::createFloat;
	_d[DOUBLE] = &AvmFactory::createDouble;
	return _d;
}

IOperand const *AvmFactory::createInt8(std::string const &value) const {
	checkOverflow<long long>(std::stoll(value), INT_8);
	std::smatch match;
	std::regex i_r(R"([0-9]+\.{1}[0-9]*)");
	if (std::regex_match(value.begin(), value.end(), match, i_r))
		throw AvmException::Parsing("push : value bad format");
	return new Operand<int8_t>(INT_8, value);
}

IOperand const *AvmFactory::createInt16(std::string const &value) const {
	checkOverflow<long long>(std::stoll(value), INT_16);
	std::smatch match;
	std::regex i_r(R"([0-9]+\.{1}[0-9]*)");
	if (std::regex_match(value.begin(), value.end(), match, i_r))
		throw AvmException::Parsing("push : value bad format");
	return new Operand<int16_t>(INT_16, value);
}

IOperand const *AvmFactory::createInt32(std::string const &value) const {
	checkOverflow<long long>(std::stoll(value), INT_32);
	std::smatch match;
	std::regex i_r(R"([0-9]+\.{1}[0-9]*)");
	if (std::regex_match(value.begin(), value.end(), match, i_r))
		throw AvmException::Parsing("push : value bad format");
	return new Operand<int32_t>(INT_32, value);
}

IOperand const *AvmFactory::createFloat(std::string const &value) const {
	checkOverflow<long double>(std::stold(value), FLOAT);
	return new Operand<float>(FLOAT, value);
}

IOperand const *AvmFactory::createDouble(std::string const &value) const {
	checkOverflow<long double>(std::stold(value), DOUBLE);
	return new Operand<double>(DOUBLE, value);
}

template<typename U>
void AvmFactory::checkOverflow(U value, eOperandType type) const {
	switch (type) {
		case INT_8:
			if (value > INT8_MAX)
				throw AvmException::Overflow("int8_t");
			if (value < INT8_MIN)
				throw AvmException::Underflow("int8_t");
			break;
		case INT_16:
			if (value > INT16_MAX)
				throw AvmException::Overflow("int16_t");
			if (value < INT16_MIN)
				throw AvmException::Underflow("int16_t");
			break;
		case INT_32:
			if (value > INT32_MAX)
				throw AvmException::Overflow("int32_t");
			if (value < INT32_MIN)
				throw AvmException::Underflow("int32_t");
			break;
		case FLOAT:
			if (value > FLT_MAX)
				throw AvmException::Overflow("float");
			if (value < -FLT_MAX)
				throw AvmException::Underflow("float");
			break;
		case DOUBLE:
			if (value > DBL_MAX)
				throw AvmException::Overflow("double");
			if (value < -DBL_MAX)
				throw AvmException::Underflow("double");
	}
}


/** Operator **/
/** Destructor **/




