//---------------------------------------------------------------------------

#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <limits.h>
#include <time.h>
#include <dos.h>

//---------------------------------------------------------------------------

#include "Keys.h"

//---------------------------------------------------------------------------

// the function must simply return number of symbols in our file
long long CountSymbols(const char* FileName) {
	// console comments
	std::cout << "Counting the symbols . . .\n";

	// opening the file
	FILE *FileToAnalyze = fopen(FileName, "rb");
	long long Count = 0;

	// catching NULL
	if (FileToAnalyze == NULL) {
		std::cout << "NULL reference. The process terminated incorrectly;\n";
		return 0;
	}

	// getting number of sybmols
	while (true) {
		getc(FileToAnalyze);
		if (!feof(FileToAnalyze)) {
			Count++;
		}
		else {
			break;
		}
	}

	// awaiting
	Sleep(200);

	// closing the file
	fclose(FileToAnalyze);
	return Count;
}

// the function that generates the key and saves it
string GenerateKey(long long NumberOfSymbols) {
	// console comments
	std::cout << "Generating the key . . .\n";

	// counting the length
	unsigned long long Length = 0;
	if (NumberOfSymbols < 2048) {
		Length = 1024;
	}
	else {
		Length = 256 * (long long) log((double) NumberOfSymbols);
	}

	// random generation
	randomize();
	char* Key = new char[Length + 1];
	for (int i = 0; i < Length; i++) {
		Key[i] = (char) (random(255) + 1); // not to generate '\0'
	}

	// converting to string
	string Result = Key;

	// returning the result
	return Result;
}

// the function that saves our key
void KeyToFile(string Key, const char* KeyFile) {
	// console comments
	std::cout << "Saving the key to the file . . .\n";

	// opening the file
	FILE* FileWithKey = fopen(KeyFile, "wb");
	int Length = Key.length();

	// saving our Key
	for (int i = 0; i < Length; i++) {
		putc(Key[i], FileWithKey);
	}

	// awaiting
	Sleep(200);

	// closing the file
	fclose(FileWithKey);
}

// the function that gets our key from the file
string KeyFromFile(const char* KeyFile) {
	// console comments
	std::cout << "Getting the key from the file . . .\n";

	// opening the file
	FILE* FileWithKey = fopen(KeyFile, "rb");

	// catching NULL
	if (FileWithKey == NULL) {
		std::cout << "NULL reference. The process terminated incorrectly;\n";
		return 0;
	}

	// creating string Key
	string Key = "";
	char Current = '\0';

	while (true) {
		Current = getc(FileWithKey);
		if (!feof(FileWithKey)) {
			Key += Current;
		}
		else {
			break;
		}
	}

	return Key;
}
