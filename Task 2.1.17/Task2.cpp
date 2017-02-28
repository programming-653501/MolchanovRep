#include "get_value.h"
#include <math.h>
#include <conio.h>
#include <string.h>

class Planet {
	public:
		long double M; // metres
		long double R; // metres
		long double V; // metres/seconds
		long double alpha; // radians
		Planet() {
			M = 0;
			R = 0;
			V = 0;
		}
};

string toupper(string value) {
	for (register int i = 0; i < value.length(); i++) {
		if (value[i] >= 97 && value[i] <= 122) {
			value[i] -= 32;
		}
	}
	return value;
}

void EnterPlanet(Planet &arg) {
	static int number = 1;
	cout << "E2G_" << number << ":\n";
	cout << "Mass <t>: ";
	get_value(arg.M); // input in tons
	arg.M *= 1000;
	cout << "Radius <km>: ";
	get_value(arg.R); // input in kilometres
	arg.R *= 1000;
	cout << "Speed <km/s>: ";
	get_value(arg.V); // input in kilometres/seconds
	arg.V *= 1000;
	cout << "\n";
	number++;
}

long double FindDistance(Planet &arg1, Planet &arg2, long double time /* seconds */) {
	long double alpha1 = arg1.V * time / arg1.R;
	long double alpha2 = arg2.V * time / arg2.R;
	long double angle = fabs(alpha1 - alpha2);
	long double distance = sqrt(arg1.R * arg1.R + arg2.R * arg2.R - 2 * arg1.R * arg2.R * cos(angle)); // using the cosine theorem
	return (distance / 1000); // counting in metres, return in kilometres
}

long double CountYear(Planet &arg) {
	return (2 * M_PI * arg.R / arg.V / 60 / 60 / 24); // return in days
}

long double FindGravitation(Planet &arg1, Planet &arg2, long double time /* seconds */) {
	long double alpha1 = arg1.V * time / arg1.R;
	long double alpha2 = arg2.V * time / arg2.R;
	long double angle = fabs(alpha1 - alpha2);
	const long double G = 0.00000000006674286767676767;
	long double distance = FindDistance(arg1, arg2, 0);
	return (G * arg1.M * arg2.M / distance / distance);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Planet E2G_1, E2G_2, E2G_3;
	EnterPlanet(E2G_1);
	EnterPlanet(E2G_2);
	EnterPlanet(E2G_3);

	string command = "";
	while (1) {
		cout << "Your command: ";
		get_value(command);
		if (toupper(command) == "FIND_DISTANCE") {
			long double Time = 0.001;
			cout << "Enter the time <sec>:";
			get_value(Time);
			cout << "p(E2G_1, E2G_2) <km>:" << FindDistance(E2G_1, E2G_2, Time) << ";\n";
			cout << "p(E2G_1, E2G_3) <km>:" << FindDistance(E2G_1, E2G_3, Time) << ";\n";
			cout << "p(E2G_2, E2G_3) <km>:" << FindDistance(E2G_2, E2G_3, Time) << ";\n";
		}
		else if (toupper(command) == "COUNT_GRAVITATION") {
			long double Time = 0.001;
			cout << "Enter the time <sec>:";
			get_value(Time);
			cout << "F(E2G_1, E2G_2) <H>:" << FindGravitation(E2G_1, E2G_2, Time) << ";\n";
			cout << "F(E2G_1, E2G_3) <H>:" << FindGravitation(E2G_1, E2G_3, Time) << ";\n";
			cout << "F(E2G_2, E2G_3) <H>:" << FindGravitation(E2G_2, E2G_3, Time) << ";\n";
		}
		else if (toupper(command) == "COUNT_YEAR") {
			cout << "The year on E2G_1 is " << CountYear(E2G_1) << " Earth days;\n";
			cout << "The year on E2G_2 is " << CountYear(E2G_2) << " Earth days;\n";
			cout << "The year on E2G_3 is " << CountYear(E2G_3) << " Earth days;\n";
		}
		else if (toupper(command) == "EXIT") {
			cout << "Press any key . . .";
			getch();
			return 0;
		}
		else continue;
	}

	getch();
	return 0;
}
//---------------------------------------------------------------------------
