//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmParser.hpp>


/** Static **/
/** Constructor **/
AvmParser::AvmParser() : _instruction(createInstructionMap()),
						 _operand(createOperandMap()) {}

/** Public **/

void AvmParser::fromFile(std::ifstream &file) const {
	std::string buffer;

	while (!file.eof()) {
		std::getline(file, buffer);
		if (!buffer.empty())
			parseString(buffer);
	}
}

void AvmParser::fromStdin() const {

}

/** Private **/

void AvmParser::parseString(std::string const &s) const {
	eInstruction ei;
	try {
		ei = parseInstruction(s);
		std::cout << "Instruction  : " << ei << std::endl;
		if (ei == PUSH || ei == ASSERT) {
			eOperandType eop = parseOperandType(s);
			std::string sv = parseValue(s);
			am.createOperand(eop, sv);

			ac.execute(ei, eop, sv);

			std::cout << "Operand : " << parseOperandType(s) << std::endl;
			std::cout << "Value : " << parseValue(s) << std::endl;
		}

	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

}

eInstruction AvmParser::parseInstruction(std::string const &s) const {
	for (auto &ins : _instruction) {
		if (s.find(ins.first) != std::string::npos)
			return ins.second;
	}
	throw std::invalid_argument("instruction false");
}

eOperandType AvmParser::parseOperandType(std::string const &s) const {
	for (auto &op : _operand) {
		if (s.find(op.first) != std::string::npos)
			return op.second;
	}
	throw std::invalid_argument("operand type false");
}

std::string AvmParser::parseValue(std::string const &s) const {
	std::string ss = boost::regex_replace(s,
			boost::regex(R"(^.*?\([^\d]*(\d+)[^\d]*\).*$)"),
			std::string("\\1")
	);
	return ss;
}

std::map<std::string, eInstruction> const AvmParser::createInstructionMap() {
	std::map<std::string, eInstruction> ins;
	ins["push"] = PUSH;
	ins["assert"] = ASSERT;
	ins["pop"] = POP;
	ins["dump"] = DUMP;
	ins["add"] = ADD;
	ins["sub"] = SUB;
	ins["mul"] = MUL;
	ins["div"] = DIV;
	ins["mod"] = MOD;
	ins["print"] = PRINT;
	ins["exit"] = EXIT;
	return ins;
}


const std::map<std::string, eOperandType> AvmParser::createOperandMap() {
	std::map<std::string, eOperandType> op;
	op["int8"] = INT_8;
	op["int16"] = INT_16;
	op["int32"] = INT_32;
	op["float"] = FLOAT;
	op["double"] = DOUBLE;
	return op;
}

/** Operator **/
/** Destructor **/

AvmParser::~AvmParser() {

}