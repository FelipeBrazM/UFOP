#ifndef CONJNAOORDENADO_H
#define CONJNAOORDENADO_H

#include <vector>

using namespace std;

template <typename T > class ConjNaoOrdenado{
private: 
    vector<T> vetor;
public:
    typedef typename vector<T>::iterator iterator;

    ConjNaoOrdenado(){};
    ConjNaoOrdenado(T& param, int quant){
        for(int i = 0; i < quant; i++){
            T c = param;
            c = (T) (c + i);
            vetor.push_back(c);
        }
    };

    void print (void){
        for(int i = 0; i < vetor.size(); i++){
            cout << vetor[i] << " ";
        }
        cout << endl;
    };

    iterator begin(){
        return vetor.begin();
    };

    iterator end(){
        return vetor.end();
    };

    T& operator [](int i){
        return vetor[i];
    }

};

#endif 


