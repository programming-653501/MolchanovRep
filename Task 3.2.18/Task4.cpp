#include <conio.h>
#include "get_value.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool Matrix[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Matrix[i][j] = false;
		}
	}

	int MyArray[8][2];
	MyArray[0][0] = 0;
	MyArray[0][1] = 1;
	for (int i = 1; i < 4; i++) {
		MyArray[i][0] = MyArray[i - 1][0] + 1;
		MyArray[i][1] = MyArray[i - 1][1] + 2;
	}

	MyArray[4][0] = 4;
	MyArray[4][1] = 2;
	for (int i = 5; i < 8; i++) {
		MyArray[i][0] = MyArray[i - 1][0] + 1;
		MyArray[i][1] = MyArray[i - 1][1] - 2;
		if (MyArray[i][1] < 0) {
			MyArray[i][1] = MyArray[i][1] + 8;
		}
	}

	/* for (int i = 0; i < 8; i++) {
		std::cout << MyArray[i][0] << " " << MyArray[i][1] << endl;
	} */

	int x, y;
	for (int i = 0; i < 8; i++) {
		y = MyArray[i][0];
		x = MyArray[i][1];
		Matrix[x][y] = true;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (!Matrix[i][j])
				std::cout << "0";
			else
				std::cout << "F";
			std::cout << " ";
		}
		std::cout << "\n";
	}

	getch();

	return 0;
}
//---------------------------------------------------------------------------