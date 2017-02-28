#include "get_value.h"
#include <conio.h>
#include <string.h>

unsigned long long Power10(unsigned int arg) {
	unsigned long long result = 1;
	for (register int i = 0; i < arg; i++) {
		result *= 10;
	}
	return result;
}

bool IsNumber(string arg) {
	for (register int i = arg.length() - 1; i >= 0; i--) {
		if (arg[i] < 48 || arg[i] > 57) {
			return false;
		}
	}
	return true;
}

unsigned long long Stol(string arg) {
	unsigned long long result = 0;
	if (!IsNumber(arg)) {
		std::cout << "Not a number or the number is below zero!\n";
		return 0;
	}
	else if (arg.length() > 20) {
		std::cout << "Overflow!\n";
		return 0;
	}
	else if (arg.length() == 20) {
		string string_limit = "18446744073709551615";
		for (register int i = arg.length() - 1; i >= 0; i--) {
			if (arg[i] > string_limit[i]) {
				std::cout << "Overflow!\n";
				return 0;
			}
			else if (arg[i] < string_limit[i])
				break;
			else
				continue;
		}
	}
	for (register int i = arg.length() - 1, power = 0; i >= 0; i--, power++) {
		result += (arg[i] - 48) * Power10(power);
		// std::cout << result << endl;
	}
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string string_number;
	get_value(string_number);
	while (string_number != "exit") {
		std::cout << Stol(string_number) << endl;
		std::cout << "Next value: ";
		get_value(string_number);
	}

	// getch();

	return 0;
}
//---------------------------------------------------------------------------
