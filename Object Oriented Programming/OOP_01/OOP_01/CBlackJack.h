#pragma once
#include "CPlayer.h"
#include "�Deck.h"
#include <cstdio>
#include <algorithm>

#define COST_OF_GAME 500

class CBlackJack {
private:
	CPlayer* players; // ���� �������
	CDeck* deck; // ������ ����
	bool* out;  // ������ �� �������� ���

	int n; // ʳ������ �������
	int k; // ʳ������ �����

	void actionPlayer(CPlayer&);  // ���� ������� ��
	void actionAI(CPlayer&); // ��������� �� ����������
	void actionGod(CPlayer&); // ��������� �� �����

	void whatThisCard(char) const; // �������� ����� �� �����
	char costOfCard(char) const; // ������� ���� �����
	char playerCostCards(const CPlayer& player) const; // ���������� ���� ��� ���� � ������

	void printState(void); // ��������� ����� ���

public:

	CBlackJack(int, int); // ����������� ���
	~CBlackJack(void); // �������� ���

	void newGame(void); // ���� ���
	void playing(void); // ������ ���
	void endingGame(void); // ���������� ���
};