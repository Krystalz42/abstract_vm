//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_AVM_HPP
#define AVM_AVM_HPP

enum eOperandType {
	INT_8,		//0
	INT_16,		//1
	INT_32,		//2
	FLOAT,		//3
	DOUBLE,		//4
	NONE		//5
};

enum eInstruction {
	PUSH,		//0
	ASSERT,		//1
	POP,		//2
	DUMP,		//3
	ADD,		//4
	SUB,		//5
	MUL,		//6
	DIV,		//7
	MOD,		//8
	PRINT,		//9
	EXIT		//10
};

#endif //AVM_AVM_HPP
