/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#define CARGA_HORARIA_MENSAL 160 * 60 //considerando 28 dias no mes, 4 semanas, 40 horas semanais

#include "Pessoa.h"
#include "Ponto.h"
#include <vector>

class Funcionario : public Pessoa{
    double salarioHora;
    int minutosPendentes;
    vector<Ponto*> pontos;
    
public:
    Funcionario(string="",  Cadastro* = new Cadastro(), double=0);
    virtual ~Funcionario();

    double getSalarioHora() const;
    void setSalarioHora(double);

    int getMinutosPendentes() const;
    void setMinutosPendentes(int);

    void registrarPonto(Ponto*);
    vector<Ponto*> getPontos() const;

    void serialize(ostream&) const;

    //funcao abstrata, sera utilizada para o polimorfismo
    virtual double calcularSalarioFinal() = 0;
    virtual void listarVendas() = 0;
    virtual double calcularBonificacao() = 0;

};

#endif