#pragma once
#include <vector>
#include "СDeck.h"
using std::vector;

#define START_MONEY 10000

// Клас гравця
class CPlayer {
private:
	vector <char> cards; // Карти, що є на руках у гравця
	int money; // Кількість грошей (фішок), що є у гравця

public:
	void addcard(char); // Функція добавлення нової карти
	bool giveMoney(int); // Функція знімання наступної ставки
	CPlayer(void);  // Конструктор за замовчуванням
	bool checkChance(const CDeck*, char, char); // Підрахувати ймовірність вибору "хорошої карти"
	char lastCard(void) const; // Показує останню зданю карту
	vector <char> listOfCards(void) const; // Повертає список карт
};