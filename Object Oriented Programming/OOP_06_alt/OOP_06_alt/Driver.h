#pragma once
#include "Tiket.h"
#include "Address.h"
#include "Order.h"
#include <vector>
using std::vector;

class Driver {
private:
	char* name;
	char* car;
	vector <Ticket <Driver, order>> tikets;

	address curAddr; // Current address
	bool isOnDuty;
	short timeOfEndingOrder;
public:

	Driver(char* name, char* car);
	Driver(const Driver& obj);
	~Driver(void);

	void addTicket(const Ticket<Driver, order>&&  ticket);
	const vector <Ticket<Driver, order>>& getTickets(void);

	bool getIsOnDuty(void);
	void setOnDuty(void);
	void setAddr(address);
	address getAddr(void);
	short getTimeOfEndingOrder(void);
	void setTimeOfEndingOrder(short time);
	const char* getName(void);
};