// prototype of the class defined in "Sequence.cpp"
class Sequence {
	private:
		__int64 Start[2];
		__int64 Current[2];
		__int64 Alpha;
		__int64 Beta;

	public:
		__int64 Next();
		void Write();
		void ToFile(const char* FileName);
		Sequence();
		Sequence(__int64 arg_a1, __int64 arg_a2, __int64 arg_Alpha, __int64 arg_Beta);
		Sequence(const char* FileName);
};
