#ifndef ARRAY_H
#define ARRAY_H


// The enhanced array class.
template<class T>
class Array
{
public:
	Array(const unsigned capacity = 100);
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
	int indexOf(const T element);
	void insert(const T element);
	void insertAt(const int signedIndex, const T element);
	unsigned maxCapacity() const;
	void remove(const T element);
	T removeAt(const int signedIndex);
	void reverse();
	Array<T> reversed();
	void set(const int index, const T element);
	unsigned size() const;
	Array<T>* subArray(const unsigned start, const unsigned end);
	std::string toString();

private:
	unsigned handleNegativeIndex(const int index);
	unsigned updateCapacity(const unsigned length);

	T* array;
	unsigned length;
	unsigned capacity;
};


#include "array.cpp"

#endif
