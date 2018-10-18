//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmParser.hpp>
#include <regex>
#include <AvmException.hpp>

//FICHIER NO_OPT			-> NOTHING	-	GETLINE			√
//NO_FICHIER NO_OPT			-> NOTHING	-	GETLINE			√

//FICHIER SLOW				-> GETCH	-	GETLINE			√
//NO_FICHIER SLOW			-> GETCH	-	GETNCURSES		NOT SUPPORTED

//FICHIER VISU				-> GETCH	-	GETLINE			√
//NO_FICHIER VISU			-> GETCH	-	GETNCURSES		√

/** Static **/
/** Constructor **/
AvmParser::AvmParser(int option) :
		_option(option),
		_ac(new AvmController(option)),
		_av(_ac->getAv()),
		_am(new AvmModels()),
		_instruction(createInstructionMap()),
		_operand(createOperandMap()) {
}

/** Public **/

void AvmParser::fromFile(std::ifstream &file) {
	std::string buffer;

	while (!file.eof()) {
		std::getline(file, buffer);
		if (!buffer.empty())
			parseString(buffer);
	}
}

void AvmParser::fromStdin() {
	std::string buffer;

	while (!std::cin.eof()) {
		if (_option & OPT_VISU)
			buffer = _av->getLine();
		else
			std::getline(std::cin, buffer);
		if (!buffer.empty()) {
			parseString(buffer);

		}
	}
}

/** Private **/

void AvmParser::parseString(std::string const &s) {
	eInstruction ei;
	if (s.find(";;") == 0)
		std::cin.setstate(std::__1::istream::eofbit);
	if (s.find(';') == 0)
		return;
	try {
		if (_ac == nullptr || _am == nullptr)
			throw AvmException::AvmError("program is close");
		ei = parseInstruction(s);
		if (ei == PUSH || ei == ASSERT) {
			eOperandType eop = parseOperandType(s);
			std::string sv = parseValue(s);

			_ac->execute(ei, _am->createOperand(eop, sv));

		} else if (ei == EXIT) {
			cleanAvm();
		} else {
			_ac->execute(ei);
		}

	} catch (AvmException::AvmError &e) {
		std::cout << "avm error : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (AvmException::Parsing &e) {
		std::cout << "avm parsing : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (AvmException::StackError &e) {
		std::cout << "stack error : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (AvmException::Overflow &e) {
		std::cout << "overflow : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (AvmException::Underflow &e) {
		std::cout << "underflow : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (AvmException::Runtime &e) {
		std::cout << "runtime : " << e.what() << std::endl;
		cleanAvm();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		cleanAvm();
	}
}

eInstruction AvmParser::parseInstruction(std::string const &s) const {
	for (auto &ins : _instruction) {
		if (s.find(ins.first) != std::string::npos)
			return ins.second;
	}
	throw AvmException::Parsing("bad instruction");
}

eOperandType AvmParser::parseOperandType(std::string const &s) const {
	for (auto &op : _operand) {
		if (s.find(op.first) != std::string::npos)
			return op.second;
	}
	throw AvmException::Parsing("bad type");
}

std::string AvmParser::parseValue(std::string const &s) const {
	std::regex rgx(
			R"([a-z]*\s[a-z]*[0-9]*\(([\+|\-]?[0-9]+\.?[0-9]*[fE\+]{0,3}[0-9]*)\))");
	std::smatch match;
	//

	if (std::regex_search(s.begin(), s.end(), match, rgx)) {
		return match[1];
	}
	throw AvmException::Parsing("value bad format");
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
	ins["swap"] = SWAP;
	ins["max"] = MAX;
	ins["min"] = MIN;
	ins["avg"] = AVG;
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

void AvmParser::cleanAvm() {
	delete _am;
	_am = nullptr;
	delete _ac;
	_ac = nullptr;
}
/** Operator **/
/** Destructor **/

AvmParser::~AvmParser() {
	if (_am != nullptr || _ac != nullptr)
		std::cerr
				<< "abstract vm : program close without calling \'exit\'"
				<< std::endl;
	delete _am;
	delete _ac;
}


