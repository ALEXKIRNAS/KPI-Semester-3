#include "CException.h"
#include <cstdio>
#include <string.h>

CException::CException(char* message) {
	msg = new char[strlen(message) + 1];
	strcpy(msg, message);
}

CException::~CException() {
	delete[] msg;
	msg = nullptr;
}

void CException::show(void) {
	printf("%s\n", msg);
}