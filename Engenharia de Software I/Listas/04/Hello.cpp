#define DEMO2

#include "Hello.h"
#include "iostream"
#include "string"
using namespace std;

#ifdef DEMO1
int main()
{
	string nome;
	char c = 'A';
	int i = 65;

	printf("Teste ");
	Buffer<char> cBuf(c); 
	Buffer<int> iBuf(i);
	cBuf.print();
	iBuf.print();
	
	cout << "Digite seu nome: ";
	cin >> nome;
	cout << "Ola " + nome + "!" << endl;
	
	system( "PAUSE" );
	return 0;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////

#ifdef DEMO2
int main()
{
	string nome;
	char c = 'A';
	int i = 65;
	
	MeuTipo<char> mC(c);
	MeuTipo<int> mI(i);
	Buffer< MeuTipo<char> > mBufC(mC);
	Buffer< MeuTipo<int> > mBufI(mI);
	mBufC.print();
	mBufI.print();
	mBufC.printIterator();

	cout << "Digite seu nome: ";
	cin >> nome;
	cout << "Ola " + nome + "!" << endl;
	
	system( "PAUSE" );
	return 0;
}
#endif

