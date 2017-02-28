//-------------------------------- Version 7 --------------------------------
// This is the library created by Strannik in BSUIR. It can be used by any
// person, who needs it, to create any projects he / she wants. This library
// can be used not to check the errors in the console input stream, it will
// check the errors and demand to repeat the input.
//---------------------------------------------------------------------------

#include <iostream>
#include <vcl.h>
#include <string>
#include <errno.h>

using namespace std;

template <class T>
void get_value(T &arg)
{
	cin >> arg; 
	while (cin.fail()) { 
		cout << "Input is incorrect. Try again." << endl; 
		cin.clear(); 
		cin.sync(); 
		cin >> arg; 
	}	
}

template <class T>
void get_value(T &arg, string message)
{	
	cout << message << endl; 
	cin >> arg; 
	while (cin.fail()) { 
		cout << "Input is incorrect. Try again." << endl; 
		cout << message << endl; 
		cin.clear(); 
		cin.sync(); 
		cin >> arg; 
	}	
}

template <class T>
void get_value(T &arg, string message, string error)
{	
	cout << message << endl; 
	cin >> arg; 
	while (cin.fail()) { 
		cout << error << endl; 
		cout << message << endl; 
		cin.clear(); 
		cin.sync(); 
		cin >> arg; 
	}	
}

//---------------------------------------------------------------------------