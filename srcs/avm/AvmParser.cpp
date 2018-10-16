//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmParser.hpp>
#include <regex>


/** Static **/
/** Constructor **/
AvmParser::AvmParser() : _instruction(createInstructionMap()),
						 _operand(createOperandMap()) {}

/** Public **/

void AvmParser::fromFile(std::ifstream &file)  {
	std::string buffer;

	while (!file.eof()) {
		std::getline(file, buffer);
		if (!buffer.empty())
			parseString(buffer);
	}
}

void AvmParser::fromStdin()  {
	std::string buffer;

	while (!std::cin.eof()) {
		std::getline(std::cin, buffer);
		if (!buffer.empty())
			parseString(buffer);
	}
}

/** Private **/

void AvmParser::parseString(std::string const &s)  {
	eInstruction ei;

	try {
		ei = parseInstruction(s);

		if (ei == PUSH || ei == ASSERT) {

			eOperandType eop = parseOperandType(s);
			std::string sv = parseValue(s);

			ac.execute(ei, am.createOperand(eop, sv));

		} else
			ac.execute(ei);

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
	std::regex rgx(R"([a-z]*\s[a-z]*[0-9]*\(([0-9]+\.?[0-9]+)\))");
	std::smatch match;
	//

	if (std::regex_search(s.begin(), s.end(), match, rgx))
		return match[1];
	throw std::invalid_argument("value bad format");
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