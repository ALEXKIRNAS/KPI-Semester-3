#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define BLOCK 512 // ����� ����� ��� �������
#define DONE 20 // ʳ������ ����� ��� �������� ��������� ����� ���������

void input_name(char* title, string& name); // �������� �����
void cpyFile(string& from, string& to); // ��������� �����