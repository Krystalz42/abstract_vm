//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmController.hpp>
#include <iostream>
#include <AvmException.hpp>
#include <iomanip>

/** Static **/
/** Constructor **/

AvmController::AvmController(int option)
		: _option(option),
		  _fun_map(createFunctionMap()),
		  _av(new AvmView(_stack)) {

	if (option & OPT_VISU) {
		_av->initView();
	}
}

/** Public **/
void AvmController::execute(
		eInstruction ei,
		IOperand const *io
) {
	if (_option & OPT_SLOW && (_option & OPT_FILE)) {
		_av->printInstruction(ei);
		if (io != nullptr)
			std::cout << std::fixed << std::setprecision(io->getPrecision())
					  << std::stod(io->toString());
		std::getline(std::cin, buffer);
	}

	(this->*_fun_map.at(ei))(io);
	if (_option & OPT_VISU && ei != ASSERT) {
		_av->newInput(ei, io);
	}
	if (_option & OPT_VISU && _option & OPT_FILE)
		getch();

}

/** Private **/

void AvmController::_push(IOperand const *io) {
	_stack.push(io);
}

void AvmController::_pop(IOperand const *) {
	if (_stack.empty())
		throw AvmException::StackError("pop : empty stack");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	delete io1;
}

void AvmController::_assert(IOperand const *io) {
	if (io->toString() != _stack.top()->toString()) {
		delete io;
		throw AvmException::StackError("assert : value isn't equals");
	}
	if (io->getType() != _stack.top()->getType()) {
		delete io;
		throw AvmException::StackError("assert : type isn't equals");
	}
	delete io;
}

void AvmController::_add(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("add : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_stack_error.push(io1);
	_stack_error.push(io2);
	_push(*io2 + *io1);
	delete io1;
	delete io2;
	_stack_error.pop();
	_stack_error.pop();
}


void AvmController::_sub(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("sub : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_stack_error.push(io1);
	_stack_error.push(io2);
	_push(*io2 - *io1);
	delete io1;
	delete io2;
	_stack_error.pop();
	_stack_error.pop();
}


void AvmController::_mul(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("mul : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_stack_error.push(io1);
	_stack_error.push(io2);
	_push(*io2 * *io1);
	delete io1;
	delete io2;
	_stack_error.pop();
	_stack_error.pop();
}

void AvmController::_div(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("div : size of stack less than two");

	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_stack_error.push(io1);
	_stack_error.push(io2);
	_push(*io2 / *io1);
	delete io1;
	delete io2;
	_stack_error.pop();
	_stack_error.pop();
}

void AvmController::_mod(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("mod : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_stack_error.push(io1);
	_stack_error.push(io2);
	_push(*io2 % *io1);
	delete io1;
	delete io2;
	_stack_error.pop();
	_stack_error.pop();
}


void AvmController::_swap(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("add : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(io1);
	_push(io2);
}

void AvmController::_max(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("add : size of stack less than two");
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	if (*io1 > *io2) {
		_push(io1);
		delete io2;
	} else {
		_push(io2);
		delete io1;
	}
}

void AvmController::_min(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("add : size of stack less than two");

	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	if (*io1 < *io2) {
		_push(io1);
		delete io2;
	} else {
		delete io1;
		_push(io2);
	}
}

void AvmController::_avg(IOperand const *) {
	if (_stack.size() < 2)
		throw AvmException::StackError("add : size of stack less than two");
	_add(nullptr);
	_push(_am.createOperand(INT_8, "2"));
	_div(nullptr);
}



void AvmController::_dump(IOperand const *) {
	if (!(_option & OPT_VISU))
		std::for_each(_stack.crbegin(), _stack.crend(), print);
}


void AvmController::_print(IOperand const *) {
	IOperand const *io;
	io = _stack.top();
	if (io->getType() == INT_8) {
		if (!(_option & OPT_VISU)) { std::cout << static_cast<int8_t >(std::stoi(io->toString())); }
		else { _av->print(static_cast<int8_t >(std::stoi(io->toString()))); }
	}

}

void AvmController::_clone(IOperand const *) {
	IOperand const * io = _stack.top();
	_push(_am.createOperand(io->getType(), io->toString()));
}

void AvmController::_exit(IOperand const *) {
}

void AvmController::print(IOperand const *io) {
	if (io != nullptr) {
		std::cout
				<< std::fixed
				<< std::setprecision(io->getPrecision())
				<< std::stod(io->toString())
				<< std::endl;
	}
}


std::map<eInstruction, AvmController::function>
AvmController::createFunctionMap() {
	std::map<eInstruction, AvmController::function> fm;
	fm[PUSH] = &AvmController::_push;
	fm[ASSERT] = &AvmController::_assert;
	fm[POP] = &AvmController::_pop;
	fm[DUMP] = &AvmController::_dump;
	fm[ADD] = &AvmController::_add;
	fm[SUB] = &AvmController::_sub;
	fm[MUL] = &AvmController::_mul;
	fm[DIV] = &AvmController::_div;
	fm[MOD] = &AvmController::_mod;
	fm[PRINT] = &AvmController::_print;
	fm[EXIT] = &AvmController::_exit;
	fm[SWAP] = &AvmController::_swap;
	fm[MAX] = &AvmController::_max;
	fm[MIN] = &AvmController::_min;
	fm[AVG] = &AvmController::_avg;
	fm[CLONE] = &AvmController::_clone;
	return fm;
}

AvmView *AvmController::getAv() const {
	return _av;
}

/** Operator **/
/** Destructor **/

AvmController::~AvmController() {
	auto it = _stack.begin();
	auto ite = _stack.end();
	for (; it != ite; ++it) {
		delete *it;
	}
	auto it_err = _stack_error.begin();
	auto ite_err = _stack_error.end();
	for (; it_err != ite_err; ++it_err) {
		delete *it_err;
	}
	delete _av;
}