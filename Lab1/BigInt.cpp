#include "BigInt.h"

BigInt::BigInt() {}

BigInt::BigInt(int) {}

BigInt::BigInt(std::string) {}

BigInt::BigInt(const BigInt&) {}

BigInt::~BigInt() {}

BigInt& BigInt:: operator=(const BigInt&){}

BigInt BigInt::operator~() const{}

BigInt& BigInt::operator++(){}

const BigInt BigInt::operator++(int) const{}

BigInt& BigInt::operator--(){}

const BigInt BigInt::operator--(int) const{}

BigInt& BigInt::operator+=(const BigInt&){}
BigInt& BigInt::operator*=(const BigInt&){}
BigInt& BigInt::operator-=(const BigInt&){}
BigInt& BigInt::operator/=(const BigInt&){}
BigInt& BigInt::operator^=(const BigInt&){}
BigInt& BigInt::operator%=(const BigInt&){}
BigInt& BigInt::operator&=(const BigInt&){}
BigInt& BigInt::operator|=(const BigInt&){}

BigInt BigInt::operator+() const {}  // unary +
BigInt BigInt::operator-() const {}  // unary -

bool BigInt::operator==(const BigInt&) const{}
bool BigInt::operator!=(const BigInt&) const{}
bool BigInt::operator<(const BigInt&) const{}
bool BigInt::operator>(const BigInt&) const{}
bool BigInt::operator<=(const BigInt&) const{}
bool BigInt::operator>=(const BigInt&) const{}

BigInt::operator int() const{}
BigInt::operator std::string() const{}

size_t BigInt::size() const {}


//Разобраться с определением и объявлением
BigInt operator+(const BigInt&, const BigInt&){}
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i) {}
