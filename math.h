#ifndef MATH_H
#define MATH_H

#include <iostream>

using std::endl;
using std::cout;
using std::cin;

class math {
private:
	int number1, number2;
public:
	math(int n1, int n2);
	~math();

	int sum();

	int unsum();
};

#endif
