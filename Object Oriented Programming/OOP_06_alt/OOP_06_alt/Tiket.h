#pragma once

template <class ... Data>
class Ticket : public Data... {
public:
	Ticket(const Data& ... data) : Data(data)... {}
};