#pragma once
#define NUM_OF_CARDS 52 // Кількість різних карт в колоді

// Клас колоди карт
class CDeck {
private:
	int cards[NUM_OF_CARDS]; // Кількість карт кожного типу в колоді
public:
	char Rand(void); //Видача випадкової карти
	CDeck(int k); // Конструктор класу
	int haveMushCards(char) const; // Визначення кількості карт в колоді заданого типу
};