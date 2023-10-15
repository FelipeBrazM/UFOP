#ifdef CONJORDENADO_H
#define CONJORDENADO_H

#include <vector>

using namespace std;

template <typename T> class ConjOrdenado{
private: 
    vector<T> vetor;
public:
    ConjOrdenado(){};
    ConjOrdenado(T& param, int quant){
        for(int i = 0; i < quant; i++){
            T c = param;
            c = (T) (c + i);
            vetor.push_back(param);
            sort(vetor.begin(), vetor.end());
        }
    };

    void print(void){
        for(int i = 0; i < vetor.size(); i++){
            cout << vetor[i] << " ";
        }
        cout << endl;
    };

    interator begin(void){
        return vetor.begin();
    };

    interator end(void){
        return vetor.end();
    };

    T& operator [] (int i){
        return vetor[i];
    }
};

#endif