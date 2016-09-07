#pragma once
#define NUM_OF_CARDS 52 // ʳ������ ����� ���� � �����

// ���� ������ ����
class CDeck {
private:
	int cards[NUM_OF_CARDS]; // ʳ������ ���� ������� ���� � �����
public:
	char Rand(void); //������ ��������� �����
	CDeck(int k); // ����������� �����
	int haveMushCards(char) const; // ���������� ������� ���� � ����� �������� ����
	int countTotal(void) const;  //  ����������� ������� ����, �� ���������� � �����
	int countLessThat(char) const; // ���������� ������� ����, �� �� ����� �� ������
};