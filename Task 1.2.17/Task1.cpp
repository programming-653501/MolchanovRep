#include <conio.h>
#include "get_value.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int num1 = 0, num2 = 0, num3 = 0;
	for (register int mainNumber = 100; mainNumber < 1000; mainNumber++) {
		num1 = mainNumber / 100;
		num2 = (mainNumber / 10) % 10;
		num3 = mainNumber % 10;
		if (mainNumber == num1 * num1 * num1 + num2 * num2 * num2 + num3 * num3 * num3) {
			cout << mainNumber << endl;
		}
	}

	getch();
	return 0;
}
//---------------------------------------------------------------------------
