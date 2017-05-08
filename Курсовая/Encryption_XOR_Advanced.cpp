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

#include "Encryption_XOR_Advanced.h"
#include "Keys.h"
#include "Sequence.h"

//---------------------------------------------------------------------------

// the function of advanced XOR encryption using Key and Sequence
void XOR_Advanced_Encrypt(const char* InputFile, const char* OutputFile, const char* KeyFile, const char* SequenceFile) {
	// generating Key
	string Key = GenerateKey(CountSymbols(InputFile));
	KeyToFile(Key, KeyFile);

	// generating Sequence
	Sequence* Object = new Sequence();
	Object -> ToFile(SequenceFile);

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

	// initializing additional variables
	char CurrentSymbol = '\0';            // Current symbol before XOR
	char CurrentEncrypted = '\0';         // Current symbol after XOR
	__int64 i = 0;                        // Number of key symbol under XOR
	__int64 missing = Object -> Next();   // Number of next symbol to be missed
	__int64 end = Key.length() - 1;       // Number of last Key symbol

	// encrypting using our Key and Sequence
	while (true) {
		// if next symbol is to be missed
		if (i == missing) {
			putc(random(256), FileEncrypted);
			missing = Object -> Next();
		}
		else {
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
	}

	// awaiting
	Sleep(200);

	// closing the files
	fclose(FileToEncrypt);
	fclose(FileEncrypted);
}

// the decrypting function
void XOR_Advanced_Decrypt(const char* InputFile, const char* OutputFile, const char* KeyFile, const char* SequenceFile) {
	// getting Key and Sequence from the files
	string Key = KeyFromFile(KeyFile);
	Sequence* Object = new Sequence(SequenceFile);

	// console comments
	std::cout << "The decryption process started;\n";

	// opening files
	FILE* FileToDecrypt = fopen(InputFile, "rb");
	FILE* FileDecrypted = fopen(OutputFile, "wb");

	// catching NULL
	if (FileToDecrypt == NULL) {
		std::cout << "NULL reference. The process terminated incorrectly;\n";
		return;
	}

	// initializing additional variables
	char CurrentSymbol = '\0';            // Current symbol before XOR
	char CurrentDecrypted = '\0';         // Current symbol after XOR
	__int64 i = 0;                        // Number of key symbol under XOR
	__int64 missing = Object -> Next();   // Number of next symbol to be missed
	__int64 end = Key.length() - 1;       // Number of last Key symbol

	// encrypting using our Key and Sequence
	while (true) {
		// if next symbol is to be missed
		if (i == missing) {
			getc(FileToDecrypt);
			missing = Object -> Next();
		}
		else {
			CurrentSymbol = getc(FileToDecrypt);
			if (!feof(FileToDecrypt)) {
				CurrentDecrypted = CurrentSymbol ^ Key[i % end];
				putc(CurrentDecrypted, FileDecrypted);
				i++;
			}
			else {
				// success report
				std::cout << "The decryption process succeeded;\n";
				break;
			}
		}
	}

	// awaiting
	Sleep(200);

	// closing the files
	fclose(FileToDecrypt);
	fclose(FileDecrypted);
}
