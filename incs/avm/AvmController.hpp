//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_AVMPARSER_HPP
#define AVM_AVMPARSER_HPP

//Manage data

#include <avm.hpp>
#include <Operand.hpp>

class AvmController {
public:
	AvmController();
	void execute(eInstruction, eOperandType, IOperand const *);


};

#endif //AVM_AVMPARSER_HPP


// AvmParser (read) >> AvmModels(createData) >> AvmController (stock data) >> AvmView (show data)

//	push
//	| pop
//	| dump
//	| assert VALUE
//	| add
//	| sub
//	| mul
//	| div
//	| mod
//	| print
//	| exit