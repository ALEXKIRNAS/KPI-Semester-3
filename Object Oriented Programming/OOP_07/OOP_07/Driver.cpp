#include "Driver.h"
#include "CException.h"
#include <string.h>

Driver::Driver(char* name, char* car) {
	if (strlen(name) == 0) throw CException("Empty name of driver");
	if(strlen(car) == 0) throw CException("Empty car name for driver");
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->car = new char[strlen(car) + 1];
	strcpy(this->car, car);

	isOnDuty = false;
	curAddr.x = curAddr.y = 0;
	timeOfEndingOrder = 0;
}

Driver::Driver(const Driver& obj) {
	this->name = new char[strlen(obj.name) + 1];
	strcpy(this->name, obj.name);

	this->car = new char[strlen(obj.car) + 1];
	strcpy(this->car, obj.car);

	this->curAddr = obj.curAddr;
	isOnDuty = false;

	this->timeOfEndingOrder = 0;
}

Driver::~Driver(void) {
	delete[] name;
	name = nullptr;

	delete[] car;
	car = nullptr;
}

void Driver::addTicket(const tuple<Driver, order>&&  ticket) {
	tikets.push_back(ticket);
}

const vector <tuple<Driver, order>>& Driver::getTickets(void) {
	return tikets;
}

bool Driver::getIsOnDuty(void) {
	return isOnDuty;
}

void Driver::setOnDuty(void) {
	isOnDuty = !isOnDuty;
}

void Driver::setAddr(address addr) {
	this->curAddr = addr;
}

short Driver::getTimeOfEndingOrder(void) {
	return timeOfEndingOrder;
}

void Driver::setTimeOfEndingOrder(short time) {
	timeOfEndingOrder = time;
}

address Driver::getAddr(void) {
	return curAddr;
}

const char* Driver::getName(void) {
	return name;
}