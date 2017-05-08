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

#include "Primes.h"

//---------------------------------------------------------------------------

bool IsPrime(__int32 Value) {
	if (Value % 2 == 0) {
		return false;
	}
	else {
		__int32 Max = (__int32) sqrt((double) Value);
		for (__int32 i = 3; i <= Max; i += 2)
			if (Value % i == 0)
				return false;
		return true;
	}
}

__int32 GeneratePrime(__int32 MaxValue) {
	if (MaxValue % 2 == 0)
		MaxValue--;

	for (__int32 i = MaxValue; i > 0; i -= 2) {
		if (IsPrime(i))
			return i;
	}

	return 0;
}

__int32 GCD(__int32 First, __int32 Second) {
	if (First % Second) {
		First %= Second;
		return GCD(Second, First);
	}
	else return std::min(First, Second);
}
