#pragma once

class CException {
private:
	char* msg;
public:
	CException(char* message);
	~CException();

	void show(void);
};