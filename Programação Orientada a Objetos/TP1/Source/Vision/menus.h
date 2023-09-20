/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef MENUS_H
#define MENUS_H

#include "../Model/Supervisor.h"
#include "../Model/Vendedor.h"
#include "../Model/Chefe.h"
#include "limits"
#include <algorithm>

void selecaoMenu(int&, int, int);

void telaInicial(int&);

bool validacaoLoginFuncionario(Cadastro, vector<Funcionario*>, Funcionario**);

bool validacaoLoginChefe(Cadastro, const Chefe&);

bool telaLoginUsuario(const int&, const Chefe&, Funcionario**);

void escolhaDeLogin(int&);

#endif