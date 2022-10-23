#include <iostream>
#include "BigInt.h"

int main() {
	BigInt a = BigInt("6");
	BigInt b = BigInt("124");
	
	std::cout << (a / b)<<std::endl;


	return 0;
}