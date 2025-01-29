#include "math.h"
#include <iostream>

using std::endl;
using std::cout;
using std::cin;

math::math(int n1, int n2): number1(n1), number2(n2) {}
math::~math() {
	cout << "math удален!" << endl;
}

int math::sum() {
	return number1 + number2;
}

int math::unsum() {
	return number1 - number2;
}