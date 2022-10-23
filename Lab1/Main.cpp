#include <iostream>
#include "BigInt.h"

int main() {
	BigInt a = BigInt(5000);
	BigInt b = BigInt(-12);
	a++ ;
	std::cout << (a)<<std::endl;


	return 0;
}