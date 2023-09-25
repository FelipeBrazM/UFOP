/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef MENUCHEFE_H
#define MENUCHEFE_H

#include "../Model/Supervisor.h"
#include "../Model/Vendedor.h"
#include "../Model/Chefe.h"
#include "limits"
#include "menus.h"


void cadastrarSupervisor(Chefe&);

Supervisor * selecionarSupervisor(Chefe&);

void cadastrarVendedor(Chefe&);

void cadastrarFuncionario(Chefe&);

bool compare(Funcionario*, Funcionario*);

void checarPontoFuncionarios(Chefe&);

void salariosFuncionarios(Chefe &);

void menuChefe(Chefe&);


#endif