//
// Created by Alexandre ROULIN on 16/10/2018.
//

#include <avm/AvmController.hpp>
#include <iostream>
/** Static **/
/** Constructor **/
AvmController::AvmController() : _fun_map(createFunctionMap()) {

}

/** Public **/
void AvmController::execute(
		eInstruction ei,
		IOperand const *io
) {

	(this->*_fun_map.at(ei))(io);
}

/** Private **/


void AvmController::_push(IOperand const *io) {
	_stack.push(io);
}

void AvmController::_pop(IOperand const *) {
	_stack.pop();
}

void AvmController::_dump(IOperand const *) {
	std::for_each(_stack.begin(), _stack.end(), print);
}

void AvmController::_assert(IOperand const *io) {
	if (io->toString() != _stack.top()->toString())
		throw std::exception();
}

void AvmController::_add(IOperand const *) {
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(_addWork(io1, io2));
}

IOperand const *AvmController::_addWork(IOperand const *io1,
										IOperand const *io2) const {
	return io1->operator+(*io2);
}

void AvmController::_sub(IOperand const *) {
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(_subWork(io1, io2));
}

IOperand const *
AvmController::_subWork(IOperand const *io1, IOperand const *io2) const {
	return io1->operator-(*io2);
}

void AvmController::_mul(IOperand const *) {
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(_mulWork(io1, io2));
}

IOperand const *
AvmController::_mulWork(IOperand const *io1, IOperand const *io2) const {
	return io1->operator*(*io2);
}

void AvmController::_div(IOperand const *) {
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(_divWork(io1, io2));
}

IOperand const *
AvmController::_divWork(IOperand const *io1, IOperand const *io2) const {
	return io1->operator/(*io2);
}

void AvmController::_mod(IOperand const *) {
	IOperand const *io1 = _stack.top();
	_stack.pop();
	IOperand const *io2 = _stack.top();
	_stack.pop();
	_push(_modWork(io1, io2));
}

IOperand const *
AvmController::_modWork(IOperand const *io1, IOperand const *io2) const {
	return io1->operator%(*io2);
}

void AvmController::_print(IOperand const *) {
	IOperand const *io;
	io = _stack.top();
	if (io->getType() == INT_8)
		std::cout << static_cast<unsigned char>(std::stoi(io->toString())) << std::endl;
}

void AvmController::_exit(IOperand const *) {
	exit(EXIT_SUCCESS);
}

void AvmController::print(IOperand const *io) {
	if (io != nullptr)
		std::cout << io->toString() << std::endl;
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
	return fm;
}
/** Operator **/
/** Destructor **/