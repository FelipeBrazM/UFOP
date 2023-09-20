/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef PESSOA_H
#define PESSOA_H

#include "Cadastro.h"
#include <iostream>
#include <string>
using namespace std;

class Pessoa {
    int id;
    static int incrementador; //variavel para setar o id de cada instancia
    string nome;
    Cadastro * cadastro;

public:
    Pessoa(string="", Cadastro * = new Cadastro());
    virtual ~Pessoa();

    string getNome() const;
    void setNome(string);

    int getId() const;

    Cadastro* getCadastro() const;
    void setCadastro(Cadastro *);

    void serialize(ostream&) const;
    friend ostream & operator<< (ostream & out, const Pessoa & obj);
};

#endif