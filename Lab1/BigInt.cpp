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
//
//BigInt& BigInt::operator++() {}
//
//const BigInt BigInt::operator++(int) const {}
//
//BigInt& BigInt::operator--() {}
//
//const BigInt BigInt::operator--(int) const {}
//
//BigInt& BigInt::operator+=(const BigInt&) {}
//BigInt& BigInt::operator*=(const BigInt&) {}
//BigInt& BigInt::operator-=(const BigInt&) {}
//BigInt& BigInt::operator/=(const BigInt&) {}
//BigInt& BigInt::operator^=(const BigInt&) {}
//BigInt& BigInt::operator%=(const BigInt&) {}
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
	unsigned int nLen{ n.value.length() }, thisLen{ this->value.length() }; //мб убрать ансайнд
	if (thisLen < nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? false : true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {
		for (unsigned int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] < n.value[i]) {
				return (n.isNegative) ? false : true;
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
	unsigned int nLen{ n.value.length() }, thisLen{ this->value.length() }; //мб убрать ансайнд
	if (thisLen > nLen && n.isNegative == this->isNegative) {
		return (n.isNegative) ? false : true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {
		for (unsigned int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] > n.value[i]) {
				return (n.isNegative) ? false : true;
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

//
//BigInt operator+(const BigInt&, const BigInt&) {}
//BigInt operator-(const BigInt&, const BigInt&) {}
//BigInt operator*(const BigInt&, const BigInt&) {}
//BigInt operator/(const BigInt&, const BigInt&) {}
//BigInt operator^(const BigInt&, const BigInt&) {}
//BigInt operator%(const BigInt&, const BigInt&) {}
//BigInt operator&(const BigInt&, const BigInt&) {}
//BigInt operator|(const BigInt&, const BigInt&) {}


std::ostream& operator<<(std::ostream& o, const BigInt& i) 
{
	//if (i.isNegative) {o << '-';}
	//return o << i.value;
	return (i.isNegative) ? (o << '-' << i.value) : (o << i.value);
}