#include "Interface.h"
#include <cstdio>

// Функція введення
void input(int& x, int limit, char ch) {
	printf("Input %c: ", ch);

	scanf("%d", &x);
	while (x <= 0 && x >= limit) {

		printf("Wrong number! Try again. ");
		scanf("%d", &x);

	}
}

// Виведення меню
bool outputMenu(void) {

	system("cls");
	printf("OOP lab work #1\nTask: Write BlackJack game\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start game\n2. Exit\n\nMake your choice ");

	int t;
	scanf("%d", &t);
	switch (t) {
	case 1: {
		int n, k;

		input(n, PLAYERS_LIMIT, 'n');
		input(k, PLAYERS_LIMIT, 'k');

		CBlackJack* game = new CBlackJack(n, k);
		while (GameMenu(game));

		delete game;
		break;
	}
	case 2: return 0;
	}

	return true;
}

// Ігрового меню
bool GameMenu(CBlackJack* (&game)) {

	system("cls");
	printf("Menu:\n 1. Next game\n 2. Out\nMake your choice: ");

	int t;
	scanf("%d", &t);
	switch (t) {
	case 1: {

		game->newGame();
		game->playing();
		if (game->endingGame()) {
			printf("\n\nGame over! =(\n");
			system("pause");
			return 0;
		}

		break;
	}
	case 2: return 0;
	}

	return 1;
}