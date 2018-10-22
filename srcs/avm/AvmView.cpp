//
// Created by Alexandre ROULIN on 17/10/2018.
//

#include <avm/AvmView.hpp>

#define COLS_WINS    COLS / 2
#define COLS_WINS_RENDER    COLS_WINS - 3


/** Static **/

/** Constructor **/

AvmView::AvmView(MutantStack<const IOperand *> &_stack_operand)
		: _stack_operand(_stack_operand) {
	_data_instruction[PUSH] = "push";
	_data_instruction[ASSERT] = "assert";
	_data_instruction[POP] = "pop";
	_data_instruction[DUMP] = "dump";
	_data_instruction[ADD] = "add";
	_data_instruction[SUB] = "sub";
	_data_instruction[MUL] = "mul";
	_data_instruction[DIV] = "div";
	_data_instruction[MOD] = "mod";
	_data_instruction[PRINT] = "print";
	_data_instruction[EXIT] = "exit";
	_data_instruction[SWAP] = "swap";
	_data_instruction[MAX] = "max";
	_data_instruction[MIN] = "min";
	_data_instruction[AVG] = "avg";
	_data_instruction[CLONE] = "clone";

	_data_operand[INT_8] = "int8_t";
	_data_operand[INT_16] = "int16_t";
	_data_operand[INT_32] = "int32_t";
	_data_operand[FLOAT] = "float";
	_data_operand[DOUBLE] = "double";
}

/** Public **/

void AvmView::initView() {
	initscr();
	noecho();
	keypad(stdscr, true);
	curs_set(false);
	_instruction_view = subwin(stdscr, LINES - 1, COLS_WINS, 1, 0);
	_stack_view = subwin(stdscr, LINES - 1, COLS_WINS, 1, COLS / 2);
	box(_stack_view, ACS_VLINE, ACS_HLINE);
	box(_instruction_view, ACS_VLINE, ACS_HLINE);
	wrefresh(_stack_view);
}

void AvmView::newInput(eInstruction ins, IOperand const *io) {
	addInstruction(ins, io);
	refreshInstruction();
	refreshOperand();
}

void AvmView::printInstruction(eInstruction ins) {
	std::cout << "       " << _data_instruction[ins] << " ";
}

std::string AvmView::getLine() {
	char str[1000] = {0};
	echo();
	curs_set(true);
	mvgetnstr(0, 0, str, 1000);
	move(0, 0);
	clrtoeol();
	curs_set(false);
	noecho();
	return std::string(str);
}

void AvmView::printError(char const *what) {
	mvprintw(0, static_cast<int>(COLS - std::strlen(what)), what);
}

void AvmView::print(char const c) {
	mvaddch(0, COLS - 1, c);
}

std::ofstream f("./error");

/** Private **/
void AvmView::addInstruction(eInstruction ei, IOperand const *io) {
	std::stringstream ss;
	ss << _data_instruction[ei];
	if (io != nullptr) {
		f << "Instr : " << ei << "type is null : " << io->getType() << std::endl << std::endl;
		ss << " ";
		ss << _data_operand[io->getType()];
		ss << " ";
		ss << std::fixed << std::setprecision(io->getPrecision())
		   << std::stod(io->toString());
	}
	_stack_instruction.push(ss.str());
}

void AvmView::refreshInstruction() {
	wclear(_instruction_view);
	int index = 0;
	auto it = _stack_instruction.rbegin();
	auto ite = _stack_instruction.crend();
	for (; it != ite; ++it) {
		if (LINES - 3 - index >= 1) {
			mvwprintw(_instruction_view, LINES - 3 - index,
					  (COLS_WINS_RENDER - (*it).size()) / 2,
					  "| %s |", (*it).c_str());
			index++;
		}

	}
	box(_instruction_view, ACS_VLINE, ACS_HLINE);
	wrefresh(_instruction_view);
}

void AvmView::refreshOperand() {
	wclear(_stack_view);
	auto it = _stack_operand.rbegin();
	auto ite = _stack_operand.crend();
	int index = static_cast<int>(static_cast<int>(_stack_operand.size()) >
								 LINES - 3 ? LINES - 3
										   : _stack_operand.size());
	for (; it != ite; ++it) {
		createBox(index, *it);
		index--;
	}
	box(_stack_view, ACS_VLINE, ACS_HLINE);
	wrefresh(_stack_view);
}

void AvmView::createBox(int index, IOperand const *io) {
	if (index > 0) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(io->getPrecision())
		   << std::stod(io->toString());
		mvwprintw(_stack_view,
				  LINES - 3 - index + 1,
				  (COLS_WINS_RENDER - ss.str().size()) / 2, "| %s |",
				  ss.str().c_str());
	}

}

/** Operator **/
/** Destructor **/

AvmView::~AvmView() {
	delwin(_stack_view);
	delwin(_instruction_view);
	curs_set(1);
	endwin();
}


