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
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

	MutantStack<T>(): std::stack<T>() {};
	MutantStack<T>(MutantStack const & ref): std::stack<T>(ref) {};
	virtual ~MutantStack<T>() = default;;

	iterator	begin()
	{
		return std::stack<T>::c.begin();
	};

	const_reverse_iterator	crbegin()
	{
		return std::stack<T>::c.crbegin();
	};
	
	reverse_iterator	rbegin()
	{
		return std::stack<T>::c.rbegin();
	};


	const_reverse_iterator	crend()
	{
		return std::stack<T>::c.crend();
	};

	const_iterator	end()
	{
		return std::stack<T>::c.end();
	};
};

#endif

#endif //AVM_MUTANTSTACK_HPP
