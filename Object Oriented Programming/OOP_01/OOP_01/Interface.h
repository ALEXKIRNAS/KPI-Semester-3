#pragma once
#include "CBlackJack.h"
#define PLAYERS_LIMIT 8

void input(int&, int, char); // ������� ��������
bool outputMenu(void); // ����
bool GameMenu(CBlackJack* (&)); // �������� ����