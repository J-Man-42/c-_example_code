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
	Array<T> operator+(const T element);
	Array<T> operator+(const Array<T>& other);
	Array<T>& operator+=(const T element);
	Array<T>& operator+=(const Array<T>& other);

	void append(const T element);
	Array<T> clone();
	bool contains(const T element) const;
	T& get(const int index);
	void reverse();
	Array<T> reversed();
	void set(const int index, const T element);
	unsigned size() const;
	Array<T>* subArray(const unsigned start, const unsigned end);
	std::string toString();

private:
	unsigned handleNegativeIndex(const int index);

	T* array;
	unsigned length;
};


#include "array.cpp"

#endif
