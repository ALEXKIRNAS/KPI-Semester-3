#include "CBlackJack.h"
#include <cstdlib>
#include <ctime>

int main(void) {
	srand(time(NULL));

	int n = 5, k = 1;
	CBlackJack game(n, k);

	game.newGame();
	game.playing();
	game.endingGame();
}