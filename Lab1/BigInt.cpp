#include "BigInt.h"
#include <iostream>

BigInt::BigInt()
{
	isNegative = false;
	value = std::string();
	//засунуть 0 по дефолту?
}

BigInt::BigInt(int n)
{
	isNegative = (n < 0) ? true : false;
	value = std::to_string(abs(n));
}

BigInt::BigInt(std::string s)
{
	if (s[0] == '-') {
		isNegative=true;
		value = std::string(s.substr(1,s.length()-1));
	}
	else {
		isNegative = false;
		value = std::string(s);
	}
}

BigInt::BigInt(const BigInt& n)
{
	isNegative = n.isNegative;
	value = std::string(n.value);
}

BigInt::~BigInt()
{

}

BigInt& BigInt:: operator=(const BigInt& n)
{
	this->isNegative = n.isNegative;
	this->value = n.value;
	return *this;
}

//BigInt BigInt::operator~() const {}

BigInt& BigInt::operator++() 
{
	return *this += 1;
}

const BigInt BigInt::operator++(int) const 
{
	BigInt tmp = BigInt(*this);
	++(const_cast<BigInt&>(*this));
	return tmp;
}

BigInt& BigInt::operator--() 
{
	return *this -= 1;
}

const BigInt BigInt::operator--(int) const 
{
	BigInt tmp = BigInt(*this);
	--(const_cast<BigInt&>(*this));
	return tmp;
}

BigInt& BigInt::operator+=(const BigInt& n) 
{
	//если разные знаки
	if (this->isNegative == false && n.isNegative) {
		return *this -= (-n);
	}
	else if (this->isNegative && n.isNegative==false) {
		*this = (const_cast<BigInt&>(n) -= -(*this));///?????
		return *this;
	}

	//вариант для беззнаковых чисел
	int thisLen = this->value.length(), nLen = n.value.length(), lim{ 0 };
	std::string buf{}, a{}, b{};

	for (int i{ 0 }; i < abs(nLen - thisLen); ++i) {a.append("0");}

	if (thisLen < nLen) {
		a += this->value;
		b = n.value;
		lim = nLen;
	}
	else {
		a += n.value;
		b = this->value;
		lim = thisLen;
	}
	
	//сложение "в тупую". всё в char
	for (int i{ 0 }; i < lim; ++i) {buf+=((b[i]-'0') + (a[i]-'0'));}

	//работа с переносами
	for (int i= lim - 1 ; i >= 0; --i) {
		if (buf[i] > 9) {
			if (i - 1 < 0) {
				buf = " " + buf;
				buf[i] -= 31;//костыль
				++i;
			}
			else {
				++buf[i - 1];
			}
			buf[i] -= 10;
		}
	}

	//приведение в читабельный вид вместо stoi, тк может встретиться \0 
	int bufLen = buf.length();
	for (int i = 0; i < bufLen; ++i) {buf[i]=((buf[i])+'0');}
	this->value = buf;

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& n) 
{
	BigInt res = BigInt(0);
	BigInt fst = (this->isNegative) ? -(*this) : *this;
	BigInt lim = (n.isNegative) ? -n : n;
	for (int i{ 0 }; i < lim; ++i) {
		res += fst;
	}
	*this = (this->isNegative!=n.isNegative ) ? -res : res;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& n)
{
	//если разные знаки
	if (this->isNegative != n.isNegative) {
		return *this += -n;
	}
	// если оба отрицательные
	else if (this->isNegative) {
		*this = (-n) -= -(*this);
		return *this;
	}

	//вариант для беззнаковых чисел
	int thisLen = this->value.length(), nLen = n.value.length(), lim{ 0 };
	std::string buf{}, a{}, b{};

	for (int i{ 0 }; i < abs(nLen - thisLen); ++i) {a.append("0");}

	if (thisLen < nLen || (thisLen == nLen && *this < n)) {
		a += this->value;
		b = n.value;
		lim = nLen;
	}
	else {
		a += n.value;
		b = this->value;
		lim = thisLen;
	}

	//вычисления и переносы b-a
	for (int i = lim - 1; i >= 0; --i) {
		if (b[i] - '0' >= a[i] - '0') {
			buf += (b[i] - '0') - (a[i] - '0');
		}
		else {
			--b[i - 1];
			b[i] =b[i]+ 10;
			buf += (b[i] - '0') - (a[i] - '0');
		}
	}

	int bufLen = buf.length();
	for (int i = 0; i < bufLen; ++i) {buf[i] = ((buf[i]) + '0');}

	//на случай, если останется 0 в начале. такое случается при вычитании однозначного из двухзначного
	while (&buf.front()!=&buf.back() && buf.back()=='0') {buf.pop_back();}
	reverse(buf.begin(), buf.end());

	//уточнение знака
	if (*this < n) {this->isNegative = true;}

	this->value = buf;

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& n) 
{
	if (n == BigInt(0)) throw std::invalid_argument("Division by zero.");
	BigInt cnt = BigInt(0);
	BigInt fst = (this->isNegative) ? -(*this) : *this;
	BigInt snd = (n.isNegative) ? -n : n;

	while (BigInt(0) <= (fst -= snd)) {++cnt;}
	*this = (this->isNegative != n.isNegative) ? -cnt : cnt;
	return *this;
}

//BigInt& BigInt::operator^=(const BigInt&) {}

BigInt& BigInt::operator%=(const BigInt& n) 
{
	*this = (*this)-(n*(*this / n));
	return *this;

}

//BigInt& BigInt::operator&=(const BigInt&) {}
//BigInt& BigInt::operator|=(const BigInt&) {}

// unary +
BigInt BigInt::operator+() const
{
	return *this;
}

// unary -
BigInt BigInt::operator-() const
{
	BigInt n = BigInt(this->value);
	n.isNegative = !(this->isNegative);
	return n;
}

bool BigInt::operator==(const BigInt& n) const
{
	return (n.isNegative == this->isNegative && (this->value == n.value));
}

bool BigInt::operator!=(const BigInt& n) const 
{
	return !(this->operator==(n));
}

bool BigInt::operator<(const BigInt& n) const 
{
	//пофиксить 50<48 == 1 kek
	int nLen= n.value.length(), thisLen= this->value.length(); 
	if (thisLen < nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? false : true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {

		for (int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] < n.value[i]) {
				return (n.isNegative) ? false : true;
			}
			else if (this->value[i] > n.value[i]) {
				return (n.isNegative) ? true : false;
			}
		}
	}
	//либо 1 >2 по длине,либо разные знаки
	else if (thisLen > nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? true : false;
	}
	else if (this->isNegative) {
		return true;
	}
	return false;
}

bool BigInt::operator>(const BigInt& n) const 
{	
	int nLen= n.value.length() , thisLen= this->value.length(); 
	if (thisLen > nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? false : true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {
		for (int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] > n.value[i]) {
				return (n.isNegative) ? false : true;
			}
			else if(this->value[i] < n.value[i]){
				return (n.isNegative) ? true : false;
			}
		}
	}
	//либо 1 < 2 по длине,либо разные знаки
	else if (thisLen < nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? true : false;
	}
	else if (n.isNegative) {
		return true;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& n) const
{
	return !(this->operator>(n));
}

bool BigInt::operator>=(const BigInt& n) const
{
	return !(this->operator<(n));
}

BigInt::operator int() const
{
	int n = std::stoi(this->value);
	return (this->isNegative) ? (-n) : n;
}

BigInt::operator std::string() const
{
	return (this->isNegative) ? ("-" + this->value) : this->value;
}

size_t BigInt::size() const
{
	return sizeof(isNegative) + this->value.size();
}

BigInt operator+(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) += b;
}

BigInt operator-(const BigInt& a , const BigInt& b) 
{
	return BigInt(a) -= b;
}

BigInt operator*(const BigInt& a, const BigInt& b) 
{
	BigInt res = BigInt(0);
	BigInt fst = (a.isNegative) ? -a : a;
	BigInt lim = (b.isNegative) ? -b : b;

	for (int i{ 0 }; i < lim; ++i) {
		res += fst;
	}
	return (a.isNegative != b.isNegative) ? -res : res;
}

BigInt operator/(const BigInt& a, const BigInt& b) 
{
	if (b == BigInt(0)) throw std::invalid_argument("Division by zero.");
	BigInt cnt = BigInt(0);
	BigInt fst = (a.isNegative) ? -a : a;
	BigInt snd = (b.isNegative) ? -b : b;

	while (BigInt(0) <= (fst -= snd)) {++cnt;}
	return (a.isNegative != b.isNegative) ? -cnt : cnt;
}

//BigInt operator^(const BigInt&, const BigInt&) {}

BigInt operator%(const BigInt& a, const BigInt& b) 
{
	BigInt res = BigInt(a - (b * (a / b)));
	return res;
}

//BigInt operator&(const BigInt&, const BigInt&) {}
//BigInt operator|(const BigInt&, const BigInt&) {}

std::ostream& operator<<(std::ostream& o, const BigInt& i) 
{
	return (i.isNegative) ? (o << '-' << i.value) : (o << i.value);
}