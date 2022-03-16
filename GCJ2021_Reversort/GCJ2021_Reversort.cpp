// GCJ2021_Reversort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define DEBUG

#include "GCJ2021_Reversort.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstddef>

int main()
{
    std::ifstream input;
    std::ofstream output;
    //myFile.open("sample_ts1_input.txt");
    input.open("ts1_input.txt"); 
    output.open("ts1_myoutput.txt");
    std::string line;
    
    if (!input.is_open() || !output.is_open())
    {
        std::cout << "file not found :(\n";
        return 1;
    }

    getline (input, line);
    unsigned int T = std::stoi(line); //number of tests

    static const unsigned int Nmax = 100;
    unsigned int N = 0;
    int L[Nmax] = {};
    unsigned int cost = 0;
    for (unsigned int i = 0; i < T; i++)
    {
        getline(input, line); // gather number of ints in this test
        N = std::stoi(line);        
        getline(input, line); // gather int values in this test
        splitString(line, ' ', [&L](const std::string& s, std::size_t from, std::size_t to, unsigned int index) {
            L[index] = std::stoi(s.substr(from, to - from));
            });
                        
        output << "Cost #" << i + 1 << ": " << ReverSort(L, N) << "\n";
    }         

    input.close();
    output.close();
}

template<typename StringFunction>
void splitString(const std::string& str, char delimiter, StringFunction f) {
    std::size_t from = 0;
    unsigned int index = 0;
    for (std::size_t i = 0; i < str.size(); ++i) {
        if (str[i] == delimiter) {
            f(str, from, i, index);
            from = i + 1;
            index++;
        }
    }
    if (from <= str.size())
        f(str, from, str.size(), index);
}

/**
 * @brief Run reversort algorithm to sort the array
 * @param array both input and output
 * @param size 
 * @return cost of the sort in terms of total number of integers processed by the Reverse(...) command.  Reverse on a sublist of 1 counts as cost of 1 even though no work is done.
*/
unsigned int ReverSort(int* array, unsigned int size)
{
    unsigned int cost = 0;
    unsigned int incrementalCost = 0;

    for (unsigned int i = 0; i < size - 1; i++)
    {
        unsigned int j = GetIndexOfMin(&array[i], size - i) + i;
#ifdef DEBUG
        std::cout << "  Before reversing (" << i << ":" << j << ") ";
        PrintArray(array, size);
#endif
        Reverse(&array[i], static_cast<unsigned int>(1U + j - i));

        incrementalCost = (1 + j - i);
#ifdef DEBUG
        std::cout << "  After reversing cost(" << incrementalCost << ") ";
        PrintArray(array, size);        
#endif
        cost += incrementalCost;
    }    

    return cost;
}

/**
 * @brief Find the minimum integer value in an array.  If there are multiple of the same value, the index of the first is returned 
 * @param array 
 * @param size 
 * @return index of the array element with the min value. If there are multiple of the same value, the index of the first is returned 
*/
unsigned int GetIndexOfMin(const int* array, unsigned int size)
{
    unsigned int indexOfMin = 0;    
    for (unsigned int i = 1; i < size; i++)
    {
        if (array[i] < array[indexOfMin])
        {
            indexOfMin = i;
        }
    }    

    return indexOfMin;
}

/**
 * @brief Reverse the order of elements in an array
 * @param array both input and output
 * @param size 
*/
void Reverse(int* array, unsigned int size)
{ 
    for (unsigned int i = 0; i < static_cast<unsigned int>(size / 2); i++)
    { 
        SwapInt(&array[i], &array[size - 1 - i]);
    }
}

/**
 * @brief Swaps location of 2 integer values
 * @param int1 
 * @param int2 
*/
void SwapInt(int* int1, int* int2)
{
#ifdef DEBUG
    std::cout << "      swapping: " << *int1 << ":" << *int2 << "\n";
#endif

    int temp = *int1;
    *int1 = *int2;
    *int2 = temp;    
}

/**
 * @brief Randomize an integer array.
 * @param array both input and output
 * @param size 
 * @param repeats number of passes to take (default 5)
*/
void Randomize(int* array, unsigned int size, unsigned int repeats)
{
    if (repeats < 1)
    {
        repeats = 1;
    }

    srand(time(NULL));

    for (unsigned int j = 0; j < repeats; j++)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            SwapInt(&array[i], &array[rand() % size]);
        }
    }
}

/**
 * @brief prints an array to the console in the form [#,#,#,#,...]
 * @param array 
 * @param size 
*/
void PrintArray(const int* array, unsigned int size)
{
    std::cout << "[";
    for (unsigned int i = 0; i < size - 1; i++)
    {
        std::cout << array[i] << ",";
    }
    std::cout << array[size - 1];
    std::cout << "]\n";
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
