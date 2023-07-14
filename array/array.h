#ifndef ARRAY_H
#define ARRAY_H


// The enhanced array class.
template<class T>
class Array
{
public:
	Array(const unsigned length);
	Array(const Array<T>& other);
	~Array();

	template<class U>
	friend std::ostream& operator<<(
		std::ostream& out, Array<U>& array);

	Array<T>& operator=(const Array<T>& other);
	T& operator[](const int index);
	std::string toString();

private:
	unsigned handleNegativeIndex(const int index);
	
	T* array;
	unsigned length;
};


#include "array.cpp"

#endif