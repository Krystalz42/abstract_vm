//
// Created by Alexandre ROULIN on 17/10/2018.
//

#ifndef AVM_AMVVIEW_HPP
#define AVM_AMVVIEW_HPP

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <MutantStack.hpp>
#include <IOperand.hpp>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

class AvmView {
private:
	WINDOW *_instruction_view;
	WINDOW *_stack_view;
	MutantStack<IOperand const *> &_stack_operand;
	MutantStack<std::string> _stack_instruction;

	std::map<eInstruction, char const *> _data_instruction;
	std::map<eOperandType, std::string> _data_operand;

	void refreshInstruction();

	void refreshOperand();

	void addInstruction(eInstruction ie, IOperand const *io);

	void createBox(int index, IOperand const *io);

public:
	AvmView() = delete;

	explicit AvmView(MutantStack<const IOperand *> &_stack_operand);

	void initView();

	void newInput(eInstruction, IOperand const *);

	void printInstruction(eInstruction);

	std::string getLine();

	virtual ~AvmView();

};

#endif //AVM_AMVVIEW_HPP
