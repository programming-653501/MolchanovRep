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

#include "Encryption_RSA_Advanced.h"
#include "RSA.h"
#include "Sequence.h"

//---------------------------------------------------------------------------

// the function of advanced RSA encryption using Key and Sequence
void RSA_Advanced_Encrypt(const char* InputFile, const char* OutputFile, const char* KeyFile, const char* SequenceFile) {
	// creating RSA structure
	RSA* Key = new RSA();

	// saving it to the file
	Key -> ToFile(KeyFile);

	// creating Sequence
	Sequence* Object = new Sequence();

	// saving it to the file
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

	// encrypting
	char CurrentSymbol = '\0';
	__int32 CurrentEncrypted = 0;
	__int64 i = 0, missing = Object -> Next();
	while (true) {
		// adding random number if necessary
		if (i == missing) {
			fprintf(FileEncrypted, "%d\n", Key -> Random());
			missing = Object -> Next();
		}
		else {
			CurrentSymbol = getc(FileToEncrypt);
			if (!feof(FileToEncrypt)) {
				CurrentEncrypted = Key -> EncryptChar(CurrentSymbol);
				fprintf(FileEncrypted,"%d\n", CurrentEncrypted);
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
void RSA_Advanced_Decrypt(const char* InputFile, const char* OutputFile, const char* KeyFile, const char* SequenceFile) {
    // creating RSA structure
	RSA* Key = new RSA(KeyFile);

	// creating Sequence
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

	// decryption
	__int32 CurrentNumber = 0;
	__int64 i = 0, missing = Object -> Next();
	char CurrentDecrypted = '\0';
	while (true) {
		if (i == missing) {
			fscanf(FileToDecrypt, "%d", &CurrentNumber);
			missing = Object -> Next();
		}
		else {
			fscanf(FileToDecrypt, "%d", &CurrentNumber);
			if (!feof(FileToDecrypt)) {
				CurrentDecrypted = Key -> DecryptChar(CurrentNumber);
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
