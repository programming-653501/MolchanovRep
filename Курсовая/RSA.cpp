//---------------------------------------------------------------------------

#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <dos.h>

//---------------------------------------------------------------------------

#include "RSA.h"
#include "Primes.h"

//---------------------------------------------------------------------------

#define HALF LONG_MAX / 4 + LONG_MAX / 8 + LONG_MAX / 16 + LONG_MAX / 32

// keys generation
void RSA::GenerateKeys() {
	__int32 Temp =  (p - 1) * (q - 1);

	std::cout << "Generating the first key . . .\n";
	__int32 Start = 1000 + random(1000);
	for (__int32 d = Start; ; d++) {
		if (GCD(Temp, d) == 1) {
			PrivateKey = d;
			break;
		}
	}

	std::cout << "Generating the second key . . .\n";
	for (__int32 e = 2; ; e++) {
		__int64 ED = e * PrivateKey;
		if ((ED % Temp) == 1) {
			PublicKey = e;
			break;
		}
	}

	std::cout << "Keys successfully generated;\n";
	Key = p * q;
}

// arg ^ power % mod
__int32 RSA::BinaryPower(__int32 arg, __int32 power, __int32 mod) {
	if (power == 0)
		return (1 % mod);
	if (power % 2 == 1) {
		__int64 temp = BinaryPower(arg, power - 1, mod) * (__int64) (arg % mod);
		return (__int32) (temp % mod);
	}
	else {
		__int64 temp = BinaryPower(arg, power / 2, mod);
		temp *= temp;
		return (__int32) (temp % mod);
	}
}

// output
void RSA::Display() {
	std::cout << "p: " << p << endl;
	std::cout << "q: " << q << endl;
	std::cout << "PrivateKey: " << PrivateKey << endl;
	std::cout << "Public Key: " << PublicKey << endl;
}

// getting from the file
void RSA::FromFile(const char* FileName) {
	FILE* InputFile = fopen(FileName, "rb");
	fread(this, sizeof(RSA), 1, InputFile);
	fclose(InputFile);
}

// saving to the file
void RSA::ToFile(const char* FileName) {
	FILE* OutputFile = fopen(FileName, "wb");
	fwrite(this, sizeof(RSA), 1, OutputFile);
	fclose(OutputFile);
}

// encryption
__int32 RSA::EncryptChar(char arg) {
	return BinaryPower(arg, PublicKey, Key);
}

// decryption
char RSA::DecryptChar(__int32 arg) {
	return (char) BinaryPower(arg, PrivateKey, Key);
}

// for random sequence
__int32 RSA::Random() {
    return random(p * q);
}

// constructor - standard
RSA::RSA() {
	__int32 Max = (__int32) sqrt(sqrt((double) LONG_MAX));
	p = GeneratePrime(Max / 2 + random(Max / 2));
	q = GeneratePrime(Max / 2 + random(Max / 2));

	GenerateKeys();
}

// constructor - from file
RSA::RSA(const char* FileName) {
	FromFile(FileName);
}

// constructor - user values
RSA::RSA(__int32 FirstPrimeNumber, __int32 SecondPrimeNumber) {
	if (IsPrime(FirstPrimeNumber) && IsPrime(SecondPrimeNumber)) {
		__int64 N = FirstPrimeNumber * SecondPrimeNumber;
		if (N < LONG_MAX) {
			p = FirstPrimeNumber;
			q = SecondPrimeNumber;
		}
		else {
			RSA();
        }
	}
	else {
		RSA();
	}

	GenerateKeys();
}
