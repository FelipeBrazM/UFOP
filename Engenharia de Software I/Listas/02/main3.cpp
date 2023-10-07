#include <cstdlib>
#include <iostream>

//#define ERROR1
//#define ERROR2

using namespace std;

int main(int argc, char *argv[])
{
	#ifndef ERROR1
	cout << "static" << endl;
    static int teste = 1, teste3 = 1;
    static int variavel = 65;
	#else
	cout << "NOT static" << endl;
	int teste, teste3; 
    int variavel = 65; 
    #endif
	
	cout << teste << endl;
    cout << "&variavel: "<< &variavel << ", variavel: " << (char) variavel <<endl;
    cout << 0xFF << endl; 
    cout << endl;
    system("PAUSE");          
    cout << endl << endl;
    
    {
         unsigned int* pInt = (unsigned int*) 0x40300c; 
         cout << "&pInt: " << &pInt << ", pInt: " << pInt << ", *pInt: " << *pInt << endl;
         *pInt = 66;
         cout << "&variavel: "<< &variavel << ", variavel: " << (char) variavel <<endl;
    }
    system("PAUSE");          
    cout << endl << endl;
       

    #ifndef ERROR2
    {
		
         unsigned int* pInt = NULL;
		 cout << "not ERRO2" << endl;
         cout << "&pInt: "<< &pInt << ", pInt: " << pInt << ", Valid? ";
         cout << (( pInt ) ? "TRUE" : "FALSE" ) << endl;
         cout << (( pInt != NULL ) ? "TRUE" : "FALSE" ) << endl;
         pInt = (unsigned int* )0x40300c; 
         cout << "&pInt: "<< &pInt << ", pInt: " << pInt <<", " << " -> ";
         cout << (( pInt != NULL ) ? "TRUE" : "FALSE" ) << endl;
		 *pInt = '7'; 
    }
    #else
    {	
         unsigned int* pInt;
		 cout << "ERRO2" << endl;
         cout << "&pInt: "<< &pInt << ", pInt: " << pInt << ", Valid? ";
         cout << (( pInt ) ? "TRUE" : "FALSE" ) << endl;
         cout << (( pInt != NULL ) ? "TRUE" : "FALSE" ) << endl;
         pInt = (unsigned int* )0x40300c; 
         cout << "&pInt: "<< &pInt << ", pInt: " << pInt <<", " << " -> ";
         cout << (( pInt != NULL ) ? "TRUE" : "FALSE" ) << endl;
    }        
    #endif
    cout << endl;
    system("PAUSE");             
    cout << endl << endl;

  
    return EXIT_SUCCESS;
}
