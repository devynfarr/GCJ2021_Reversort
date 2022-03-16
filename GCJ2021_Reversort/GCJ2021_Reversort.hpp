#pragma once
#include <string>

void SwapInt(int* int1, int* int2);
unsigned int GetIndexOfMin(const int* array, unsigned int size);
void Randomize(int* array, unsigned int size, unsigned int repeats = 5);
void Reverse(int* array, unsigned int size);
void PrintArray(const int* array, unsigned int size);
unsigned int ReverSort(int* array, unsigned int size);

template<typename StringFunction>
void splitString(const std::string& str, char delimiter, StringFunction f);