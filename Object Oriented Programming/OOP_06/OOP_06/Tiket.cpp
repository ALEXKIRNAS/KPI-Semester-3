#include "Tiket.h"
#include <string.h>

Ticket::Ticket(char* name, int cost) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->cost = cost;
}

Ticket::Ticket(const Ticket& obj) {
	this->name = new char[strlen(obj.getName()) + 1];
	strcpy(this->name, obj.name);
	this->cost = obj.cost;
}

const char* Ticket::getName(void) const {
	return name;
}

int Ticket::getCost(void) const{
	return cost;
}
Ticket::~Ticket(void) {
	delete[] name;
	name = nullptr;
}