#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define BLOCK 512 // Розмір блока для читання
#define DONE 20 // Кількість блоків для виведння поточного стану виконання

void input_name(char* title, string& name); // Введення файлу
void cpyFile(string& from, string& to); // Копіювання файлу