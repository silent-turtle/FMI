#ifndef POLY_HDR
#define POLY_HDR

#include<iostream>

template<typename T>
class Poly
{
public:
	Poly(const T* arr, size_t num);
	~Poly();

	void printPoly() const;

	bool operator==(const Poly& other) const;
	bool operator<(const Poly& other) const;
	bool operator>(const Poly& other) const;
	T& operator[](size_t index);
	const T operator[] (size_t index) const;


	Poly<T>& operator+=(const Poly& other);
	Poly<T> operator+(const Poly& other);
	Poly<T>& operator-=(const Poly& other);
	Poly<T> operator-(const Poly& other);

private:
	T* coeffs;
	size_t poly_size;

private:
	class Iterator
	{
	public:
		Iterator(T* p) : ptr(p) { ; }
		Iterator& operator++() { ++ptr; return *this; }
		Iterator operator++(int) {Iterator temp(*this); operator++(); return temp;}
		bool operator==(const Iterator&);
		bool operator!=(const Iterator&);
		T& operator*() { return *ptr; }


	private:
		T* ptr;
	};

	void setCoeffs(const T* arr);
	Iterator begin() const { return Iterator(coeffs); }
	Iterator end() const { return Iterator(coeffs+poly_size); }
};

template<typename T>
Poly<T>::Poly(const T* arr, size_t num) : poly_size(num)
{
	setCoeffs(arr);
}

template<typename T>
Poly<T>::~Poly()
{
	delete[] coeffs;
}

template<typename T>
bool Poly<T>::Iterator::operator==(const Iterator& other)
{
	if (ptr == other.ptr)
		return true;

	return false;
}

template<typename T>
bool Poly<T>::Iterator::operator!=(const Iterator& other)
{
	return !(*this == other);
}

template<typename T>
void Poly<T>::setCoeffs(const T* arr)
{
	T* newMem = new T[poly_size];

	for (size_t i = 0; i < poly_size; ++i)
		newMem[i] = arr[i];

	if (coeffs) delete[] coeffs;
	coeffs = newMem;
}

template<typename T>
void Poly<T>::printPoly() const
{
	size_t cnt = 0;
	for (Iterator it = begin(); it != end(); ++it)
	{
		if (*it)
			std::cout << *it << "x^" << cnt << ' ';
		++cnt;
	}
}
template<typename T>
bool Poly<T>::operator==(const Poly<T>& other) const
{
	if (poly_size != other.poly_size)
		return false;
	
	Iterator other_it = other.begin();
	
	for(Iterator it = begin(); it!= end(); ++it, ++other_it)
		if (it != other_it)
			return false;

	return true;
}

template<typename T>
bool Poly<T>::operator<(const Poly<T>& other) const
{
	if (poly_size < other.poly_size)
		return true;

	return false;
}

template<typename T>
bool Poly<T>::operator>(const Poly<T>& other) const
{
	return (other < *this);
}

template<typename T>
Poly<T>& Poly<T>::operator+=(const Poly<T>& other)
{
	if (poly_size < other.poly_size)
	{
		T* newMem = new T[other.poly_size];

		for (Iterator it = begin(); it != end(); ++it)
		{
			*newMem = *it;
			++newMem;
		}

		for (Iterator it = end(); it != other.end(); ++it)
		{
			*newMem = 0;
			++newMem;
		}

		delete[] coeffs;
		coeffs = newMem;
		poly_size = other.poly_size;
	}

	Iterator other_it = other.begin();

	for(Iterator it = begin(); it != end(); ++it, ++other_it)
		*it += *other_it;

	return *this;
}

template<typename T>
Poly<T>& Poly<T>::operator-=(const Poly<T>& other)
{

	if (poly_size < other.poly_size)
	{
		T* newMem = new T[other.poly_size];

		for (Iterator it = begin(); it != end(); ++it)
		{
			*newMem = *it;
			++newMem;
		}

		for (Iterator it = end(); it != other.end(); ++it)
		{
			*newMem = 0;
			++newMem;
		}

		delete[] coeffs;
		coeffs = newMem;
		poly_size = other.poly_size;
	}

	Iterator other_it = other.begin();

	for (Iterator it = begin(); it != end(); ++it, ++other_it)
		*it -= *other_it;

	return *this;
}

template<typename T>
T& Poly<T>::operator[](size_t index)
{
	T num = 0;
	if (index >= poly_size)
		return num;

	return coeffs[index];
}

template<typename T>
const T Poly<T>::operator[] (size_t index) const
{
	T num = 0;
	if (index >= poly_size)
		return num;

	return coeffs[index];
}

#endif //POLY_HDR
