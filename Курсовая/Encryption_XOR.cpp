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

#include "Encryption_XOR.h"
#include "Keys.h"
#include "Sequence.h"

//---------------------------------------------------------------------------

// standard XOR
void XOR_Perform(const char* InputFile, const char* OutputFile, string Key) {
	// console comments
	std::cout << "The encryption process started;\n";

	// opening files
	FILE* FileToEncrypt = fopen(InputFile, "rb");
	FILE* FileEncrypted = fopen(OutputFile, "wb");

	// catching NULL
	if (FileToEncrypt == NULL) {
		std::cout << "NULL reference. The process terminated incorrectly;\n";
		return;
	}

	// encripting
	char CurrentSymbol = '\0', CurrentEncrypted = '\0';
	long long i = 0, end = Key.length() - 1;
	while (true) {
		CurrentSymbol = getc(FileToEncrypt);
		if (!feof(FileToEncrypt)) {
			CurrentEncrypted = CurrentSymbol ^ Key[i % end];
			putc(CurrentEncrypted, FileEncrypted);
			i++;
		}
		else {
			// success report
			std::cout << "The encryption process succeeded;\n";
			break;
		}
	}

	// awaiting
	Sleep(200);

	// closing the files
	fclose(FileToEncrypt);
	fclose(FileEncrypted);
}

// the encryption function generating the key file
void XOR_Encrypt(const char* InputFile, const char* OutputFile, const char* KeyFile) {
	// counting symbols
	long long Number = CountSymbols(InputFile);

	// generating the key and the key file
	string Key = GenerateKey(Number);
	KeyToFile(Key, KeyFile);

	// encrypring our file
	XOR_Perform(InputFile, OutputFile, Key);
}

// the standard decrypting function
void XOR_Decrypt(const char* InputFile, const char* OutputFile, const char* KeyFile) {
	// getting the Key
	string Key = KeyFromFile(KeyFile);

	// decrypting
	XOR_Perform(InputFile, OutputFile, Key);
}
