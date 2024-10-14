#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Nome: Felipe Braz Marques
Matrícula: 22.1.4030

Como executar o código: gcc qA.c -o main -Wall
                        ./main

A análise assintótica pode ser feita da seguinte forma:
T(1) = 1
T(n) = 2T(n/2) + 7
T(n) = 2T(n/2) + O(1)

Pelo teorema mestre:
a = 2, b = 2, d = 0
log2 2 > 0

findMaxValue() = O(n)
*/

void findMaxValue(int* vector, int left, int right, int* maximum)
{
    if (right <= left)                            //1
        return;                                   //1
    
    int middle = (left + right) / 2;              //1
    if (vector[middle] > *maximum)                //2
    {
       *maximum = vector[middle];                 //2 
    }
 
    findMaxValue(vector, left, middle, maximum);       // T(n/2)
    findMaxValue(vector, middle + 1, right, maximum);  // T(n/2)
}

int main()
{
    int vector[] = {7, 9, 5, 8, 11, 15};
    int length = sizeof(vector) / sizeof(vector[0]);
    int maximum = vector[0];
    
    findMaxValue(vector, 0, length, &maximum);
    
    printf("The highest value in the vector is: %d\n", maximum);
    
    return 0;
}

/*

Output: 
The highest value in the vector is: 15

*/