#include "Interface.h"
#include <cstdio>
#include <time.h>


// ������� ��������
void input(int& x, int limit, char ch) {
	printf("Input %c: ", ch);

	scanf("%d", &x);
	while (x <= 0 || x >= limit) {

		printf("Wrong number! Try again. ");
		scanf("%d", &x);

	}
}

// ��������� ����
bool outputMenu(void) {

	system("cls");
	printf("OOP lab work #1\nVariant - 7, Level - C\nTask: Write BlackJack game\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start game\n2. Exit\n\nMake your choice ");

	int t;
	scanf("%d", &t);
	switch (t) {
	case 1: {
		int n, k;

		input(n, PLAYERS_LIMIT, 'n');
		input(k, PLAYERS_LIMIT, 'k');

		time_t rawtime;
		struct tm * timeinfo;
		char buffer[200];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 200, "%d.%m.%Y-%H.%M.%S.log", timeinfo);
		FILE* file = fopen(buffer, "wt");

		fprintf(file, "Beging loging:");

		CBlackJack* game = new CBlackJack(n, k, file);
		while (GameMenu(game));

		fprintf(file, "End of log");

		fclose(file);

		delete game;
		break;
	}
	case 2: return 0;
	}

	return true;
}

// �������� ����
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