#include "big_number.h"
#include <iostream>
#include <string>

using namespace BigErrors;

#define LENGTH 100

/*
head - указатель на начало числа
tail - указатель на конец числа
alloc - количество выделенной памяти
length - мощность - количество блоков
capacity - емкость, количество выделенной памяти
*/

unsigned int nlz(base x)
{
	unsigned int result = sizeof(base) * 8, sdwig = sizeof(base) * 8 / 2, add = sdwig;
	while (add > 0)
	{
		if ((x >> sdwig) == 0)
		{
			result -= add; x <<= add;
			//            std::cout << "x >>" << sdwig << " = 0  " << "  result = " << result;
		}
		add /= 2;
		sdwig += add;

		//        std::cout << "   add = " << add << "   sdwig = " << sdwig << std::endl;
	}
	//    std::cout << std::endl << "result = " << result;
	return result;
}

Big_number Big_number::Karacuba(Big_number& a, Big_number& b)
{
	Big_number result;
	Big_number X0, X1, Y0, Y1;
	int n = 0;
	if (a.GetLength() > b.GetLength())
	{
		n = (a.GetLength() + 1) >>1;

		//Big_number X0(&a.head[0], &a.head[n-1]), X1(&a.head[n], a.tail);
		X0.head = a.head; X0.tail = &a.head[n - 1]; X0.alloc = X0.tail;
		X1.head = &a.head[n]; X1.tail = a.tail; X1.alloc = X1.tail;

		if (n >= b.GetLength())
		{
			//Big_number Y0(&b.head[0], b.tail), Y1; Y1 = 0;
			Y0.head = b.head; Y0.tail = b.tail; Y0.alloc = Y0.tail; Y1 = 0;
		}
		else
		{
			//Big_number Y0(&b.head[0], &b.head[n-1]) ,Y1(&b.head[n], b.tail);
			Y0.head = b.head; Y0.tail = &b.head[n - 1]; Y0.alloc = Y0.tail;
			Y1.head = &b.head[n]; Y1.tail = b.tail; Y1.alloc = Y1.tail;
		}
	}
	else
	{
		n = (b.GetLength() + 1) / 2;
		//Big_number Y0(&b.head[0], &b.head[n-1]) ,Y1(&b.head[n], b.tail);
		Y0.head = b.head; Y0.tail = &b.head[n - 1]; Y0.alloc = Y0.tail;
		Y1.head = &b.head[n]; Y1.tail = b.tail; Y1.alloc = Y1.tail;

		if (n >= a.GetLength())
		{
			//Big_number X0(&a.head[0], a.tail), X1; X1 = 0;
			X0.head = a.head; X0.tail = a.tail; X0.alloc = X0.tail; X1 = 0;
		}
		else
		{
			//Big_number X0(&a.head[0], &a.head[n-1]), X1(&a.head[n], a.tail);
			X0.head = a.head; X0.tail = &a.head[n - 1]; X0.alloc = X0.tail;
			X1.head = &a.head[n]; X1.tail = a.tail; X1.alloc = X1.tail;
		}
	}

	Big_number A, B, C, tmp1, tmp2;
	tmp1 = X0 + X1;
	tmp2 = Y0 + Y1;
	B.Resize(n * 4);
	C.Resize(n * 3);
	result.Resize(n * 4);
	if (X1.GetLength() < LENGTH || Y1.GetLength() < LENGTH)
		A = X1 * Y1;
	else
		A = X1.Karacuba(X1, Y1);

	if (X0.GetLength() < LENGTH || Y0.GetLength() < LENGTH)
		B = X0 * Y0;
	else
		B = X0.Karacuba(X0, Y0);

	if (tmp1.GetLength() < LENGTH || tmp2.GetLength() < LENGTH)
		C = tmp2 * tmp1;
	else
		C = tmp1.Karacuba(tmp1, tmp2);

	X0.head = NULL; X0.tail = NULL; X0.alloc = NULL;
	X1.head = NULL; X1.tail = NULL; X1.alloc = NULL;
	Y0.head = NULL; Y0.tail = NULL; Y0.alloc = NULL;
	Y1.head = NULL; Y1.tail = NULL; Y1.alloc = NULL;

	C = C - A; C = C - B;
	C.left_shift(n);

	for (int i = B.GetLength(); i < n * 2; i++)
	{
		B.head[i] = 0;
		B.tail++;
	}

	for (int i = 0; i < A.GetLength(); i++)
	{
		B.head[2 * n + i] = A.head[i];
		B.tail++;
	}
	result = C + B;
	return result;
}

void Big_number::left_shift(int n)
{
	if (this->GetCapacity() < this->GetLength() + n)
	{
		std::cout << "error";
		return;
	}

	for (int i = this->GetLength(); i > 0; i--)
	{
		this->head[i + n - 1] = this->head[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		this->head[i] = 0;
		this->tail++;
	}
}

//быть осторожней с конструктором, не определен alloc
//Big_number::Big_number(base* _head, base* _tail)
//{
//	head = _head;
//	tail = _tail;
//}

Big_number::Big_number()
{
	head = new base[1];
	tail = head;
	alloc = head + 1 - 1;
}

Big_number::~Big_number()
{
	if (head)
	{
		delete[] head;
		head = NULL;
	}
}

Big_number::Big_number(const Big_number &old_big)
{
	int capacity = old_big.alloc - old_big.head + 1;
	int length = old_big.tail - old_big.head + 1;

	head = new base[capacity];
	alloc = head + capacity - 1;
	tail = head;
	for (int i = 0; i < length; i++)
	{
		head[i] = old_big.head[i];
		tail++;
	}
	tail--;
}

void Big_number::Resize(int new_capacity)
{
	if (GetCapacity() < new_capacity)
	{
		if (head)
		{
			delete[] head;
		}
		head = new base[new_capacity];
		tail = head;
		alloc = head + new_capacity - 1;
	}
}

int Big_number::GetCapacity() const
{
	return alloc - head + 1;
}

int Big_number::GetLength() const
{
	return tail - head + 1;
}

int Big_number::Rand(int boundary)
{
	if (GetCapacity() <  boundary)
	{
		Resize(boundary + 1);
	}
	tail = head;
	alloc = head + GetCapacity() - 1;
	for (int i = 0; i < boundary; i++)
	{
		head[i] = rand();
		tail++;
	}
	tail--;
	return 0;
}

void Big_number::Compress()
{
	for (int i = GetLength() - 1; 0 <= i; i--)
	{
		if (head[i] != 0)
		{
			return;
		}
		tail--;
	}
}

/*1 - больше
* -1 меньше
* 0 - равно*/
int Compare(const Big_number& b, const Big_number& a)
{
	if (b.GetLength() > a.GetLength())
	{
		return 1;
	}
	else
		if (b.GetLength() < a.GetLength())
		{
			return -1;
		}
	for (int i = a.GetLength() - 1; 0 <= i; i--)
	{
		if (b.head[i] > a.head[i])
			return 1;
		else
			if (b.head[i] < a.head[i])
			{
				return -1;
			}
	}
	return 0;
}

int Compare_with_zero(const Big_number& a)
{
	for (int i = a.GetLength() - 1; 0 <= i; i--)
	{
		if (a.head[i] != 0)
		{
			return false;
		}
	}
	return true;
}

bool operator>(Big_number& a, Big_number& b)
{
	if (Compare(a, b) == 1) {
		return true;
	}
	return false;
}

bool operator<(Big_number& a, Big_number& b)
{
	if (Compare(a, b) == -1) {
		return true;
	}
	return false;
}

bool operator>=(Big_number& a, Big_number& b)
{
	int result = Compare(a, b);
	if ((result == 1) || (result == 0)) {
		return true;
	}
	return false;
}

bool operator<=(Big_number& a, Big_number& b)
{
	int result = Compare(a, b);
	if ((result == -1) || (result) == 0) {
		return true;
	}
	return false;
}

bool operator==(Big_number& a, Big_number& b)
{
	if (Compare(a, b) == 0)
	{
		return true;
	}
	return false;
}

bool operator!=(Big_number &a, Big_number &b)
{
	if (Compare(a, b) == 0)
	{
		return false;
	}
	return true;
}

Big_number Big_number::Mul(base small)
{
	Big_number result;

	if (0 == small)
	{
		result.head[0] = 0;
		result.tail = result.head;
		return result;
	}
	d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);

	if (result.GetCapacity() < GetLength() + 1) {
		result.Resize(GetLength() + 1);
	}

	d_base tmp;
	d_base carry = 0;
	result.tail = result.head;

	int i;
	for (i = 0; i < GetLength(); i++)
	{
		tmp = static_cast<d_base>(head[i]) * static_cast<base>(small) + carry;
		carry = tmp / mask;
		result.head[i] = static_cast<base>(tmp % mask);
		result.tail++;
	}

	result.head[i] = carry;
	result.Compress();
	return result;
}

Big_number Big_number::Div(base small, base &remainder)
{
	Big_number result;
	if (0 == small) {
		throw DIV_ZERO;
	}

	if (GetLength() <= 1 && 0 == head[0])  // comparison with zero
	{
		result.tail = result.head;
		result.head[0] = 0;
		remainder = small;
		return result;
	}

	result.Resize(GetCapacity());

	d_base t = 0;
	d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
	remainder = 0;

	result.tail = result.head + GetLength() - 1;
	for (int i = 0; i <result.GetLength(); i++)
	{
		result.head[i] = 0;
	}

	for (int i = GetLength() - 1; 0 <= i; i--)
	{
		t = static_cast<d_base>(head[i]) + static_cast<d_base>(remainder) * mask;
		result.head[i] = static_cast<base>(t / small);
		remainder = static_cast<base>(t % static_cast<d_base>(small));
	}

	result.Compress();
	return result;

}

// e/c
Big_number Division(Big_number &e, Big_number &c, Big_number &remainder)
{
	Big_number a, b, result;
	a.Resize(e.GetLength() + 1);

	a = e;
	b = c;

	int j = 0, n = b.GetLength(), m = a.GetLength() - n, flag;

	if (Compare_with_zero(e))
	{
		result.tail = result.head + 1;
		result.head[0] = 0;
		remainder.tail = remainder.head + 1;
		remainder.head[0] = 0;
		return result;
	}

	if (-1 == Compare(e, c))
	{
		result.tail = result.head;
		result.head[0] = 0;
		remainder = e;
		return result;
	}

	//if base div
	if (b.GetLength() <= 1)
	{
		base r;
		result = a.Div(b.head[0], r);
		remainder.head[0] = r;
		remainder.tail = remainder.head;
		return result;
	}

	d_base d, mask;
	mask = static_cast<d_base>(1) << (sizeof(base) * 8);
	d = mask / static_cast<d_base>(b.head[b.GetLength() - 1] + 1);

	a = a.Mul(static_cast<base>(d));
	if (a.GetLength() == e.GetLength())
	{
		a.tail++;
		a.head[a.GetLength() - 1] = 0;
	}
	b = b.Mul(static_cast<base>(d));

	d_base roof, left_part, right_part;
	Big_number glass, new_num, q;

	new_num.Resize(a.GetLength());
	q.Resize(a.GetLength());
	q.tail = q.head + m + 1;

	for (int i = 0; i < q.GetLength(); i++)
	{
		q.head[i] = 0;
	}

	base b1 = b.head[b.GetLength() - 1];
	base b2 = b.head[b.GetLength() - 2];
	base aj, aj1, aj2;
	for (j = 0; j <= m; j++)
	{
		aj = a.head[a.GetLength() - j - 1];
		aj1 = a.head[a.GetLength() - j - 2];
		aj2 = a.head[a.GetLength() - j - 3];

		if (aj == b1)
		{
			roof = mask - 1;
		}
		else
		{
			roof = (static_cast<d_base>(aj) * static_cast<d_base>(mask)
				+ static_cast<d_base>(aj1)) /
				static_cast<d_base>(b1);
		}

		//check uneq
		while (1)
		{
			left_part = static_cast<d_base>(b2) * roof;

			right_part = static_cast<d_base>(aj) * mask + static_cast<d_base>(aj1)
				- roof * static_cast<d_base>(b1);
			/*дальнейшее умножение приведет к переполнению,
			* а left_part переполнится никогда не может =>
			* нервенство не выполнено*/
			if (right_part >> sizeof(base) * 8)
			{
				break;
			}
			right_part = right_part * mask + static_cast<d_base>(aj2);
			if (left_part > right_part)
			{
				roof--;
			}
			else
				break;
		}
		//mul and sub

		new_num.tail = new_num.head;

		for (int i = 0; i <= n; i++)
		{
			new_num.head[n - i] = a.head[a.GetLength() - j - 1 - i];
			new_num.tail++;
		}
		new_num.tail--;

		flag = 0;
		glass = b.Mul(static_cast<base>(roof));
		while (-1 == Compare(new_num, glass))
		{
			roof--;
			flag = 1;
			glass = b.Mul(static_cast<base>(roof));
			exit(0);
		}

		int stored_length_new_num = new_num.GetLength();
		new_num = new_num - glass;

		if (stored_length_new_num > new_num.GetLength())
		{
			for (int i = new_num.GetLength(); i < stored_length_new_num; i++)
			{
				new_num.head[i] = 0;
				new_num.tail++;
			}
		}

		for (int i = 0; i <= n; i++)
		{
			a.head[a.GetLength() - j - 1 - i] = new_num.head[n - i];
		}

		if (flag)
		{
			roof--;
			a = a + b;
		}
		q.head[m - j] = static_cast<base>(roof);
	}
	base r;
	remainder = a.Div(d, r);
	q.Compress();
	return q;
}

void Big_number::Pow(Big_number y, Big_number m)
{
	Big_number z = *this;
	int n = nlz(y.head[y.GetLength() - 1]);
	n -= 2;
	for (int i = y.GetLength() - 1; i >= 0; i--)
	{
		while (n >= 0)
		{
			z = z * z;
			z = z % m;
			if ((y.head[i] >> n) & 1)
			{
				z = z * *this;
				z = z % m;
			}
			n--;
		}
		n = sizeof(base) * 8;
	}
	*this = z;
	//    return z;
}

Big_number operator+(Big_number&a, Big_number &b)
{
	Big_number result;
	d_base tmp;
	d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
	int carry = 0;
	int BLength = b.GetLength();
	int ALength = a.GetLength();
	int LessLength;
	int rcapacity, i;

	if (ALength <= BLength)
		LessLength = ALength;
	else
		LessLength = BLength;

	if (a.GetCapacity() <= b.GetCapacity())
	{
		rcapacity = b.GetCapacity();
	}
	else
	{
		rcapacity = a.GetCapacity();
	}

	if (rcapacity + 1 > result.GetCapacity())
	{
		result.Resize(rcapacity + 1);
	}

	result.tail = result.head;

	for (i = 0; i < LessLength; i++)
	{
		tmp = static_cast<d_base>(b.head[i]) +
			static_cast<d_base>(a.head[i]) + carry;
		result.head[i] = tmp % mask;
		carry = !!(tmp / mask);
		result.tail++;
	}

	if (i < ALength)
	{
		for (; i < ALength; i++)
		{
			tmp = a.head[i] + carry;
			result.head[i] = tmp % mask;
			result.tail++;
			carry = !!(tmp / mask);
		}
	}
	else
		if (i < BLength)
		{
			for (; i < BLength; i++)
			{
				tmp = b.head[i] + carry;
				result.head[i] = tmp % mask;
				result.tail++;
				carry = !!(tmp / mask);
			}
		}
	if (carry)
	{
		result.head[i] = carry;
		result.tail++;
	}
	result.tail--;
	result.Compress();
	return result;
}

Big_number operator -(Big_number& b, Big_number& a)
{
	int flag = Compare(b, a);
	if (-1 == flag)
	{
		std::cout << "invalid operation" << std::endl;
		throw INCOMPATIBLE_OPERANDS;
	}

	Big_number result;
	result.Resize(b.GetCapacity());
	result.tail = result.head;

	if (0 == flag)
	{
		result.head[0] = 0;
		return result;
	}
	int carry = 0, given = 0;
	d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
	d_base tmp0 = 0;
	d_base tmp1;

	int i;
	for (i = 0; i < a.GetLength(); i++)
	{
		result.tail++;
		tmp0 = static_cast<d_base>(a.head[i]) + static_cast<d_base>(carry);
		carry = 0;

		if (static_cast<d_base>(b.head[i]) < tmp0)
		{
			given = 1;
		}

		if (given) {
			tmp1 = static_cast<d_base>(b.head[i]) + mask - tmp0;
			result.head[i] = static_cast<base>(tmp1);
			carry = 1;
			given = 0;
		}

		else {
			result.head[i] = b.head[i] - static_cast<base>(tmp0);
		}
	}

	for (i; i < b.GetLength(); i++)
	{
		result.tail++;
		tmp0 = carry;
		carry = 0;
		if (static_cast<d_base>(b.head[i]) < tmp0)
		{
			given = 1;
		}

		if (given) {
			tmp1 = static_cast<d_base>(b.head[i]) + mask - static_cast<d_base>(tmp0);
			result.head[i] = tmp1;
			carry = 1;
			given = 0;
		}
		else {
			result.head[i] = static_cast<d_base>(b.head[i]) - static_cast<d_base>(tmp0);
		}
	}
	result.tail--;
	result.Compress();
	return result;
}

Big_number operator *(Big_number& b, Big_number& a)
{
	Big_number result;
	if (a.GetLength() <= 1) {
		result = b.Mul(a.head[0]);
		return result;
	}

	result.Resize(b.GetLength() + a.GetLength());

	d_base mask = static_cast<d_base>(1) << (sizeof(base) * 8);
	d_base tmp, carry = 0;

	for (int i = 0; i <result.GetCapacity(); i++)
	{
		result.head[i] = 0;
		result.tail++;
	}
	result.tail--;

	int i, j;
	for (j = 0; j < a.GetLength(); j++)
	{
		if (0 == a.head[j])
		{
			continue;
		}

		for (i = 0; i < b.GetLength(); i++)
		{
			tmp = static_cast<d_base>(b.head[i]) * static_cast<d_base>(a.head[j]) +
				static_cast<d_base>(result.head[i + j]) + carry;
			result.head[i + j] = static_cast<base>(tmp);
			carry = tmp >> sizeof(base) * 8;
		}
		result.head[i + j] = carry;
		carry = 0;
	}
	result.Compress();
	return result;
}

Big_number operator/(Big_number &a, Big_number &b)
{
	Big_number remainder;
	return Division(a, b, remainder);
}

Big_number operator%(Big_number &a, Big_number &b)
{
	Big_number remainder;

	Division(a, b, remainder);
	return remainder;
}

void Big_number::operator =(const Big_number & a)
{
	if (GetCapacity() < a.GetCapacity()) {
		Resize(a.GetCapacity());
	}

	tail = head;
	int length = a.GetLength();

	for (int i = 0; i < length; i++)
	{
		head[i] = a.head[i];
		tail++;
	}
	tail--;
}

void Big_number::operator =(int a)
{
	if (GetCapacity() < 1)
	{
		Resize(1);
	}

	tail = head;
	head[0] = a;
}

std::istream &operator >>(std::istream &in, Big_number &a)
{
	int block = sizeof(base) * 2;//количество цифр F в числе
	base tmp0, tmp1;
	int index;
	std::string string_for_num;
	in >> string_for_num;
	int string_length = string_for_num.length();
	int n = (string_length) / block + !!((string_length) % (block));
	if (n>a.GetCapacity())
	{
		a.Resize(n);
	}

	for (int k = 0; k < n; k++)
	{
		tmp0 = 0;
		tmp1 = 0;
		for (int i = 0; i< block; i++)
		{
			index = string_length - k * block - i - 1;
			if (index < 0)
				break;
			char symbol = string_for_num[index];
			if (symbol >= '0' && symbol <= '9')
			{
				tmp1 = symbol - 48;
			}
			else if (symbol >= 'a' && symbol <= 'f')
			{
				tmp1 = symbol - 87;  // 10 + symbol - 97;
			}
			else if (symbol >= 'A' && symbol <= 'F')
			{
				tmp1 = symbol - 55;  // symbol + 10 - 65
			}
			else
			{
				throw INCORRECT_SYMBOL;
			}
			tmp0 = tmp0 | (tmp1 << 4 * i);
		}
		a.head[k] = tmp0;
		a.tail++;
	}
	a.tail--;
	return in;
}

std::ostream &operator <<(std::ostream &out, Big_number &a)
{
	int block = sizeof(base) * 2;  // *8/4 how many numbers in the "base"
								   //int length = a.GetLength();
	int mask = 0xF;
	char tmp;
	unsigned int flag = 1;

	for (int i = a.GetLength() - 1; 0 <= i; i--)  // starting from the older
	{
		for (int l = (block - 1) * 4; l >= 0; l -= 4)
		{
			tmp = (a.head[i] & (mask << l)) >> l;  // get an each number from the block(one number - four bytes)
			if (tmp >= 0 && tmp <= 9)
			{
				if (flag && 0 == tmp)
				{
					continue;
				}
				flag = 0;
				tmp = tmp + '0';
				out << tmp;
			}
			else
				if (tmp >= 0xA && tmp <= 0xF)
				{
					tmp = tmp + 87;
					out << tmp;
					flag = 0;
				}
				else
				{
					throw INCORRECT_SYMBOL;
				}
		}
	}

	if (flag)
	{
		out << "0";
	}
	return out;
}


void Big_number::right_shift(unsigned int n)
{
	int i;
	int old_length = this->GetLength();
	for (i = 0; i < old_length; i++)
	{
		if ((i + n) < old_length)
		{
			head[i] = head[i + n];
		}
		else
		{
			head[i] = NULL;
			tail--;
		}
	}
}

void Big_number::mod_base_in_degree(int n)
{
	for (int i = GetLength() - 1; i >= n; i--)
	{
		head[i] = NULL;
		tail--;
	}
}

Big_number Big_number::Mod_by_Barret(Big_number& mod, Big_number& z)
{
	if (*this < mod)
	{
		return *this;
	}
	Big_number result = *this;
	int mod_length = mod.GetLength();
	result.right_shift(mod_length - 1);
	Big_number q = result * z;
	q.right_shift(mod_length + 1);
	//2
	Big_number r1 = *this;
	r1.mod_base_in_degree(mod_length + 1);
	if (r1.GetLength() > mod_length+1)
		std::cout << "ERROR" << std::endl;
	Big_number r2 = q * mod;
	r2.mod_base_in_degree(mod_length + 1);
	if (r2.GetLength() > mod_length+1)
		std::cout << "ERROR" << std::endl;
	//3
	if (r1 >= r2)
	{
		result = r1 - r2;
	}
	else
	{
		result.Resize(mod_length + 2);
		//std::cout << result.GetLength() << " r1 " << r1.GetLength() << std::endl;
		result = r1;
		//std::cout << "r1 = " << r1 <<std::endl;
		result.tail = result.head + mod_length + 1;
		result.head[mod_length + 1] = 1;
		//std::cout << "r2 = " << r2 << std::endl;
		//std::cout << "re = " << result << std::endl;
		if (r2 > result)
			std::cout << "ERROR" << std::endl;
		result = result - r2;
		//std::cout << "re = " << result << std::endl;
		if (result.GetLength() > mod_length+1)
			std::cout << "ERROR" << std::endl;

	}
	//
	while (result >= mod)
	{
	//	std::cout << "mod = " << mod << std::endl;
		result = result - mod;
		//std::cout << " re = " << result << std::endl;
	}
	return result;
	//4
}

void Big_number::z_for_Barret(Big_number& mod)
{
	Big_number b;
	unsigned int mod_length = mod.GetLength();
	b.Resize(2 * mod_length + 1);
	for (int i = 0; i < 2 * mod_length; i++)
	{
		b.head[i] = 0;
		b.tail++;
	}
	b.head[2 * mod_length] = 1;
	*this = b / mod;
}