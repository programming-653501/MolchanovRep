// prototype of the class defined in "RSA.cpp"
class RSA {
	private:
		__int32 p;
		__int32 q;
		__int32 PrivateKey;

		// private functions
		void GenerateKeys();
		__int32 BinaryPower(__int32 arg, __int32 power, __int32 mod);

	public:
		__int32 PublicKey;
		__int32 Key;

		// input/output
		void Display();
		void FromFile(const char* FileName);
		void ToFile(const char* FileName);

		// encryption/decryption
		__int32 EncryptChar(char arg);
		char DecryptChar(__int32 arg);

		// for random sequence
        __int32 Random();

        // constructors
		RSA();
		RSA(const char* FileName);
		RSA(__int32 FirstPrimeNumber, __int32 SecondPrimeNumber);
};


