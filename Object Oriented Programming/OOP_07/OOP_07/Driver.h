#pragma once
#include "Address.h"
#include "Order.h"
#include <vector>
#include <tuple>
using std::vector;
using std::tuple;

class Driver {
private:
	char* name;
	char* car;
	vector <tuple <Driver, order>> tikets;

	address curAddr; // Current address
	bool isOnDuty;
	short timeOfEndingOrder;
public:

	Driver(char* name, char* car);
	Driver(const Driver& obj);
	~Driver(void);

	void addTicket(const tuple<Driver, order>&&  ticket);
	const vector <tuple<Driver, order>>& getTickets(void);

	bool getIsOnDuty(void);
	void setOnDuty(void);
	void setAddr(address);
	address getAddr(void);
	short getTimeOfEndingOrder(void);
	void setTimeOfEndingOrder(short time);
	const char* getName(void);
};