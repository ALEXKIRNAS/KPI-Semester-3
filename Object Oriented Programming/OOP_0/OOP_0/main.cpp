#include "Interface.h"
#include <cstdlib>

int main(void) {
	string from, to;
	input_name("input", from);
	input_name("output", to);
	cpyFile(from, to);

	system("pause");
}