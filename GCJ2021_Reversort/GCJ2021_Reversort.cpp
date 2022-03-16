/* Google Codejam 2021 Qualifier Reversort
Problem
Note: The main parts of the statements of the problems "Reversort" and "Reversort Engineering" are identical, except for the last paragraph. The problems can otherwise be solved independently.

Reversort is an algorithm to sort a list of distinct integers in increasing order. The algorithm is based on the "Reverse" operation. Each application of this operation reverses the order of some contiguous part of the list.

The pseudocode of the algorithm is the following:

Reversort(L):
  for i := 1 to length(L) - 1
    j := position with the minimum value in L between i and length(L), inclusive
    Reverse(L[i..j])
After i−1 iterations, the positions 1,2,…,i−1 of the list contain the i−1 smallest elements of L, in increasing order. During the i-th iteration, the process reverses the sublist going from the i-th position to the current position of the i-th minimum element. That makes the i-th minimum element end up in the i-th position.

For example, for a list with 4 elements, the algorithm would perform 3 iterations. Here is how it would process L=[4,2,1,3]:

i=1, j=3⟶L=[1,2,4,3]
i=2, j=2⟶L=[1,2,4,3]
i=3, j=4⟶L=[1,2,3,4]
The most expensive part of executing the algorithm on our architecture is the Reverse operation. Therefore, our measure for the cost of each iteration is simply the length of the sublist passed to Reverse, that is, the value j−i+1. The cost of the whole algorithm is the sum of the costs of each iteration.

In the example above, the iterations cost 3, 1, and 2, in that order, for a total of 6.

Given the initial list, compute the cost of executing Reversort on it.

Input
The first line of the input gives the number of test cases, T. T test cases follow. Each test case consists of 2 lines. The first line contains a single integer N, representing the number of elements in the input list. The second line contains N distinct integers L1, L2, ..., LN, representing the elements of the input list L, in order.

Output
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the total cost of executing Reversort on the list given as input.

Limits
Time limit: 10 seconds.
Memory limit: 1 GB.
Test Set 1 (Visible Verdict)
1≤T≤100.
2≤N≤100.
1≤Li≤N, for all i.
Li≠Lj, for all i≠j.*/
//#define DEBUG

#include <iostream>

void SwapInt(int* int1, int* int2);
unsigned int GetIndexOfMin(const int* array, unsigned int size);
void Randomize(int* array, unsigned int size, unsigned int repeats = 5);
void Reverse(int* array, unsigned int size);
void PrintArray(const int* array, unsigned int size);
unsigned int ReverSort(int* array, unsigned int size);

int main()
{    
    unsigned int T;
    std::cin >> T;

    static const unsigned int Nmax = 100;
    unsigned int N = 0;
    int L[Nmax] = {};
    unsigned int cost = 0;
    for (unsigned int i = 1; i <= T; i++)
    {
        std::cin >> N;        
        for (int j = 0; j < N; j++)
        {
            std::cin >> L[j];
        }        
                        
        std::cout << "Case #" << i << ": " << ReverSort(L, N) << "\n";
    }         
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
