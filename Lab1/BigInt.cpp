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

std::string toBin(const BigInt& n)
{
	BigInt tmp = n;
	BigInt BI_zero = BigInt(0), BI_two = BigInt(2);
	std::string binNum{};

	while (tmp != BI_zero) {
		binNum.push_back((tmp.value.back() % 2)+'0');
		tmp /= BI_two;
	}

	if (!binNum.length())
		binNum.push_back('0');
	else 
		reverse(binNum.begin(), binNum.end());
	return binNum;
}

BigInt toDec(const std::string n)
{
	int bLen= n.length();
	BigInt pow = BigInt(1),decNum = BigInt(0),BI_two = BigInt(2);

	for (int i{ bLen-2 }; i>=0;--i) {	
		pow *= BI_two;
		if (n[i]!='0')
			decNum += pow;
	}
	decNum += n[bLen - 1]-'0';
	return decNum;
}

BigInt& BigInt::operator=(const BigInt& n)
{
	this->isNegative = n.isNegative;
	this->value = n.value;
	return *this;
}

BigInt BigInt::operator~() const 
{
	std::string bThis{ toBin(*this) };
	int len = bThis.length();
	for (int i{ 0 }; i < len; ++i) {
		 bThis[i] = ~(bThis[i]/*-'0'*/);
	}
	BigInt res = BigInt(toDec(bThis));
	return res;
}

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

BigInt& BigInt::safePlus(const BigInt& n)
{
	//вариант для беззнаковых чисел
	int thisLen = this->value.length(), nLen = n.value.length(), lim{ 0 };
	std::string buf{}, a{}, b{};

	for (int i{ 0 }; i < abs(nLen - thisLen); ++i) { a.append("0"); }

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
	for (int i{ 0 }; i < lim; ++i) { buf += ((b[i] - '0') + (a[i] - '0')); }

	//работа с переносами
	for (int i = lim - 1; i >= 0; --i) {
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
	for (int i = 0; i < bufLen; ++i) { buf[i] = ((buf[i]) + '0'); }
	this->value = buf;

	return *this;
}

BigInt& BigInt::operator+=(const BigInt& n) 
{
	if (this->isNegative == false && n.isNegative) {
		return safeMinus(-n);
	}
	else if (this->isNegative && n.isNegative==false) {
		BigInt tmp = BigInt(-*this);
		*this = n;
		return safeMinus(tmp);
		//изначальный вариант
		//*this = (const_cast<BigInt&>(n) -= -(*this));
		//return *this;
	}
	return safePlus(n);
}

BigInt& BigInt::operator*=(const BigInt& n) 
{
	int thisLen = this->value.length(), nLen = n.value.length(), limF{ 0 }, limS{ 0 },zeroCnt{ 0 };
	std::string buf{}, fst{}, snd{};
	BigInt res = BigInt(0);

	if (thisLen < nLen) {
		snd = this->value;
		fst = n.value;
		limF = nLen;
		limS = thisLen;
		zeroCnt = thisLen-1;
	}
	else {
		snd = n.value;
		fst = this->value;
		limF = thisLen;
		limS = nLen;
		zeroCnt = nLen-1;
	}

	for (int i{ limS -1}; i >= 0; --i) {
		//тупое перемножение
		for (int j{ limF - 1 }; j >= 0; --j) {
			buf += ((fst[j] - '0') * (snd[i] - '0'));
		}

		//работа с переносами
		for (int k{ 0 }; k < limF; ++k) {
			if (buf[k] > 9) {
				char f{ buf[k] / 10 }, s{ buf[k] % 10 };//возможно сделать инт?
				buf[k] = s + '0';
				if (k + 1 >= limF) {
					buf += (f + '0');
				}
				else {
					buf[k + 1] += f;
				}
			}
			else {
				buf[k] += '0';
			}	
		}
		//получается обратная запись одного из слагаемых

		//если результат - 0, то удаляем лишние
		while (&buf.front() != &buf.back() && buf.back() == '0') { buf.pop_back(); }

		reverse(buf.begin(), buf.end());
		//добавление нулей к слагаемым
		for (int k{ 0 }; k < zeroCnt -i; ++k) {buf.push_back('0');}
		res += BigInt(buf);
		buf.clear();
	}

	*this = (this->isNegative != n.isNegative && !(res == BigInt(0))) ? -res : res;
	return *this;
}

BigInt& BigInt::safeMinus(const BigInt& n)
{
	//вариант для беззнаковых чисел
	int thisLen = this->value.length(), nLen = n.value.length(), lim{ 0 };
	std::string buf{}, a{}, b{};

	for (int i{ 0 }; i < abs(nLen - thisLen); ++i) { a.append("0"); }

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
			buf += ((b[i] - '0') - (a[i] - '0')) + '0';//!
		}
		else {
			--b[i - 1];
			b[i] = b[i] + 10;
			buf += ((b[i] - '0') - (a[i] - '0')) + '0';//!!
		}
	}

	//int bufLen = buf.length();
	//for (int i = 0; i < bufLen; ++i) {buf[i] = ((buf[i]) + '0');}

	//на случай, если останется 0 в начале. такое случается при вычитании однозначного из двухзначного
	while (&buf.front() != &buf.back() && buf.back() == '0') { buf.pop_back(); }
	reverse(buf.begin(), buf.end());

	//уточнение знака
	if (*this < n) { this->isNegative = true; }

	this->value = buf;

	return *this;
}

BigInt& BigInt::operator-=(const BigInt& n)
{
	//если разные знаки
	if (this->isNegative != n.isNegative) {
		return safePlus(-n);
	}
	// если оба отрицательные
	else if (this->isNegative) {
		BigInt tmp = BigInt(-*this);
		*this = -n;
		return safeMinus(tmp);
		//изначальный вариант
		//*this = (-n) -= -(*this);
		//return *this;
	}

	return safeMinus(n);
}

BigInt& BigInt::operator/=(const BigInt& n) 
{
	if (n == BigInt(0)) throw std::invalid_argument("Division by zero.");
	if (n == BigInt(1)) return *this;
	if (n == BigInt(-1)) {
		*this = -*this;
		return *this;
	}
	BigInt fst = (this->isNegative) ? -(*this) : *this,
		snd = (n.isNegative) ? -n : n, res=BigInt(0);

	//делимое меньше делителя по модулю => сразу 0
	if (fst < snd) {
		*this = BigInt(0);
		return *this;
	}
	
	int zeroAmount = fst.value.length()-snd.value.length();
	BigInt tenPow = BigInt(1), BI_ten = BigInt(10),tmp =BigInt(0);

	for (int i{ 0 }; i < zeroAmount; ++i) { tenPow *= BI_ten;}

	while (fst >= snd) {
		for (BigInt i = BigInt(1); i <= BI_ten; ++i) {
			if (tenPow * snd * i > fst) {
				tmp = (--i) * tenPow;
				break;
			}
		}
		fst -= tmp * snd;
		res += tmp;
		tenPow.value.erase(tenPow.value.end()-1);
		if (tenPow.value.empty()) {
			break;
		}
	}

	*this = (this->isNegative != n.isNegative && !(res == BigInt(0))) ? -res : res;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& n) 
{
	std::string bThis{ toBin(*this) }, bNum{ toBin(n) }, bRes{ };
	int thisLen = bThis.length(), numLen = bNum.length(), maxLen = 0, shift = abs(thisLen - numLen);
	bool thisIsLonger = false;
	if (thisLen > numLen) {
		maxLen = thisLen;
		thisIsLonger = true;
	}
	else { maxLen = numLen; }

	for (int i{ 0 }; i < maxLen; ++i) {
		if (i < shift) {
			bRes += (thisIsLonger) ? bThis[i] : bNum[i];
		}
		else {
			if (thisIsLonger)
				bRes += (bThis[i] - '0' ^ bNum[i - shift] - '0') + '0';
			else
				bRes += (bThis[i - shift] - '0' ^ bNum[i] - '0') + '0';
		}
	}

	this->value = toDec(bRes).value;
	this->isNegative = (this->isNegative != n.isNegative) ? true : false;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& n) 
{
	*this -= (n*(*this / n));
	return *this;
}

BigInt& BigInt::operator&=(const BigInt& n) 
{
	std::string bThis{ toBin(*this) }, bNum{ toBin(n) }, bRes{ };
	int thisLen = bThis.length(), numLen = bNum.length(), maxLen{ 0 }, shift = abs(thisLen - numLen);
	bool thisIsLonger = false;
	if (thisLen > numLen) {
		maxLen = thisLen;
		thisIsLonger = true;
	}
	else {maxLen = numLen;}

	for (int i{ shift }; i < maxLen; ++i) {
		if (thisIsLonger)
			bRes += (bThis[i]-'0' && bNum[i - shift] - '0')+'0';
		else 
			bRes += (bThis[i - shift] - '0' && bNum[i] - '0')+'0';
	}	

	this->value = toDec(bRes).value;
	this->isNegative = (this->isNegative != n.isNegative) ? true : false;
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& n) 
{
	std::string bThis{ toBin(*this) }, bNum{ toBin(n) }, bRes{ };
	int thisLen = bThis.length(), numLen = bNum.length(), maxLen = 0, shift = abs(thisLen - numLen);
	bool thisIsLonger = false;

	if (thisLen > numLen) {
		maxLen = thisLen;
		thisIsLonger = true;
	}
	else { maxLen = numLen; }

	for (int i{ 0 }; i < maxLen; ++i) {
		if (i < shift) {
			bRes += (thisIsLonger) ? bThis[i] : bNum[i];
		}
		else {
			if (thisIsLonger)
				bRes += (bThis[i] - '0' || bNum[i - shift] - '0') + '0';
			else
				bRes += (bThis[i - shift] - '0' || bNum[i] - '0') + '0';
		}
	}

	this->value = toDec(bRes).value;
	this->isNegative = (this->isNegative != n.isNegative) ? true : false;
	return *this;
}

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
	return n < *this;
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
	return BigInt(a) *= b;
}

BigInt operator/(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) /= b;
}

BigInt operator^(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) ^= b;
}

BigInt operator%(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) %= b;
}

BigInt operator&(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) &= b;
}

BigInt operator|(const BigInt& a, const BigInt& b) 
{
	return BigInt(a) |= b;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) 
{
	return (i.isNegative) ? (o << '-' << i.value) : (o << i.value);
}