/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#ifndef PONTO_H
#define PONTO_H

#include "Hora.h"
#include <string>
#include <iomanip>

using namespace std;

class Ponto{
    Hora * horarioEntrada;
    Hora * horarioSaida;
    string data;

public:
    Ponto(Hora * = new Hora(), Hora * = new Hora(), string = "");
    virtual ~Ponto();

    Hora * getHorarioEntrada() const;
    void setHorarioEntrada(Hora *);

    Hora * getHorarioSaida() const;
    void setHorarioSaida(Hora *);

    string getData() const;
    void setData(string);

    void serialize(ostream &out) const;
    friend ostream & operator << (ostream & out, const Ponto &h);
};

#endif