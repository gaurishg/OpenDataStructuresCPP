#pragma once

#include "Array.h"
#include <iostream>
#include <exception>

class PopFromEmptyStack : public std::exception
{
	const char* what() const throw()
	{
		return "Can not pop from an empty stack";
	}
};

class PeepOnEmptyStack : public std::exception
{
	const char* what() const throw()
	{
		return "Can not peep on an empty stack";
	}
};

class OperationOusideOfStack : public std::exception
{
	const char* what() const throw()
	{
		return "Operation outside of stack";
	}
};


template<typename T>
class ArrayStack;

template<typename T>
std::ostream& operator<<(std::ostream&, const ArrayStack<T>&);

template<typename T>
class ArrayStack : public Array<T>
{
	//Array<T> arr;
	int n; // number of elements in stack
public:
	ArrayStack(int len = 100);
	~ArrayStack();
	int get_top() const;
	int size() const;
	virtual void free();
	T push(const T);
	T pop();
	T peep() const;
	virtual bool operator==(const ArrayStack<T>&) const;
	virtual bool operator!=(const ArrayStack<T>&) const;
	virtual T add(int, T);
	virtual T remove(int);
};

template<typename T>
ArrayStack<T>::ArrayStack(int len) : Array<T>(len), n(0)
{
}

template<typename T>
ArrayStack<T>::~ArrayStack()
{
}

template<typename T>
int ArrayStack<T>::get_top() const
{
	return n - 1;
}

template<typename T>
int ArrayStack<T>::size() const
{
	return n;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ArrayStack<T>& stack)
{
	os << '[';
	int i{ 0 };
	for (; i <= stack.get_top() - 1; ++i)
		os << stack[i] << ' ';
	if (i == stack.get_top())
		os << '(' << stack[i] << ')';
	os << ']';
	return os;
}

template<typename T>
void ArrayStack<T>::free()
{
	Array<T>::free();
	n = 0;
}

template<typename T>
T ArrayStack<T>::push(const T new_element)
{
	if (size() == this->capacity())
		this->resize(2 * size() + 1); // 1 is added for the case when size is zero
	this->set(n++, new_element);
	return new_element;
}

template<typename T>
T ArrayStack<T>::pop()
{
	if (n == 0)
		throw PopFromEmptyStack();
	--n;
	return this->get(n);
}

template<typename T>
T ArrayStack<T>::peep() const
{
	if (n == 0)
		throw PeepOnEmptyStack();
	return this->get(n - 1);
}

template<typename T>
bool ArrayStack<T>::operator==(const ArrayStack<T>& rhs) const
{
	bool result = (n == rhs.n);
	if (result)
	{
		for (int i = 0; i < n && result; ++i)
			result = (this->get(i) == rhs.get(i));
	}
	return result;
}

template<typename T>
bool ArrayStack<T>::operator!=(const ArrayStack<T>& rhs) const
{
	return !(this->operator==(rhs));
}

template<typename T>
T ArrayStack<T>::add(int index, T item)
{
	if (index < 0 || index >= n)
		throw OperationOusideOfStack();
	if (this->capacity() == this->size())
		this->resize(2 * this->size() + 1);
	++n;
	return Array<T>::add(index, item);
}

template<typename T>
T ArrayStack<T>::remove(int index)
{
	if (index < 0 || index >= n)
		throw OperationOusideOfStack();
	--n;
	return Array<T>::remove(index);
}