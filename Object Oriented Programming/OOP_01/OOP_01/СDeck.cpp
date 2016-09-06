#include "СDeck.h"
#include <cstdlib>

//Видача випадкової карти
char CDeck::Rand(void) {

	int countOfCards = 0;
	for (int i = 0; i < NUM_OF_CARDS; i++) countOfCards += cards[i];

	int numberOfCard = (rand() * 1.0f / static_cast <double> (RAND_MAX)) * countOfCards;

	for(int i = 0; i < NUM_OF_CARDS; i++, numberOfCard -= cards[i]) 
		if (numberOfCard <= cards[i]) {
			cards[i]--;
			return i;
		}
}

// Конструктор класу
CDeck::CDeck(int k) {

	for (int i = 0; i < NUM_OF_CARDS; i++) cards[i] = k;

}

// Визначення кількості карт в колоді заданого типу
int CDeck::haveMushCards(char index) const {
	if (index < NUM_OF_CARDS) return cards[index];
	else return 0;
}