#include "iostream"
using namespace std;

#ifdef DEMO1

template <class T>
class Buffer
{
	T dado;
public:
	Buffer(T& d) { dado = d; }
	
	void print(  ) {
		cout << dado << endl;
	}
};
#endif

///////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEMO2

#include <vector>
using namespace std;

template <class T>
class MeuTipo
{
	vector<T> vetor;
	
public: 
	typedef typename vector<T>::iterator iterator;
	
	MeuTipo( void ) {};
	MeuTipo( T& param ){
		for( int i = 0; i < 10; i++ ){
			T c = param;
			c = (T) (c + i);
			vetor.push_back(c);
		}
	};
	void print( void ) {
		for( int i = 0; i < 10; i++ ) {
			cout << vetor[i];
			cout << " ";
		}
	cout << endl;
	}
	iterator begin( void ) {
		return vetor.begin();
	}
	iterator end( void ){
		return vetor.end();
	}
	T& operator [] ( int i ) {
		return vetor[i];
	}
};
			
//////////////////////////////////////////////////////////////////////////////			

template <class T>
class Buffer
{
	T dado;
public:
	Buffer(T& d) { dado = d; }
	
	void print(  ) {
		dado.print();
	}

	void printIterator( void ) 
	{
		typename T::iterator it;
		it = dado.begin();
		while( it != dado.end() ) {
			cout << *(it);
			cout << " ";
			it++;
		}
		cout << endl;
	}
	
};
#endif
