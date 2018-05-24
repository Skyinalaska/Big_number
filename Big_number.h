//#ifndef BIG_NUMBER_H
//#define BIG_NUMBER_H
#pragma once
#include <iostream>
#include <cstring>

typedef int BigError;
typedef unsigned int base;
typedef unsigned long long d_base;

namespace BigErrors {
	static const BigError OK = 0;
	static const BigError INCORRECT_SYMBOL = 1;
	static const BigError INCOMPATIBLE_OPERANDS = 2;
	static const BigError DIV_ZERO = 3;
}
class Big_number
{
private:
	base * head;
	base *tail;
	base *alloc;

	void Resize(int);
	Big_number(base* _head, base* _tail);

public:
	Big_number();
	Big_number(const Big_number &);
	~Big_number();

	int GetCapacity() const;
	int GetLength() const;
	int Rand(int bound);
	void Compress();

	friend int Compare(const Big_number &b, const Big_number &a);
	friend int Compare_with_zero(const Big_number &b);
	friend bool operator>(Big_number &a, Big_number &b);
	friend bool operator<(Big_number &a, Big_number &b);
	friend bool operator>=(Big_number &a, Big_number &b);
	friend bool operator<=(Big_number &a, Big_number &b);
	friend bool operator==(Big_number &a, Big_number &b);
	friend bool operator!=(Big_number &a, Big_number &b);

	void operator =(const Big_number &a);
	void operator =(int a);

	Big_number Karacuba(Big_number&, Big_number&);
	void Pow(Big_number, Big_number);
	Big_number Mul(base);
	Big_number Div(base, base&);
	friend Big_number Division(Big_number&, Big_number&, Big_number&);

	friend Big_number operator+(Big_number &a, Big_number &b);
	friend Big_number operator-(Big_number &a, Big_number &b);
	friend Big_number operator*(Big_number &a, Big_number &b);
	friend Big_number operator/(Big_number &a, Big_number &b);
	friend Big_number operator%(Big_number &a, Big_number &b);

	friend std::istream &operator >> (std::istream &in, Big_number &a);

	friend std::ostream &operator << (std::ostream &out, Big_number &a);

	void left_shift(int);
	void right_shift(unsigned int);

	Big_number Mod_by_Barret(Big_number& mod, Big_number& z);
	void mod_base_in_degree(int n);
	void z_for_Barret(Big_number& mod);
};

//#endif // BIG_NUMBER_H
