#include "BigInt.h"


BigInt::BigInt()
{
	isNegative = false;
	value = std::string();
}

BigInt::BigInt(int n)
{
	isNegative = (n < 0) ? true : false;
	value = std::to_string(n);
}

BigInt::BigInt(std::string s)
{
	isNegative = (s[0] == '-') ? true : false;
	value = std::string(s);
}

BigInt::BigInt(const BigInt& n)
{
	isNegative = n.isNegative;
	value = std::string(n.value);
}

BigInt::~BigInt()
{

}

BigInt& BigInt:: operator=(const BigInt&) {}

BigInt BigInt::operator~() const {}

BigInt& BigInt::operator++() {}

const BigInt BigInt::operator++(int) const {}

BigInt& BigInt::operator--() {}

const BigInt BigInt::operator--(int) const {}

BigInt& BigInt::operator+=(const BigInt&) {}
BigInt& BigInt::operator*=(const BigInt&) {}
BigInt& BigInt::operator-=(const BigInt&) {}
BigInt& BigInt::operator/=(const BigInt&) {}
BigInt& BigInt::operator^=(const BigInt&) {}
BigInt& BigInt::operator%=(const BigInt&) {}
BigInt& BigInt::operator&=(const BigInt&) {}
BigInt& BigInt::operator|=(const BigInt&) {}

BigInt BigInt::operator+() const {}  // unary +
BigInt BigInt::operator-() const {}  // unary -

bool BigInt::operator==(const BigInt&) const {}
bool BigInt::operator!=(const BigInt&) const {}
bool BigInt::operator<(const BigInt&) const {}
bool BigInt::operator>(const BigInt&) const {}
bool BigInt::operator<=(const BigInt&) const {}
bool BigInt::operator>=(const BigInt&) const {}

BigInt::operator int() const {}
BigInt::operator std::string() const {}

size_t BigInt::size() const
{
	return sizeof(isNegative) + this->value.size();
}

BigInt operator+(const BigInt&, const BigInt&) {}
BigInt operator-(const BigInt&, const BigInt&) {}
BigInt operator*(const BigInt&, const BigInt&) {}
BigInt operator/(const BigInt&, const BigInt&) {}
BigInt operator^(const BigInt&, const BigInt&) {}
BigInt operator%(const BigInt&, const BigInt&) {}
BigInt operator&(const BigInt&, const BigInt&) {}
BigInt operator|(const BigInt&, const BigInt&) {}


std::ostream& operator<<(std::ostream& o, const BigInt& i) {}