#include "get_value.h"
#include <conio.h>

using namespace std;

struct Book;

struct Reader {
	// pointers
	Reader* Next;
	Reader* Previous;

	// properties
	string Surname;
	string Name;
	string Group;
	string Phone;
	string Mail;
	Book* Books[5];

	// output
	void Display() {
		cout << "\n" << Surname << "\n" << Name << "\n" << Group << "\n" << Phone << "\n" << Mail << "\n\n";
	}

	// constructor
	Reader(string arg_Surname, string arg_Name, string arg_Group,
							   string arg_Phone, string arg_Mail) {
		Surname = arg_Surname;
		Name = arg_Name;
		Group = arg_Group;
		Phone = arg_Phone;
		Mail = arg_Mail;

		for (int i = 0; i < 5; i++) {
			Books[i] = NULL;
		}
	}

	// copying constructor
	Reader(const Reader* arg) {
		Surname = arg -> Surname;
		Name = arg -> Name;
		Group = arg -> Group;
		Phone = arg -> Phone;
		Mail = arg -> Mail;
		for (int i = 0; i < 5; i++) {
			Books[i] = arg -> Books[i];
		}
	}
};

struct Book {
	// pointers
	Book* Next;
	Book* Previous;

	// properties
	string Author;
	string Name;
	int Cost;
	int Number;
	Reader** Readers;

	// output
	void Display() {
		cout << "\n" << Author << "\n" << Name << "\n" << Cost << "\n" << Number << "\n\n";
	}

	// constructor
	Book(string arg_Author, string arg_Name, int arg_Cost, int arg_Number) {
		Author = arg_Author;
		Name = arg_Name;

		if (arg_Cost > 0)
			Cost = arg_Cost;
		else
			Cost = 0;

		if (arg_Number > 0)
			Number = arg_Number;
		else
			Number = 1;

		Readers = new Reader*[Number];
		for (int i = 0; i < Number; i++) {
			Readers[i] = NULL;
		}
	}

	// copying constructor
	Book(const Book* arg) {
		Author = arg -> Author;
		Name = arg -> Name;
		Cost = arg -> Cost;
		Number = arg -> Number;
		Readers = new Reader*[Number];
		for (int i = 0; i < Number; i++) {
			Readers[i] = arg -> Readers[i];
		}
	}
};

struct Library {
	// list of readers
	Reader* FirstReader;
	Reader* LastReader;

	// list of books
	Book* FirstBook;
	Book* LastBook;

	// operations with readers
	void AddReader(const Reader* arg) {
		LastReader -> Next = new Reader(arg);
		LastReader -> Next -> Previous = LastReader;
		LastReader = LastReader -> Next;
	}

	Reader* FindReader(string arg_Surname, string arg_Name) {
		Reader* Temp = FirstReader;
		while (Temp != NULL) {
			if (Temp -> Surname == arg_Surname && Temp -> Name == arg_Name)
				return Temp;
			else
				Temp = Temp -> Next;
		}
		return NULL;
	}

	bool RemoveReader(Reader* arg) {
		// checking NULL
		if (arg == NULL || FindReader(arg -> Surname, arg -> Name) == NULL) {
			cout << "Unable to find the reader to delete it;\n";
			return false;
		}

		// checking books
		for (int i = 0; i < 5; i++) {
			if (arg ->Books[i] != NULL) {
				cout << "Unable to delete the reader. There are unreturned books.\n";
				return false;
			}
		}

		// deleting the reader
		if (arg == LastReader) {
			LastReader = LastReader -> Previous;
			arg -> Previous -> Next = NULL;
		}
		else if (arg == FirstReader) {
			FirstReader = FirstReader -> Next;
			arg -> Next -> Previous = NULL;
		}
		else {
			arg -> Previous -> Next = arg -> Next;
			arg -> Next -> Previous = arg -> Previous;
		}

		delete arg;
		return true;
	}

	void DisplayReaders() {
		Reader* Temp = FirstReader;
		Temp -> Display();

		while (Temp -> Next != NULL) {
			Temp -> Next -> Display();
			Temp = Temp -> Next;
		}
	}

	void SaveReaders() {
		FILE *p = fopen("_out_Readers.txt", "w");
		Reader* Temp = FirstReader;

		while (Temp != NULL) {
			fprintf(p, "%s %s %s %s %s\n", Temp -> Surname.c_str(), Temp -> Name.c_str(), Temp -> Group.c_str(), Temp -> Phone.c_str(), Temp -> Mail.c_str());
			Temp = Temp -> Next;
		}

		fclose(p);
	}

	// operations with books
	void AddBook(const Book* arg) {
		Book* Existing = FindBook(arg -> Name);
		if (Existing == NULL) {
			// if book doesn't exist, just create new
			LastBook -> Next = new Book(arg);
			LastBook -> Next -> Previous = LastBook;
			LastBook = LastBook -> Next;
		}
		else {
			// changing number if the book already exists
			int NewNumber = Existing -> Number + arg -> Number;

			// widening the array of readers
			Reader** NewArrayOfReaders = new Reader*[NewNumber];
			for (int i = 0; i < Existing -> Number; i++)
				NewArrayOfReaders[i] = Existing -> Readers[i];
			for (int i = Existing -> Number; i < NewNumber; i++)
				NewArrayOfReaders[i] = NULL;

			// changing the array pointer
			Existing -> Readers = NewArrayOfReaders;

			// changing the number itself
			Existing -> Number = NewNumber;
		}
	}

	Book* FindBook(string arg) {
		Book* Temp = FirstBook;
		while (Temp != NULL) {
			if (Temp -> Name == arg)
				return Temp;
			else
				Temp = Temp -> Next;
		}
		return NULL;
	}

	bool RemoveBook(Book* arg) {
		// checking NULL
		if (arg == NULL || FindBook(arg -> Name) == NULL) {
			cout << "Unable to find the book to delete it;\n";
			return false;
		}

        // checking readers
		for (int i = 0; i < arg ->Number; i++) {
			cout << "Unable to delete the book. It has some readers;\n";
			if (arg ->Readers[i] != NULL) {
				return false;
			}
		}

		// deleting the book
		if (arg == LastBook) {
			LastBook = LastBook -> Previous;
			arg -> Previous -> Next = NULL;
		}
		else if (arg == FirstBook) {
			FirstBook = FirstBook -> Next;
			arg -> Next -> Previous = NULL;
		}
		else {
			arg -> Previous -> Next = arg -> Next;
			arg -> Next -> Previous = arg -> Previous;
		}

		delete arg;
		return true;
	}

	void DisplayBooks() {
		Book* Temp = FirstBook;
		Temp -> Display();

		while (Temp -> Next != NULL) {
			Temp -> Next -> Display();
			Temp = Temp -> Next;
		}
	}

	void SaveBooks() {
		FILE *p = fopen("_out_Books.txt", "w");
		Book* Temp = FirstBook;

		while (Temp != NULL) {
			fprintf(p, "%s %s %d %d\n", Temp -> Author.c_str(), Temp -> Name.c_str(), Temp -> Cost, Temp -> Number);
			Temp = Temp -> Next;
		}

		fclose(p);
	}

	// operation with both readers and books
	bool Borrow(Reader* arg_Reader, Book* arg_Book) {
		for (int i = 0; i < 5; i++) {
			if (arg_Reader -> Books[i] == NULL) {
				for (int j = 0; j < arg_Book -> Number; j++) {
					if (arg_Book -> Readers[j] == NULL) {
						arg_Reader -> Books[i] = arg_Book;
						arg_Book -> Readers[j] = arg_Reader;
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Return(Reader* arg_Reader, Book* arg_Book) {
		for (int i = 0; i < 5; i++) {
			if (arg_Reader -> Books[i] == arg_Book) {
				for (int j = 0; j < arg_Book -> Number; j++) {
					if (arg_Book -> Readers[j] == arg_Reader) {
						arg_Reader -> Books[i] = NULL;
						arg_Book -> Readers[j] = NULL;
						return true;
					}
				}
			}
		}
		return false;
	}

	void DisplayBorrowings() {
		Reader* Temp = FirstReader;
		while (Temp != NULL) {
			for (int i = 0; i < 5; i++) {
				if (Temp -> Books[i] != NULL) {
					cout << Temp -> Surname << " " << Temp -> Name << " => " << Temp -> Books[i] -> Name << endl;
				}
			}
			Temp = Temp -> Next;
		}
	}

	void SaveBorrowings() {
		FILE *p = fopen("_out_Borrowings.txt", "w");
		Reader* Temp = FirstReader;

		while (Temp != NULL) {
			for (int i = 0; i < 5; i++) {
				if (Temp -> Books[i] != NULL) {
					fprintf(p, "%s %s => %s\n", Temp -> Surname.c_str(), Temp -> Name.c_str(), Temp -> Books[i] -> Name.c_str());
				}
			}
			Temp = Temp -> Next;
		}

		fclose(p);
	}

	// first part of the constructor
	void InitializeReaders(const char* FileReaders) {
		// initializing readers
		FILE *p = fopen(FileReaders, "r");
		char Surname[100], Name[100], Group[100], Phone[100], Mail[100];
		Reader* Temprorary = NULL;

		// first reader
		if (!feof(p)) {
			if (fscanf(p, "%s %s %s %s %s", &Surname, &Name, &Group, &Phone, &Mail) != EOF) {
				FirstReader = new Reader(Surname, Name, Group, Phone, Mail);
				LastReader = FirstReader;
			}
		}

		// other readers
		while (!feof(p)) {
			if (fscanf(p, "%s %s %s %s %s", &Surname, &Name, &Group, &Phone, &Mail) != EOF) {
				LastReader -> Next = new Reader(Surname, Name, Group, Phone, Mail);
				LastReader -> Next -> Previous = LastReader;
				LastReader = LastReader -> Next;
			}
		}

		// closing our file
		fclose(p);
	}

	// second part
	void InitializeBooks(const char* FileBooks) {
		// initializing readers
		FILE *p = fopen(FileBooks, "r");
		char Author[100], Name[100];
		int Cost, Number;
		Book* Temprorary = NULL;

		// first book
		if (!feof(p)) {
			if (fscanf(p, "%s %s %d %d", &Author, &Name, &Cost, &Number) != EOF) {
				FirstBook = new Book(Author, Name, Cost, Number);
				LastBook = FirstBook;
			}
		}

		// other books
		while (!feof(p)) {
			if (fscanf(p, "%s %s %d %d", &Author, &Name, &Cost, &Number) != EOF) {
				LastBook -> Next = new Book(Author, Name, Cost, Number);
				LastBook -> Next -> Previous = LastBook;
				LastBook = LastBook -> Next;
			}
		}

		fclose(p);
	}

	// third part
	void InitializeBorrowings(const char* FileBorrowings) {
		FILE *p = fopen(FileBorrowings, "r");
		char arg_Surname[100], arg_Name[100], arg_Book[100];
		Reader* ReaderToBorrow;
		Book* BookToBorrow;

		while (!feof(p)) {
			if (fscanf(p, "%s %s => %s", &arg_Surname, &arg_Name, &arg_Book)!= EOF) {
				ReaderToBorrow = FindReader(arg_Surname, arg_Name);
				BookToBorrow = FindBook(arg_Book);
				if (ReaderToBorrow != NULL && BookToBorrow != NULL) {
					Borrow(ReaderToBorrow, BookToBorrow);
				}
			}
		}

		fclose(p);
	}


	// constructor
	Library(const char* FileReaders, const char* FileBooks, const char* FileBorrowings) {
		InitializeReaders(FileReaders);
		InitializeBooks(FileBooks);
		InitializeBorrowings(FileBorrowings);
	}
};

struct Interface {
	// working with commands
	static void ToUpper(string &arg) {
		for (int i = 0; i < arg.length(); i++) {
			if (arg[i] >= 97 && arg[i] <= 122) {
				arg[i] = arg[i] - 32;
			}
		}
	}

	// choosing the command
	static int ChooseCommand(Library* arg) {
		cout << "\nEnter any command of the following: \n<DISPLAY, ADD, FIND, DELETE, BORROW, RETURN, SAVE, EXIT>: \n";
		string command;
		cin >> command;
		ToUpper(command);
		if (command == "DISPLAY") {
			Display(arg);
			return 0;
		}
		else if (command == "ADD") {
			Add(arg);
			return 0;
		}
		else if (command == "FIND") {
			Find(arg);
			return 0;
		}
		else if (command == "DELETE") {
			Delete(arg);
			return 0;
		}
		else if (command == "BORROW") {
			Borrow(arg);
			return 0;
		}
		else if (command == "RETURN") {
			Return(arg);
			return 0;
		}
		else if (command == "SAVE") {
			Save(arg);
			return 0;
		}
		else if (command == "EXIT") {
			cout << "Press any key . . . ";
			getch();
			return 1;
		}
		else {
			cout << "Unknown command. Try again.\n";
			return 0;
        }
	}

	// display function
	static void Display(Library* arg) {
		string object;
		cin >> object;
		ToUpper(object);

		if (object == "BOOKS")
			arg -> DisplayBooks();
		else if (object == "READERS")
			arg -> DisplayReaders();
		else if (object == "BORROWINGS")
			arg -> DisplayBorrowings();
		else
			cout << "Unknown object. Try again.\n";
	}

	// add function
	static void Add(Library* arg) {
		string object;
		cin >> object;
		ToUpper(object);

		if (object == "BOOK") {
			Book* BookToAdd = new Book("", "", 0, 0);
			cout << "Author: ";
			cin >> BookToAdd -> Author;
			cout << "Name: ";
			cin >> BookToAdd -> Name;
			cout << "Price: : ";
			cin >> BookToAdd -> Cost;
			cout << "Number: ";
			cin >> BookToAdd -> Number;
			arg -> AddBook(BookToAdd);
		}
		else if (object == "READER") {
			Reader* ReaderToAdd = new Reader("", "", "", "", "");
			cout << "Surname: ";
			cin >> ReaderToAdd -> Surname;
			cout << "Name: ";
			cin >> ReaderToAdd -> Name;
			cout << "Group: : ";
			cin >> ReaderToAdd -> Group;
			cout << "Phone: ";
			cin >> ReaderToAdd -> Phone;
			cout << "Mail: ";
			cin >> ReaderToAdd -> Mail;
			arg -> AddReader(ReaderToAdd);
		}
		else
			cout << "Unknown object. Try again.\n";
	}

	// find function
	static void Find(Library* arg) {
		string object;
		cin >> object;
		ToUpper(object);

		if (object == "BOOK") {
			string name;
			cout << "Name: ";
			cin >> name;
			Book* BookToDisplay = arg -> FindBook(name);

			if (BookToDisplay != NULL)
				BookToDisplay -> Display();
			else
				cout << "Book not found. Try again.\n";
		}
		else if (object == "READER") {
			string surname;
			cout << "Surname: ";
			cin >> surname;
			string name;
			cout << "Name: ";
			cin >> name;
			Reader* ReaderToDisplay = arg -> FindReader(surname, name);

			if (ReaderToDisplay != NULL)
				ReaderToDisplay -> Display();
			else
				cout << "Reader not found. Try again.\n";
		}
	}

	// delete function
	static void Delete(Library* arg) {
		string object;
		cin >> object;
		ToUpper(object);

		if (object == "BOOK") {
			Book* BookToDelete = new Book("", "", 0, 0);
			cout << "Name of the book: ";
			cin >> BookToDelete -> Name;
			BookToDelete = arg -> FindBook(BookToDelete -> Name);

			if (BookToDelete != NULL && arg -> RemoveBook(BookToDelete))
				cout << "Success.\n";
			else
				cout << "Not done. Try again.\n";
		}
		else if (object == "READER") {
			Reader* ReaderToDelete = new Reader("", "", "", "", "");
			cout << "Surname: ";
			cin >> ReaderToDelete -> Surname;
			cout << "Name: ";
			cin >> ReaderToDelete -> Name;
			ReaderToDelete = arg -> FindReader(ReaderToDelete -> Surname, ReaderToDelete -> Name);

			if (ReaderToDelete != NULL && arg -> RemoveReader(ReaderToDelete))
				cout << "Success.\n";
			else
				cout << "Not done. Try again.\n";
		}
	}

	// borrow function
	static void Borrow(Library* arg) {
		Book* BookToBorrow = new Book("", "", 0, 0);
		cout << "Name of the book: ";
		cin >> BookToBorrow -> Name;

		Reader* ReaderToBorrow = new Reader("", "", "", "", "");
		cout << "Surname: ";
		cin >> ReaderToBorrow -> Surname;
		cout << "Name: ";
		cin >> ReaderToBorrow -> Name;

		BookToBorrow = arg -> FindBook(BookToBorrow -> Name);
		ReaderToBorrow = arg -> FindReader(ReaderToBorrow -> Surname, ReaderToBorrow -> Name);

		if (BookToBorrow != NULL && ReaderToBorrow != NULL) {
			if (arg -> Borrow(ReaderToBorrow, BookToBorrow))
				cout << "Success.\n";
			else
				cout << "Unable to borrow.\n";
		}
		else
			cout << "Data is incorrect. Try again.\n";
	}

	// return function
	static void Return(Library* arg) {
		Book* BookToReturn = new Book("", "", 0, 0);
		cout << "Name of the book: ";
		cin >> BookToReturn -> Name;

		Reader* ReaderToReturn = new Reader("", "", "", "", "");
		cout << "Surname: ";
		cin >> ReaderToReturn -> Surname;
		cout << "Name: ";
		cin >> ReaderToReturn -> Name;

		BookToReturn = arg -> FindBook(BookToReturn -> Name);
		ReaderToReturn = arg -> FindReader(ReaderToReturn -> Surname, ReaderToReturn -> Name);

		if (BookToReturn != NULL && ReaderToReturn != NULL) {
			if (arg -> Return(ReaderToReturn, BookToReturn))
				cout << "Success.\n";
			else
				cout << "Data is incorrect. Try again.\n";
		}
		else
			cout << "Data is incorrect. Try again.\n";
	}

	// save function
	static void Save(Library* arg) {
		string object;
		cin >> object;
		ToUpper(object);

		if (object == "BOOKS") {
			arg -> SaveBooks();
			cout << "Success.\n";
		}
		else if (object == "READERS") {
			arg -> SaveReaders();
			cout << "Success.\n";
		}
		else if (object == "BORROWINGS") {
			arg -> SaveBorrowings();
			cout << "Success.\n";
		}
		else
			cout << "Unknown object. Try again.\n";
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Library* MyLibrary = new Library("_in_Readers.txt", "_in_Books.txt", "_in_Borrowings.txt");
	Interface* MyInterface = new Interface();

	while (true) {
		if (MyInterface -> ChooseCommand(MyLibrary))
			break;
	}

	return 0;
}

//---------------------------------------------------------------------------
