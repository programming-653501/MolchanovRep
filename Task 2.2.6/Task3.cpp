#include <conio.h>
#include <math.h>
#include "get_value.h"

long double Power(long double x, unsigned int Power) {
	if (Power == 0) {
		return 1;
	}
	else {
		double result = 1;
		for (register unsigned int i = 0; i < Power; i++) {
			result *= x;
		}
		return result;
	}
}

long double Factorial(long double x) {
	for (register unsigned int i = x - 1; i > 1; i--) {
		x *= i;
	}
	return x;
}

long double Sinus(long double x, long double accuracy) {
	if (x < 0) {
		while (x < 0) {
			x += 2 * M_PI;
		}
	}
	else if (x > 2 * M_PI) {
		while (x > 2 * M_PI) {
			x -= 2 * M_PI;
		}
	}

	long double result = 0;
	int n = 1;
	while (fabs(sin(x) - result) > accuracy && n < 100) {
		result += Power(-1, n - 1) * Power(x, 2 * n - 1) / Factorial(2 * n - 1);
		n++;
	}
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/* std::cout << Power(5, 3) << endl;
	std::cout << Power(7, 3) << endl;

	std::cout << Factorial(3) << endl;
	std::cout << Factorial(100) << endl; */

	long double angle, accuracy;
	std::cout << "Enter your angle <rad> and accuracy: ";
	get_value(angle);
	get_value(accuracy);

	std::cout << "Result using our row: " << Sinus(angle, accuracy) << endl;
	std::cout << "Computer result: " << sin(angle) << endl;

	getch();

	return 0;
}
//---------------------------------------------------------------------------
