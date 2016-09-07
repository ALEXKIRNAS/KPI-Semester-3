#include "CBlackJack.h"
#include "Interface.h"
#include <cstdlib>
#include <ctime>

int main(void) {
	srand(time(NULL));
	while (outputMenu());
}