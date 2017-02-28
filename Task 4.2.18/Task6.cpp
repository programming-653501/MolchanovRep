#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "get_value.h"

void funct(char *name, int day, int month, int year, int number, int price) {
	std::cout << name << " ";
	if (day < 10)
		std::cout << "0" << day << ".";
	else
		std::cout << day << ".";
	if (month < 10)
		std::cout << "0" << month << ".";
	else
		std::cout << month << ".";
	std::cout << year << " " << number << " " << price << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *base;
	base = fopen("Base.txt", "r");

	char name[100];
	int day, month, year, number, price, sum = 0;
	int current_day = 28, current_month = 02, current_year = 2017;

	if (base == NULL) {
		std::cout << "NULL!";
		getch();
		return 0;
	}
	else {
		while (!feof(base)) {
			fscanf(base, "%s %d.%d.%d %d %d", &name, &day, &month, &year, &number, &price);
			if (year > 2017 || (year == current_year && month > current_month))
				continue;
			else {
				funct(name, day, month, year, number, price);
				//std::cout << name << " " << day << "." << month << "." << year << " " << number << " " << price << endl;
				sum += number * price;
			}
		}
	}

	fclose(base);
	std::cout << "Money to write off: " << sum;

	getch();
	return 0;
}
//---------------------------------------------------------------------------
