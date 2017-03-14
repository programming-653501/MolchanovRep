#include <conio.h>
#include <queue.h>
#include <string.h>
#include "get_value.h"

struct ListMember {
	ListMember* Previous;
	int Value;
	ListMember* Next;
};

struct List {
	ListMember* First;
	ListMember* Last;

	void Add(int arg) {
		ListMember* NewMember = new ListMember;
		Last -> Next = NewMember;
		NewMember -> Previous = Last;
		NewMember -> Value = arg;
		NewMember -> Next = NULL;
		Last = NewMember;
	}

	void Display() {
		ListMember* I = First;
		while (I != NULL) {
			cout << I -> Value;
			I = I -> Next;
		}
		cout << endl;
	}

	List(int arg) {
		ListMember* NewMember = new ListMember;
		NewMember -> Previous = NULL;
		NewMember -> Value = arg;
		NewMember -> Next = NULL;
		First = Last = NewMember;
    }
};

struct LongNumber {
	List* Number;

	string ToBinary() {
		// creating a copy
		List* Copy = new List(Number -> First -> Value);
		ListMember* I = Number -> First;
		while (I != Number -> Last) {
			Copy -> Add(I -> Next -> Value);
			I = I -> Next;
		}

		// working with a copy
		string result = "";

		bool IsZero = false;
		while (!IsZero) {
			// checking zero
			IsZero = true;
			I = Copy -> First;
			while (I != NULL) {
				if (I -> Value) {
					IsZero = false;
				}
				I = I -> Next;
			}

			// adding values
			if (IsZero)
				break;
			else if (Copy -> Last -> Value % 2)
				result += "1";
			else
				result += "0";

			// dividing by 2
			I = Copy -> First;
			while (I != NULL) {
				if (I -> Value % 2) {
					I -> Value /= 2;
					if (I -> Next != NULL) {
						I -> Next -> Value += 10;
					}
				}
				else {
					I -> Value /= 2;
				}
				I = I -> Next;
			}
		}

		string reversed = "";
		for (int i = result.length() - 1; i >= 0; i--) {
			reversed += result[i];
		}

		return reversed;
	}

	LongNumber(int arg) {
		Number = new List(arg);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	LongNumber MyNumber(cin.get() - 48);
	if (MyNumber.Number -> First -> Value < 0 || MyNumber.Number -> First -> Value > 9) {
		cout << "Not a number! Press any key . . . ";
		getch();
		return 0;
	}

	int temp;
	do {
		temp = cin.get();
		if (temp >= 48 && temp <= 57) {
			MyNumber.Number -> Add(temp - 48);
		}
	}
	while ((char)temp != '\n');

	cout << endl;
	cout << "The result is: " << MyNumber.ToBinary();

	getch();
	return 0;
}
//---------------------------------------------------------------------------
