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

#include "Sequence.h"

//---------------------------------------------------------------------------

#define ERROR 1000000000000000000

//---------------------------------------------------------------------------

// next number
__int64 Sequence::Next() {
	if (Current[0] > ERROR) {
		return 0;
	}
	else {
		__int64 Result = Alpha * Current[0] + Beta * Current[1];
		Current[0] = Current[1];
		Current[1] = Result;
		return Result;
	}
}

// output
void Sequence::Write() {
	std::cout << Start[0] << " " << Start[1] << " " << Alpha << " " << Beta << endl;
}

// saving the key to file
void Sequence::ToFile(const char* FileName) {
	FILE* FileWithKey = fopen(FileName, "wb");
	fprintf(FileWithKey, "%lld %lld %lld %lld", Start[0], Start[1], Alpha, Beta);
	fclose(FileWithKey);
}

// random generation
Sequence::Sequence() {
	randomize();
	Current[0] = Start[0] = random(3) + 1;
	Current[1] = Start[1] = random(3) + 1;
	Alpha = random(3) + 1;
	Beta = random(3) + 1;
}

// manual numbers
Sequence::Sequence(__int64 arg_a1, __int64 arg_a2, __int64 arg_Alpha, __int64 arg_Beta) {
	Current[0] = Start[0] = arg_a1;
	Current[1] = Start[1] = arg_a2;
	Alpha = arg_Alpha;
	Beta = arg_Beta;
}

// from file
Sequence::Sequence(const char* FileName) {
	FILE* FileWithKey = fopen(FileName, "rb");
	fscanf(FileWithKey, "%lld %lld %lld %lld", &Start[0], &Start[1], &Alpha, &Beta);
	Current[0] = Start[0];
	Current[1] = Start[1];
	fclose(FileWithKey);
}
