//
// Created by Alexandre ROULIN on 16/10/2018.
//

#ifndef AVM_MUTANTSTACK_HPP
#define AVM_MUTANTSTACK_HPP

#ifndef EX02_MUTANTSTACK_HPP
#define EX02_MUTANTSTACK_HPP

#include <stack>
#include <list>
#include <iostream>
#include <unistd.h>
template <typename T>
class MutantStack: public std::stack<T>
{
public:
	typedef typename std::stack<T>::container_type::iterator iterator;

	MutantStack<T>(): std::stack<T>() {};
	MutantStack<T>(MutantStack const & ref): std::stack<T>(ref) {};
	virtual ~MutantStack<T>() = default;;

	iterator	begin()
	{
		return std::stack<T>::c.begin();
	};

	iterator	end()
	{
		return std::stack<T>::c.end();
	};
};

#endif

#endif //AVM_MUTANTSTACK_HPP
