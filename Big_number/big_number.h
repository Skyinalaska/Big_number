//#ifndef BIG_NUMBER_H
//#define BIG_NUMBER_H
#pragma once
#include <iostream>
#include <string>

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
    base *head;
    base *tail;
    base *alloc;

    void Resize(int);
    Big_number(base* _head, base* _tail);

	void left_shift(int);

public:
	void right_shift(int);
	void mod_base_in_degree(int);
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

    void operator =(const Big_number &a);
    void operator =(int a);

    Big_number Mul_by_Karacuba(Big_number&, Big_number&);
    void Pow(Big_number, Big_number);
	Big_number Mod_by_Barret(Big_number&, Big_number&);
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

};

//#endif // BIG_NUMBER_H
