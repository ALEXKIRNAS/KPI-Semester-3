#pragma once
#include "CPlayer.h"
#include "СDeck.h"
#include <cstdio>
#include <algorithm>

#define COST_OF_GAME 500

class CBlackJack {
private:
	CPlayer* players; // Стан гравців
	CDeck* deck; // Колода карт
	bool* out;  // Гравці що покинули гру
	FILE* log; // Файл логу гри

	int n; // Кількість гравців
	int k; // Кількість колод

	void actionPlayer(CPlayer&);  // Вибір гравцем дій
	void actionAI(CPlayer&); // Виконання дій компютером
	void actionGod(CPlayer&); // Виконання дій ділера

	void whatThisCard(char) const; // Виводить карту на екран
	void logCard(char) const; // Записує задану карту в лог
	char costOfCard(char) const; // Визначає ціну карти
	char playerCostCards(const CPlayer& player) const; // Визначення ціни всіх карт у гравця

	void printStateBefore(void); // Виведення стану гри
	void printStateAfter(void); // Виведення стану гри

public:

	CBlackJack(int, int, FILE*); // Ініціалізація гри
	~CBlackJack(void); // Очищення гри

	void newGame(void); // Нова гра
	void playing(void); // Процес гри
	bool endingGame(void); // Завершення гри
};