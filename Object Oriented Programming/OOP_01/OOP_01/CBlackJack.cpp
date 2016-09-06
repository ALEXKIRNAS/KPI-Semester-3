#include "CBlackJack.h"

// Виводить карту на екран
void CBlackJack::whatThisCard(char card) const {
	char number = card / 4 + 1;
	
	if (number <= 10) printf("%d", number);
	else switch (number) {
		case 11: printf("V"); break;
		case 12: printf("D"); break;
		case 13: printf("K"); break;
		case 14: printf("T"); break;
	};

	printf("%c ", char(card % 4));
}

// Визначає ціну карти
char CBlackJack::costOfCard(char card) const {
	char number = card / 4 + 1;

	if (number <= 10) return number;
	else if (number != 14) return 10;
	else return 11;

}

// Визначення ціни всіх карт у гравця
char CBlackJack::playerCostCards(const CPlayer& player) const {
	int cost = 0;
	vector <char> cards = player.listOfCards();

	for (int i = 0, size = cards.size(); i < size; i++)
		cost += costOfCard(cards[i]);

	return cost;
}

// Ініціалізація гри
CBlackJack::CBlackJack(int n, int k) {
	this->n = n; this->k = k;

	players = new CPlayer[(n + 1) * 2];

	out = new bool[n];
	for (int i = 0; i < n; i++) out[i] = false;
}

// Очищення гри
CBlackJack::~CBlackJack(void) {
	delete[] out;
}

// Нова гра
void CBlackJack::newGame(void) {

	for (int i = 0; i < n; i++)
		if (!players[i].giveMoney(COST_OF_GAME)) out[i] = true;

	deck = new CDeck(k);

	for (int i = 0; i < 2; i++)
		for (int z = 0; z <= n; z++)
			players[z].addcard(deck->Rand());

}

// Процес гри
void CBlackJack::playing(void) {
	printState();

	actionPlayer(players[0]);

	for (int i = 0; i < n; i++)
		actionAI(players[i]);

	actionGod(players[n]);

	printState();
}

// Завершення гри
void CBlackJack::endingGame(void) {
	int cost = playerCostCards(players[n]);

	for (int i = 0; i < n; i++) {
		int playercost = playerCostCards(players[i]);

		if ((playercost == cost && players[i].listOfCards().size() == 2) || playercost > cost ) players[i].giveMoney(-2 * COST_OF_GAME);
	}

}

// Вибір гравцем дій
void CBlackJack::actionPlayer(CPlayer& player) {

	while (true) {
		int cost = playerCostCards(player);

		printf("\nCurrent cost: %d", cost);
		printf("\nDo you want new card? (Y\\N)");
		
		char str[10];
		scanf("%s", str);
		if (*str == 'Y' || *str == 'y') player.addcard(deck->Rand());
		else if (*str == 'n' || *str == 'N') break;
		else printf("Wrong letter! Try again.\n");
	}


}

// Виконання дій компютером
void CBlackJack::actionAI(CPlayer& player) {

	int cost = playerCostCards(player);

	while (player.checkChance(deck, players[n].lastCard(), std::max(0, 21 - cost))) {
		player.addcard(deck->Rand());
		cost = playerCostCards(player);
	}
}

// Виконання дій ділера
void CBlackJack::actionGod(CPlayer& player) {
	int cost = playerCostCards(player);

	while (cost < 17) {
		player.addcard(deck->Rand());
		cost = playerCostCards(player);
	}
}

// Виведення стану гри
void CBlackJack::printState(void) {
	
	for (int i = 0; i <= n; i++) {
		printf("%d:\n", i);
		vector <char> cards = players[i].listOfCards();

		for (int z = 0, size = cards.size(); z < size; z++) whatThisCard(cards[z]);
		printf("%d", playerCostCards(players[i]));
		printf("\n\n");
	}

}