//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_AVMPARSER_HPP
#define AVM_AVMPARSER_HPP

//Read file/stdin
#include <fstream>
#include <map>
#include <avm.hpp>
#include "AvmController.hpp"
#include "AvmModels.hpp"
#include <boost/regex.hpp>
#include <iostream>

class AvmParser {
public:
	AvmParser() = delete;

	explicit AvmParser(int option);

	void fromFile(std::ifstream &file);

	void fromStdin();

	virtual ~AvmParser();

private:
	int _option;
	AvmController *_ac;
	AvmView *_av;
	AvmModels *_am;
	std::map<std::string, eInstruction> const _instruction;
	std::map<std::string, eOperandType> const _operand;

	eInstruction parseInstruction(std::string const &s) const;

	void cleanAvm();

	eOperandType parseOperandType(std::string const &s) const;

	void parseString(std::string const &s);

	std::string parseValue(std::string const &s) const;

	const std::map<std::string, eInstruction>

	createInstructionMap();

	const std::map<std::string, eOperandType> createOperandMap();
};

#endif //AVM_AVMPARSER_HPP
