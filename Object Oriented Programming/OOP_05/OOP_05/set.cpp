#include "set.h"
#include "CException.h"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>

// Get next char-element from input
char set::nextElement(char* (&ptr)) {
	while (*ptr == ' ') ptr++; // Eating space elements before symbol

	char symbol = *ptr;
	ptr++;

	while (*ptr == ' ') ptr++; // Eateing space elents after symbol

	if (*ptr != ',' && *ptr) {
		char msg[sizeT];
		msg[0] = 0;
		strcpy(msg, "Error! Wrong input format!!! Expected \",\" but found:\n");
		strcat(msg, ptr);

		throw CException(msg);
		system("pause");
	}

	if(*ptr) ptr++;
	return symbol;
}

// Getting index in table of CharSet
inline int set::index(const char &c) {
	return CharToIndex(c) / (sizeof(baseElement) * 8);
}

// Getting position character in table cell
inline int set::position(const char &c) {
	return CharToIndex(c) % (sizeof(baseElement) * 8);
}

// Getting character index
inline int set::CharToIndex(const char& c) {
	return static_cast<int> (c) + countOfNegativeElemnts;
}

// Getting character by index
inline char set::IndexToChar(const int& index) {
	return static_cast<char> (index - countOfNegativeElemnts);
}

// Cheaking index-byte
bool set::cheak(const int& _index) const{
	int base = (sizeof(baseElement) * 8);
	return elements[_index / base] & (1ll << position(_index % base));
}

// Default constructor
set::set(void) {
	for (int i = 0; i < capacity; i++) elements[i] = 0;
}

// Constructor
set::set(char* str) {
	
	for (int i = 0; i < capacity; i++) elements[i] = 0;

	while (*str){
		char symbol = nextElement(str);
		(*this) <<= symbol;
	}

}

// Output all CharSet on screen
void set::printSet(void) const {
	bool flag = false;
	bool isFirst = true;

	for (int i = 0, size = sizeof(baseElement) * capacity * 8; i < size; i++)
		if (cheak(i)) {
			if (!isFirst) printf(", ");
			printf("%c", IndexToChar(i));

			flag = true;
			isFirst = false;
		}

	if (!flag) printf("CharSet is Empty!");
}

// ---- OPERATIONS ----

//Union
const set set::operator+ (const set &obj) const {
	set tmp = (*this);
	for (int i = 0; i < capacity; i++)
		tmp.elements[i] |= obj.elements[i];

	return tmp;
}

set& set::operator+= (const set &obj) {
	for (int i = 0; i < capacity; i++)
		this->elements[i] |= obj.elements[i];

	return (*this);
}

//Difference
const set set::operator- (const set &obj) const {
	set tmp(*this);
	for (int i = 0; i < capacity; i++)
		tmp.elements[i] ^= this->elements[i] & obj.elements[i];

	return tmp;
}

set& set::operator-= (const set &obj) {
	for (int i = 0; i < capacity; i++)
		this->elements[i] ^= this->elements[i] & obj.elements[i];

	return (*this);
}

//Intersection
const set set::operator* (const set &obj) const {
	set tmp;
	for (int i = 0; i < capacity; i++)
		tmp.elements[i] = this->elements[i] & obj.elements[i];

	return tmp;
}

set& set::operator*= (const set &obj) {
	for (int i = 0; i < capacity; i++)
		this->elements[i] &= obj.elements[i];

	return (*this);
}

// Adding and remove
set& set::operator<<= (const char& c) {
	elements[index(c)] |= (1ll << position(c));

	return (*this);
}

set& set::operator>>= (const char& c) {
	if(elements[index(c)] & (1ll << position(c)))
		elements[index(c)] ^= (1ll << position(c));

	return (*this);
}