#include "Estudante.h"
#include "string"

using namespace std;

Estudante::Estudante(string nome, float nota): nome(nome),nota(nota){}

Estudante::~Estudante(){}

string Estudante::getNome(){
    return nome;
}

void Estudante::setNome(string nome){
    this->nome = nome;
}

float Estudante::getNota(){
    return nota;
}

void Estudante::setNota(float nota){
    this->nota = nota;
}
