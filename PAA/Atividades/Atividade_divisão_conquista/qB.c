#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Nome: Felipe Braz Marques
Matrícula: 22.1.4030

Como executar o código: gcc qB.c -o main -Wall
                        ./main

A análise assintótica pode ser feita da seguinte forma:
T(1) = 1
T(n) = 2T(n/2) + 7
T(n) = 2T(n/2) + O(1)

Pelo teorema mestre:
a = 2, b = 2, d = 0
log2 2 > 0

findMaxMinValues() = O(n)
*/

void findMaxMinValues(int* vector, int left, int right, int* maximum, int* minimum)
{
    if (right <= left)                                   //1
        return;                                          //1
    
    int middle = (left + right) / 2;                     //1
    
    if (vector[middle] > *maximum)                       //1
    { 
       *maximum = vector[middle];                        //1
    }
    if (vector[middle] < *minimum)                       //1
    {
        *minimum = vector[middle];                       //1
    }
 
    findMaxMinValues(vector, left, middle, maximum, minimum);        // T(n/2)
    findMaxMinValues(vector, middle + 1, right, maximum, minimum);   // T(n/2)  
}

int main()
{
    int vector[] = {7, 9, 5, 8, 11, 15};
    int length = sizeof(vector) / sizeof(vector[0]);
    int maximum = vector[0];
    int minimum = 100000000;
    
    findMaxMinValues(vector, 0, length, &maximum, &minimum);
    
    printf("The highest value in the vector is: %d\n", maximum);
    printf("The lowest value in the vector is: %d\n", minimum);   
    return 0;
}

/*
Output: 
The highest value in the vector is: 15
The lowest value in the vector is: 5

*/