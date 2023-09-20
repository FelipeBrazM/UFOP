/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef MENUFUNCIONARIO_H
#define MENUFUNCIONARIO_H

#include "menus.h"
#include "regex"

void menuFuncionario(Funcionario*);

void opcoesSupervisor(Supervisor*);

void opcoesVendedor(Vendedor*);

bool validaData(string&);

void lerHora(Hora*);

void lerMinuto(Hora*);

void cadastrarPonto(Ponto*);

void cadastrarVendaUnica(Venda*);


#endif