#include <iostream>
#include "BigInt.h"
#include <assert.h>

int main() {
	BigInt a = BigInt("300");
	BigInt b = BigInt(0);
	
	std::cout << (a/=b) << std::endl;
	//std::cout << (-50%6)<<std::endl;
	return 0;
}