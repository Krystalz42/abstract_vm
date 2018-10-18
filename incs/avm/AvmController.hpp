//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef __AVM_AVM_CONTROLLER_HPP__
#define __AVM_AVM_CONTROLLER_HPP__

//Manage data

#include <avm.hpp>
#include <Operand.hpp>
#include <stack>
#include <MutantStack.hpp>
#include <map>
#include <avm/AvmView.hpp>

class AvmController {
private:

	int _option;

	MutantStack<IOperand const *> _stack;

	AvmModels _am;

	AvmView		*_av;

	std::string			buffer;

	typedef void (AvmController::*function)(IOperand const *);

	std::map<eInstruction, function> const _fun_map;

	std::map<eInstruction, function> createFunctionMap();

	void _push(IOperand const *);

	void _pop(IOperand const *);

	void _dump(IOperand const *);

	void _assert(IOperand const *);

	void _add(IOperand const *);

	IOperand const *_addWork(IOperand const *io1, IOperand const *io2) const;

	IOperand const *_subWork(IOperand const *io1, IOperand const *io2) const;

	IOperand const *_mulWork(IOperand const *io1, IOperand const *io2) const;

	IOperand const *_divWork(IOperand const *io1, IOperand const *io2) const;

	IOperand const *_modWork(IOperand const *io1, IOperand const *io2) const;

	void _sub(IOperand const *);

	void _swap(IOperand const *);

	void _max(IOperand const *);

	void _min(IOperand const *);

	void _avg(IOperand const *);

	void _mul(IOperand const *);

	void _div(IOperand const *);

	void _mod(IOperand const *);

	void _print(IOperand const *);

	void _exit(IOperand const *);

public:
	AvmView *getAv() const;

private:

	static void print(IOperand const *);

public:
	AvmController() = delete;

	explicit AvmController(int option);

	void execute(eInstruction, IOperand const * = nullptr);

	virtual ~AvmController();


};

#endif //__AVM_AVM_CONTROLLER_HPP__


// AvmParser (read) >> AvmModels(createData) >> AvmController (stock data) >> AvmView (show data)

//
//
//
//	VALUE
//
//
//
//
//
//
//