/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef CADASTRO_H
#define CADASTRO_H

#include <string>
using namespace std;

class Cadastro{
    string login;
    string senha;
public:
    Cadastro(string = "", string="");
    virtual ~Cadastro();
    
    string getLogin() const;
    void setLogin(string);
    
    string getSenha() const;
    void setSenha(string);
    
    friend bool operator==(const Cadastro&, const Cadastro&);
};
#endif