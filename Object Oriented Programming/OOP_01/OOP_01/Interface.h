#pragma once
#include "CBlackJack.h"
#define PLAYERS_LIMIT 8

void input(int&, int, char); // Функція введення
bool outputMenu(void); // Меню
bool GameMenu(CBlackJack* (&)); // Ігрового меню