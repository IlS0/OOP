#include <iostream>
#include "BigInt.h"

int main() {
	BigInt a = BigInt(-13);
	BigInt b = BigInt(-144);
	std::cout << (a>b)<<std::endl;


	return 0;
}