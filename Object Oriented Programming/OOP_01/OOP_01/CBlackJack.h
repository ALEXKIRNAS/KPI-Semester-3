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
	FILE* log; // ���� ���� ���

	int n; // ʳ������ �������
	int k; // ʳ������ �����

	void actionPlayer(CPlayer&);  // ���� ������� ��
	void actionAI(CPlayer&); // ��������� �� ����������
	void actionGod(CPlayer&); // ��������� �� �����

	void whatThisCard(char) const; // �������� ����� �� �����
	void logCard(char) const; // ������ ������ ����� � ���
	char costOfCard(char) const; // ������� ���� �����
	char playerCostCards(const CPlayer& player) const; // ���������� ���� ��� ���� � ������

	void printStateBefore(void); // ��������� ����� ���
	void printStateAfter(void); // ��������� ����� ���

public:

	CBlackJack(int, int, FILE*); // ����������� ���
	~CBlackJack(void); // �������� ���

	void newGame(void); // ���� ���
	void playing(void); // ������ ���
	bool endingGame(void); // ���������� ���
};