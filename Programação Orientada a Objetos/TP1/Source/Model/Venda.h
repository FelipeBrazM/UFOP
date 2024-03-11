/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef VENDA_H
#define VENDA_H

#include <iostream>
using namespace std;

class Venda{
    int id;
    static int incrementador; //variavel para setar o id de cada instancia
    double valor; //valor unitario de cada item
    int quantidade;

public: 
    Venda(double = 0.0, int = 0);
    virtual ~Venda();

    int getId() const;
    double getValor() const;
    int getQuantidade() const;

    void setValor(double);
    void setQuantidade(int);

    void serialize(ostream&) const;
    friend ostream& operator<<(ostream&, const Venda&);
};

#endif