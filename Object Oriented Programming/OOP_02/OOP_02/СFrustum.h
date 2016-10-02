#pragma once
#include "CTopCircle.h"
#include "CBaseCircle.h"

class CFrustum : public CTopCircle, public CBaseCircle {
private:
	double height; // ������ ������
public:
	CFrustum(pair <double, pair <double, double>> base, pair <double, pair <double, double>> top); // �����������
	double getVolume(void); // ����������� ���
	double getSufaceSquare(void); // ����������� ����� �������
};