#include <conio.h>
#include <math.h>
#include "get_value.h"

struct Tree {
	Tree* BigChild;
	Tree* SmallChild;
	int value;

	bool Find(int arg) {
		if (arg == value)
			return true;
		else if (BigChild == NULL && arg > value || SmallChild == NULL && arg < value)
			return false;
		else
			return (arg > value ? BigChild -> Find(arg) : SmallChild -> Find(arg));
	}

	bool Add(int arg) {
		if (arg == value)
			return false;
		else if (arg > value) {
			if (BigChild == NULL) {
				BigChild = new Tree(arg);
				return true;
			}
			else {
				return BigChild -> Add(arg);
			}
		}
		else {
			if (SmallChild == NULL) {
				SmallChild = new Tree(arg);
				return true;
			}
			else {
				return SmallChild -> Add(arg);
			}
		}
	}

	Tree(int arg) {
		value = arg;
		BigChild = NULL;
		SmallChild = NULL;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Tree MyTree(1);

	FILE *fp;
	fp = fopen("text_to_process.txt", "r");
	if (fp == NULL) {
		cout << "Error. Unable to open file.";
		getch();
		return 0;
	}
	else {
		while (!feof(fp)) {
			int temp;
			fscanf(fp, "%d ", &temp);
			MyTree.Add(temp);
			cout << temp << " ";
		}
	}

	while (true) {
		int number;
		cout << "\nEnter the numbers you want to seek for: ";
		get_value(number);

		if (MyTree.Find(number))
			cout << number << " was found";
		else
			cout << number << " wasn't found";
	}

	cout << "Press any key . . . ";
	getch();
	return 0;
}
//---------------------------------------------------------------------------
