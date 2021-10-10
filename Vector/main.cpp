#include <iostream>
#include "Vector.h"

int main() {
	const IntVector vec1{3, 4, 5, 6, 7, 8};
	std::cout << vec1.Size();
}