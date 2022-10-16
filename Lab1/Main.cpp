#include <iostream>
#include "BigInt.h"

int main() {
	BigInt a = BigInt(-12);
	BigInt b = BigInt(-12222);
	std::cout << (a>=b);

	// a ==b
	// a <b, len a < len b 
	// a < b, len a == len b
	// a > b, len a == len b
	// a > b, len a > len b
	// a < b, a<0, b<0
	return 0;
}