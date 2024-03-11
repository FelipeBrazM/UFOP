/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "Hora.h"

Hora::Hora(int hora, int minuto){
    this->setHora(hora);
    this->setMinuto(minuto);
}

Hora::~Hora(){}

int Hora :: getHora() const{
    return this->hora;
}
void Hora :: setHora(int hora){
    if(hora < 0 || hora > 23)
        throw invalid_argument("A hora deve estar entre 0 e 23.\n");

    this->hora = hora;
}

int Hora :: getMinuto() const{
    return this->minuto;
}
void Hora :: setMinuto(int minuto){
    if(minuto < 0 || minuto > 59)
        throw invalid_argument("O minuto deve estar entre 0 e 59.\n");

    this->minuto = minuto;
}