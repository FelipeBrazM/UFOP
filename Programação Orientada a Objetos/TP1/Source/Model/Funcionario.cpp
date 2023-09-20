/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "Funcionario.h"

Funcionario::Funcionario(string nome, Cadastro* cadastro, double salarioHora):Pessoa(nome, cadastro){
    this->setSalarioHora(salarioHora);
    this->minutosPendentes = CARGA_HORARIA_MENSAL;
}

Funcionario :: ~Funcionario(){
    for(auto it : pontos)
        delete it;
}

double Funcionario :: getSalarioHora() const {
    return salarioHora;
}

void Funcionario :: setSalarioHora(double salarioHora) {
    if(salarioHora < 0)
        throw invalid_argument("O valor não pode ser menor que zero.\n");

    this->salarioHora = salarioHora;
}

int Funcionario :: getMinutosPendentes() const{
    return minutosPendentes;
}

void Funcionario :: setMinutosPendentes(int minPendentes){
    this->minutosPendentes = minPendentes;
}

void Funcionario :: registrarPonto(Ponto* ponto){
    //Caso em que é o inicio de um novo mes
    if(((pontos.size()) % 28) == 0){
        minutosPendentes = CARGA_HORARIA_MENSAL;
    }

    int minutosTrabalhados;

    int minutosEntrada = (ponto->getHorarioEntrada()->getHora() * 60) + ponto->getHorarioEntrada()->getMinuto();
    int minutosSaida = (ponto->getHorarioSaida()->getHora() * 60) + ponto->getHorarioSaida()->getMinuto();
    
    minutosTrabalhados = minutosSaida - minutosEntrada;

    if(minutosTrabalhados <= 0) minutosTrabalhados += 1440;

    minutosPendentes -= minutosTrabalhados;

    this->pontos.push_back(ponto);
}

vector<Ponto*> Funcionario :: getPontos() const {
    return pontos;
}

void Funcionario :: serialize(ostream& out) const{
    Pessoa::serialize(out);

    out << "\nSalário por Hora: R$" << salarioHora << endl;
}