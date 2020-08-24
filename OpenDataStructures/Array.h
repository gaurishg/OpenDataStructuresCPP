#pragma once

/*
This is just basic array, it keeps record of number of elements it can hold
But it doesn't keep track of how many of them you have currently used
*/

#include<iostream>
#include<exception>



class ArrayIndexOutOfBounds : public std::exception
{
	const char* what() const throw()
	{
		return "Array Index Out of Bounds";
	}
};

class ArrayAlreadyFull : public std::exception
{
	const char* what() const throw()
	{
		return "Array is already full";
	}
};

template<typename T>
class Array;

template<typename T>
std::ostream& operator<<(std::ostream&, const Array<T>&);

template<typename T>
class Array
{
private:
	T* arr;
	int length;
public:
	Array();
	Array(int);
	//Array(Array<T>&);//Copy constructor not needed since anyway default copy constructor is provided
	//~Array();
	T& operator[](int);
	virtual Array<T>& operator=(Array<T>&);
	virtual bool operator==(const Array<T>&) const;
	virtual bool operator!=(const Array<T>&) const;
	friend std::ostream& operator<<<T>(std::ostream& os, const Array<T>& bar);
	int capacity() const;
	virtual void free();
	T get(int) const;
	T set(int, T);
	virtual T add(int, T);
	virtual T remove(int);
	bool resize(int);
};


template<typename T>
Array<T>::Array() : length(0), arr(nullptr)
{}

template<typename T>
Array<T>::Array(int len) : length(len), arr(new T[len])
{}

//template<typename T>
//Array<T>::Array(Array<T>& brr) : length(brr.length), arr(brr.arr)
//{
//	//brr.arr = nullptr;
//	//brr.length = 0;
//}

//template<typename T>
//Array<T>::~Array()
//{
//	/*if (arr != nullptr)
//		delete[] arr;*/
//}

template<typename T>
T& Array<T>::operator[](int index)
{
	//assert(index >= 0 && index < length);
	if (!(index >= 0 && index < length))
		throw ArrayIndexOutOfBounds();
	return arr[index];
}

template<typename T>
int Array<T>::capacity() const
{
	return length;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>& rhs)
{
	if (arr != nullptr)
		delete[] arr;
	arr = rhs.arr;
	//rhs.arr = nullptr; // temporary addition
	length = rhs.length;
	//rhs.length = 0; // temporary addition
	return *this;
}

template<typename T>
bool Array<T>::operator==(const Array<T>& rhs) const
{
	return (arr == rhs.arr && length == rhs.length);
}

template<typename T>
bool Array<T>::operator!=(const Array<T>& rhs) const
{
	return !operator==(rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& bar)
{
	os << '[';
	int i{ 0 };
	for (; i < bar.length - 1; ++i)
		os << (bar.arr)[i] << ", ";
	if (i == bar.length - 1)
		os << (bar.arr)[i];
	os << ']';

	return os;
}

template<typename T>
void Array<T>::free()
{
	if (arr)
		delete[] arr;
	length = 0;
}

template<typename T>
T Array<T>::get(int index) const
{
	if (!(index >= 0 && index < length))
		throw ArrayIndexOutOfBounds();
	return arr[index];
}

template<typename T>
T Array<T>::set(int index, T new_value)
{
	T prev_value = arr[index];
	arr[index] = new_value;
	return prev_value;
}

template<typename T>
bool Array<T>::resize(int new_size)
{
	T* new_arr = new T[new_size];
	if (!new_arr)
		return false;
	if (arr && length > 0)
	{
		for (int i{ 0 }; i < length && i < new_size; ++i)
			new_arr[i] = arr[i];
		delete[] arr;
	}
	arr = new_arr;
	length = new_size;
	return true;
}

template<typename T>
T Array<T>::add(int index, T item)
{
	if (index < 0 || index >= length)
		throw ArrayIndexOutOfBounds();
	int i;
	for (i = length - 1; i > index; --i)
		arr[i] = arr[i - 1];
	arr[i] = item;
	return item;
}

template<typename T>
T Array<T>::remove(int index)
{
	if (index < 0 || index >= length)
		throw ArrayIndexOutOfBounds();
	int temp = arr[index];
	for (int i{ index }; i < length - 1; ++i)
		arr[i] = arr[i + 1];
	return temp;
}