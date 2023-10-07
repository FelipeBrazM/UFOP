#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   
    cout << 0xFF <<endl; 
   
    //-----------------------------------------------------------------
    char *pChar;
    char disciplina[] = "Tecnicas de Programação II";

    pChar = disciplina;
    while( *pChar != '\0' ) {
           
           cout << *pChar;
           pChar++;
    }
    cout << endl;
    system("PAUSE");
    
    //-----------------------------------------------------------------
        
    int algarismos[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int *pInt = algarismos;
    
    do {       
           cout << *pInt << ", " << pInt << endl;
           pInt++;
    } while( *pInt != 9 );
    cout << "----- sizeof(int): " << sizeof(int) << endl;
    system("PAUSE");
    
    //-----------------------------------------------------------------
    
    pChar = (char *) algarismos;
    for( int i = 0; i < 10; i++  ) {
           
           cout << *pChar << ", " << pChar << endl;
           pChar++;
    }
    cout << endl;
    system("PAUSE");
    
    return EXIT_SUCCESS;
}
