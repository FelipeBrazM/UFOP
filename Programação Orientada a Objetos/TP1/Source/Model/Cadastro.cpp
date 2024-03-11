/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include <iostream>
#include "Cadastro.h"
using namespace std;

Cadastro :: Cadastro(string login, string senha){
    this->login = login;
    this->senha = senha;
}

Cadastro :: ~Cadastro() {}

string Cadastro :: getLogin() const {
    return login;
}

void Cadastro :: setLogin(string login) {
    this->login = login;
}

string Cadastro :: getSenha() const {
    return senha;
}

void Cadastro :: setSenha(string senha) {
    this->senha = senha;
}

bool operator==(const Cadastro& a, const Cadastro& b){
    return (a.senha == b.senha && a.login == b.login);
}
