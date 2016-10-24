#pragma once
#define countOfNegativeElemnts 128
#define baseElement unsigned __int64
#define capacity 4

class set {
private:
	baseElement elements[capacity]; // CharSet

	static char nextElement(char* (&ptr)); // Get next char-element from input
	static int index(const char &c); // Getting index in table of CharSet
	static int position(const char &c); // Getting position character in table cell
	static int CharToIndex(const char& c); // Getting index by character
	static char IndexToChar(const int& _index); // Getting character by index
	bool cheak(const int& index) const; // Cheaking index-byte

public:
	set(void); // Default constructor
	set(char* str); // Constructor
	void printSet(void) const; // Output all CharSet on screen

	// ---- OPERATIONS ----
	//Union
	const set operator+ (const set &obj) const;
	set& operator+= (const set &obj);

	//Difference
	const set operator- (const set &obj) const;
	set& operator-= (const set &obj);

	//Intersection
	const set operator* (const set &obj) const;
	set& operator*= (const set &obj);

	// Adding and remove
	set& operator<<= (const char& c);
	set& operator>>= (const char& c); 
};