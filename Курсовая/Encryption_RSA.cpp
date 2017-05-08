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

#include "Encryption_RSA.h"
#include "RSA.h"

//---------------------------------------------------------------------------

// standard RSA encryption
void RSA_Encrypt(const char* InputFile, const char* OutputFile, const char* KeyFile) {
	// creating RSA structure
	RSA* Key = new RSA();

	// saving it to the file
	Key -> ToFile(KeyFile);

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

	// encrypting
	char CurrentSymbol = '\0';
	__int32 CurrentEncrypted = 0;
	while (true) {
		CurrentSymbol = getc(FileToEncrypt);
		if (!feof(FileToEncrypt)) {
			CurrentEncrypted = Key -> EncryptChar(CurrentSymbol);
			fprintf(FileEncrypted,"%d\n", CurrentEncrypted);
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

// standard RSA decryption
void RSA_Decrypt(const char* InputFile, const char* OutputFile, const char* KeyFile) {
    // creating RSA structure
	RSA* Key = new RSA(KeyFile);

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

	// decryption
	__int32 CurrentNumber = 0;
	char CurrentDecrypted = '\0';
	while (true) {
		fscanf(FileToDecrypt, "%d", &CurrentNumber);
		if (!feof(FileToDecrypt)) {
			CurrentDecrypted = Key -> DecryptChar(CurrentNumber);
			putc(CurrentDecrypted, FileDecrypted);
		}
		else {
			// success report
			std::cout << "The decryption process succeeded;\n";
			break;
		}
	}

	// awaiting
	Sleep(200);

	// closing the files
	fclose(FileToDecrypt);
	fclose(FileDecrypted);
}
