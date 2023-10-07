#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World" << endl;
    
    char c;
    int incr;
    while ( c != 's') {
    
         cin >> c;
    
        cout << (incr = (int) ('A' - 'a')) << endl;
        cout << "Caracter: " << (char)(c - 32) << endl;
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
