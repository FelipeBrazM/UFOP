/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "Ponto.h"

Ponto::Ponto(Hora * horarioEntrada, Hora * horarioSaida, string data){
    this->horarioEntrada = horarioEntrada;
    this->horarioSaida = horarioSaida;
    this->data = data;
}

Ponto :: ~Ponto(){
    delete horarioEntrada;
    delete horarioSaida;
}

Hora* Ponto :: getHorarioEntrada() const{
    return this->horarioEntrada;
}
void Ponto :: setHorarioEntrada(Hora *horarioEntrada){
    this->horarioEntrada = horarioEntrada;
}

Hora* Ponto :: getHorarioSaida() const{
    return this->horarioSaida;
}
void Ponto :: setHorarioSaida(Hora * horarioSaida){
    this->horarioSaida = horarioSaida;
}

string Ponto :: getData() const{
    return this->data;
}
void Ponto :: setData(string data){
    this->data = data;
}

void Ponto :: serialize(ostream &out) const{
    out << "Horário entrada: " << setfill('0') << setw(2) << horarioEntrada->getHora() 
                        << ":" << setfill('0') << setw(2) << horarioEntrada->getMinuto() 
                        << endl;

    out << "Horário saída: " << setfill('0') << setw(2) << horarioSaida->getHora() 
                        << ":" << setfill('0') << setw(2) << horarioSaida->getMinuto() 
                        << endl;
                        
    out << "Dia: " << getData() << endl;
}

ostream & operator << (ostream & out, const Ponto & h){
    h.serialize(out);
    return out;
}

