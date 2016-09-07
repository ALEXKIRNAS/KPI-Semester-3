#include "CBlackJack.h"

// Виводить карту на екран
void CBlackJack::whatThisCard(char card) const {
	char number = card / 4 + 2;
	
	if (number <= 10) printf("%d", number);
	else switch (number) {
		case 11: printf("V"); break;
		case 12: printf("D"); break;
		case 13: printf("K"); break;
		case 14: printf("T"); break;
	};

	printf("-%c ", char(card % 4 + 'a'));
}

// Визначає ціну карти
char CBlackJack::costOfCard(char card) const {
	char number = card / 4 + 2;

	if (number <= 10) return number;
	else if (number != 14) return 10;
	else return 1;

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

	players = new CPlayer[(n + 1)];

	out = new bool[n + 1];
	for (int i = 0; i <= n; i++) out[i] = false;
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
		for (int z = 0; z <= n; z++) //if (!out[z])
			players[z].addcard(deck->Rand());
}

// Процес гри
void CBlackJack::playing(void) {
	printStateBefore();

	actionPlayer(players[0]);

	for (int i = 1; i < n; i++)
		actionAI(players[i]);

	actionGod(players[n]);

	printf("\n\nActions of other players...\n");
	printStateAfter();
	system("pause");
}

// Завершення гри
bool CBlackJack::endingGame(void) {
	int cost = playerCostCards(players[n]);

	for (int i = 0; i < n; i++) {
		int playercost = playerCostCards(players[i]);

		if ((playercost == cost && playercost == 21 && players[i].listOfCards().size() == 2) 
			||  (playercost > cost  && playercost <= 21) || (playercost <= 21 && cost > 21) ) players[i].giveMoney(-2 * COST_OF_GAME);
		players[i].clearCards();
	}

	players[n].clearCards();
	delete deck;

	if (players[0].getMoney() < COST_OF_GAME) return 1;
	return 0;
}

// Вибір гравцем дій
void CBlackJack::actionPlayer(CPlayer& player) {

	while (true) {
		int cost = playerCostCards(player);
		if (cost > 21) break;

		printf("\nYou current cost: %d", cost);
		printf("\nDo you want new card? (Y\\N) ");
		
		char str[10];
		scanf("%s", str);
		if (*str == 'Y' || *str == 'y') {
			char card = deck->Rand();
			player.addcard(card);
			printf("Added card:");
			whatThisCard(card);
			printf("\n");
			system("pause");
		}
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

	while (cost < 17 && player.checkChance(deck, players[n].lastCard(), std::max(0, 21 - cost))) {
		player.addcard(deck->Rand());
		cost = playerCostCards(player);
	}
}

// Виведення стану гри
void CBlackJack::printStateBefore(void) {
	printf("Begin of game status:\n\n");


	for (int i = 0; i < n; i++) if(!out[i]){

		if(i) printf("Player %d:\n", i);
		else printf("You:\n");

		vector <char> cards = players[i].listOfCards();
		printf("Money: %d\nCards: ", players[i].getMoney());

		for (int z = 0, size = cards.size(); z < size; z++) whatThisCard(cards[z]);
		printf("\nTotal cost: %d", playerCostCards(players[i]));
		printf("\n\n");
	}

	printf("God: \n");
	vector <char> cards = players[n].listOfCards();

	for (int z = 0, size = cards.size(); z < (size - 1); z++) whatThisCard(cards[z]);
	printf("*\n\n");
	//printf("\nTotal cost: %d\n\n", playerCostCards(players[n]));

}

// Виведення стану гри
void CBlackJack::printStateAfter(void) {
	printf("End of game status:\n\n");
	int cost = playerCostCards(players[n]);

	for (int i = 0; i < n; i++) if (!out[i]) {
		if (i) printf("Player %d:\n", i);
		else  printf("You:\n");

		vector <char> cards = players[i].listOfCards();
		int playercost = playerCostCards(players[i]);

		for (int z = 0, size = cards.size(); z < size; z++) whatThisCard(cards[z]);
		printf("\nTotal cost: %d", playerCostCards(players[i]));
		printf("\nStatus: %s\n\n", (((playercost == cost && players[i].listOfCards().size() == 2 && playercost == 21)
			|| (playercost > cost  && playercost <= 21) || (playercost <= 21 && cost > 21)) ? "win" : "lose") );
	}

	printf("God: \n");
	vector <char> cards = players[n].listOfCards();

	for (int z = 0, size = cards.size(); z < size; z++) whatThisCard(cards[z]);
	printf("\nTotal cost: %d\n\n", playerCostCards(players[n]));
}