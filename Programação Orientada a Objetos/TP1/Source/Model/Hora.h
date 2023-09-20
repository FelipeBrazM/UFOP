/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class Hora{
    int hora;
    int minuto;

public:
    Hora(int = 0, int = 0);
    virtual ~Hora();

    int getHora()const;
    void setHora(int) ;

    int getMinuto()const;
    void setMinuto(int);
};

#endif