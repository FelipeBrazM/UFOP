#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Nome: Felipe Braz Marques
Matrícula: 22.1.4030

Como executar o código: gcc qC.c -o main -Wall
                        ./main

A análise assintótica pode ser feita da seguinte forma:
T(1) = 1
T(n) = T(n/2) + 7
T(n) = T(n/2) + O(1)

Pelo teorema mestre:
a = 1, b = 2, d = 0
log2 1 > 0

exponentiation() = O(log(n))
*/

int exponentiation(int base, int power)
{
    if (power == 0)                                         // 1
        return 1;                                           // 1
    
    int result = exponentiation(base, power / 2);           // T(n/2)
    
    if (power % 2 == 0)                                     // 2
        return result * result;                             // 2
    else 
        return base * result * result;                      // 3
}

int main()
{
    int base = 2;
    int power = 5;
    int result = exponentiation(base, power);
    
    printf("%d raised to the power of %d is equal to %d\n", base, power, result);
    
    return 0;
}

/*
Output:
2 raised to the power of 5 is equal to 32

*/