/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef VENDEDOR_H
#define VENDEDOR_H


#include <iostream>
#include <vector>
#include "Funcionario.h"
#include "Venda.h"

using namespace std;

class Vendedor : public Funcionario{
    vector<Venda*> vendas;
    
public:
    Vendedor(string="", Cadastro* = new Cadastro(), double=0);
    virtual ~Vendedor();

    void cadastrarVenda(Venda*);
    void listarVendas();
    double calculaVendas();
    double calcularBonificacao();
    double calcularSalarioFinal();
    vector<Venda*> getVendas();

    void serialize (ostream&);
    friend ostream&  operator<<(ostream&, Vendedor&);
};

#endif
