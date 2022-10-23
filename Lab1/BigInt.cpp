#include "BigInt.h"
#include <iostream>

BigInt::BigInt()
{
	isNegative = false;
	value = std::string();
	//�������� 0 �� �������?
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
	return ++(const_cast<BigInt&>(*this));
}

BigInt& BigInt::operator--() 
{
	return *this -= 1;
}

const BigInt BigInt::operator--(int) const 
{
	return --(const_cast<BigInt&>(*this));
}

BigInt& BigInt::operator+=(const BigInt& n) 
{
	//���� ������ �����
	if (this->isNegative == false && n.isNegative) {
		return *this -= (-n);
	}
	else if (this->isNegative && n.isNegative==false) {
		*this = (const_cast<BigInt&>(n) -= -(*this));///?????
		return *this;
	}

	//������� ��� ����������� �����
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
	
	//�������� "� �����". �� � char
	for (int i{ 0 }; i < lim; ++i) {buf+=((b[i]-'0') + (a[i]-'0'));}

	//������ � ����������
	for (int i= lim - 1 ; i >= 0; --i) {
		if (buf[i] > 9) {
			if (i - 1 < 0) {
				buf = " " + buf;
				buf[i] -= 31;//�������
				++i;
			}
			else {
				++buf[i - 1];
			}
			buf[i] -= 10;
		}
	}

	//���������� � ����������� ��� ������ stoi, �� ����� ����������� \0 
	int bufLen = buf.length();
	for (int i = 0; i < bufLen; ++i) {buf[i]=((buf[i])+'0');}
	this->value = buf;

	return *this;
}

//BigInt& BigInt::operator*=(const BigInt&) {}

BigInt& BigInt::operator-=(const BigInt& n)
{
	//���� ������ �����
	if (this->isNegative != n.isNegative) {
		return *this += -n;
	}
	// ���� ��� �������������
	else if (this->isNegative) {
		*this = (-n) -= -(*this);
		return *this;
	}

	//������� ��� ����������� �����
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

	//���������� � �������� b-a
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

	//�� ������, ���� ��������� 0 � ������. ����� ��������� ��� ��������� ������������ �� ������������
	while (&buf.front()!=&buf.back() && buf.back()=='0') {buf.pop_back();}
	reverse(buf.begin(), buf.end());

	//��������� �����
	if (*this < n) {this->isNegative = true;}

	this->value = buf;

	return *this;
}

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
	unsigned int nLen{ n.value.length() }, thisLen{ this->value.length() }; //�� ������ �������
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
	//���� 1 >2 �� �����,���� ������ �����
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
	unsigned int nLen{ n.value.length() }, thisLen{ this->value.length() }; //�� ������ �������
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
	//���� 1 < 2 �� �����,���� ������ �����
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

//BigInt operator*(const BigInt&, const BigInt&) {}
//BigInt operator/(const BigInt&, const BigInt&) {}
//BigInt operator^(const BigInt&, const BigInt&) {}
//BigInt operator%(const BigInt&, const BigInt&) {}
//BigInt operator&(const BigInt&, const BigInt&) {}
//BigInt operator|(const BigInt&, const BigInt&) {}

std::ostream& operator<<(std::ostream& o, const BigInt& i) 
{
	return (i.isNegative) ? (o << '-' << i.value) : (o << i.value);
}