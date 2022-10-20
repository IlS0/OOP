#include <iostream>
#include "BigInt.h"

int main() {
	BigInt a = BigInt(-5129);
	BigInt b = BigInt(1000);
	std::cout << (a+=b)<<std::endl;


	return 0;
}