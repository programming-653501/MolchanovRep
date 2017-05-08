#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

//---------------------------------------------------------------------------

#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <conio.h>
#include <limits.h>
#include <time.h>
#include <dos.h>
#include <vcl.h>

//---------------------------------------------------------------------------

#include "Encryption_XOR.h"
#include "Encryption_XOR_Advanced.h"

#include "Encryption_RSA.h"
#include "Encryption_RSA_Advanced.h"

//---------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	system("color 0a");
	system("title Crypto");
	randomize();

	// the address of the .exe file
	std::cout << "Executing: " << argv[0] << endl;

	// creating the path to the key files
	std::string ProgramPath(argv[0]);
	ProgramPath.erase(ProgramPath.length() - 10, 10);

	// input data
	std::string Mode;
	std::string Encryption;
	std::string Input;
	std::string Output;

	// getting arguments
	if (argc >= 2) {
		Mode = argv[1];
		if (argc >= 3) {
			Encryption = argv[2];
			if (argc >= 4) {
				Input = argv[3];
				if (argc >= 5) {
					Output = argv[4];
				}
			}
		}
	}

	// If not enough data found
	if (argc < 5) {
		std::cout << "Not enough data. Choosing manually . . .\n";
	}

	if (argc < 2) {
		std::cout << "Choose mode: encrypt/decrypt: ";
		std::getline(std::cin, Mode);
	}

	if (argc < 3) {
        std::cout << "Choose encryption: rsa/xor: ";
		std::getline(std::cin, Encryption);
	}

	if (argc < 4) {
		std::cout << "Enter the input file path: ";
		std::cout << ProgramPath;
		std::getline(std::cin, Input);
	}

	if (argc < 5) {
		std::cout << "Enter the output file name: ";
		std::cout << ProgramPath;
		std::getline(std::cin, Output);
	}

	// generating file paths
	std::cout << "Generating file directories . . .\n";

	std::string InputPath = ProgramPath;
	std::string OutputPath = ProgramPath;
	std::string KeyPath = ProgramPath;
	std::string SequencePath = ProgramPath;

	InputPath.append(Input);
	OutputPath.append(Output);
	KeyPath.append("Key.txt");
	SequencePath.append("Sequence.txt");
	std::cout << "Generated Directories:\n" << InputPath << endl << OutputPath << endl << KeyPath << endl << SequencePath << endl;

	// choosing the mode and starting the process
	if (Mode == "decrypt") {
		if (Encryption == "rsa") {
			RSA_Advanced_Decrypt(InputPath.c_str(), OutputPath.c_str(), KeyPath.c_str(), SequencePath.c_str());
		}
		else {
			// standard encryption - xor
			XOR_Advanced_Decrypt(InputPath.c_str(), OutputPath.c_str(), KeyPath.c_str(), SequencePath.c_str());
		}
	}
	else {
		// standard mode - encrypt
		if (Encryption == "rsa") {
			RSA_Advanced_Encrypt(InputPath.c_str(), OutputPath.c_str(), KeyPath.c_str(), SequencePath.c_str());
		}
		else {
			// standard encryption - xor
			XOR_Advanced_Encrypt(InputPath.c_str(), OutputPath.c_str(), KeyPath.c_str(), SequencePath.c_str());
		}
	}

	std::cout << "Press any key . . . ";
	getch();
	return 0;
}
//---------------------------------------------------------------------------
