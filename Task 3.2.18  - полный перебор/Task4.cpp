#include <conio.h>
#include "get_value.h"

void output(int *Positions) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Positions[i] == j)
				cout << "F ";
			else
				cout << "- ";
		}
		cout << endl;
	}
	cout << endl;
	getch();
}

void TryToSet(int* Positions, int CurrentRow) {
	bool Free[8]; // array of free cells
	for (int i = 0; i < 8; i++)
		Free[i] = true;

	// finding free cells
	for (int i = 0; i < CurrentRow; i++) {
		// coordinates of figures
		int X = Positions[i];
		int Y = i;
		int distance = CurrentRow - Y;

		// checking deleted cells on the CurentRow
		int Pos[3];
		Pos[0] = X - distance;
		Pos[1] = X;
		Pos[2] = X + distance;

		// deleting cells
		for (int i = 0; i < 3; i++) {
			if (Pos[i] >= 0 && Pos[i] < 8) {
				Free[Pos[i]] = false;
			}
		}
	}

	// creating recursive algoritm
	for (int i = 0; i < 8; i++) {
		if (Free[i]) {
			Positions[CurrentRow] = i;
			if (CurrentRow == 7)
				output(Positions);
			else
				TryToSet(Positions, CurrentRow + 1);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int Positions[8];  // array of positions
	for (int i = 0; i < 8; i++) {
		Positions[i] = 0;
	}

	TryToSet(Positions, 0);

	getch();

	return 0;
}
//---------------------------------------------------------------------------
