#pragma once
#include <string>

class BigInt {
public:
	BigInt();
	BigInt(int);
	BigInt(std::string); // áðîñàòü èñêëþ÷åíèå std::invalid_argument ïðè îøèáêå
	BigInt(const BigInt&);
	~BigInt();

	BigInt& operator=(const BigInt&);  //âîçìîæíî ïðèñâàèâàíèå ñàìîìó ñåáå!

	BigInt operator~() const;

	BigInt& operator++();
	const BigInt operator++(int) const;
	BigInt& operator--();
	const BigInt operator--(int) const;

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes

//private:
	std::string value;
	bool isNegative;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);