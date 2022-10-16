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

//BigInt& BigInt:: operator=(const BigInt&) {}
//
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
//
//BigInt BigInt::operator+() const {}  // unary +
//BigInt BigInt::operator-() const {}  // unary -
//
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
		if (n.isNegative)
			return false;
		else
			return true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {
		for (unsigned int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] < n.value[i]) {
				if (n.isNegative)
					return false;
				else
					return true;
			}
		}
	}
	else if (this->isNegative == true) {
		return true;
	}
	return false;
}

bool BigInt::operator>(const BigInt& n) const 
{	
	if (this->operator==(n))
		return false;

	unsigned int nLen{ n.value.length() }, thisLen{ this->value.length() }; //мб убрать ансайнд
	if (thisLen > nLen && n.isNegative == this->isNegative) {
		if (n.isNegative)
			return false;
		else
			return true;
	}
	else if (thisLen == nLen && n.isNegative == this->isNegative) {
		for (unsigned int i{ 0 }; i < nLen; ++i) {
			if (this->value[i] > n.value[i]) {
				if (n.isNegative)
					return false;
				else
					return true;
			}
		}
		if (!n.isNegative)
			return false;
		else
			return true;
	}

	else if (n.isNegative != this->isNegative) {
		if (this->isNegative == false) {
			return true;
		}
		else
			return false;
	}

	else if(thisLen < nLen)
		if (!n.isNegative)
			return false;
		else
			return true;
	
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
//
//BigInt::operator int() const {}
//BigInt::operator std::string() const {}
//
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
	if (i.isNegative) {o << '-';}
	return o << i.value;
}