/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "Vendedor.h"

Vendedor::Vendedor(string nome, Cadastro* cadastro, double salarioHora):Funcionario(nome, cadastro, salarioHora){}

Vendedor::~Vendedor(){
    for(auto venda : vendas){
        delete venda;
    }
}

void Vendedor :: cadastrarVenda(Venda* venda){
    this->vendas.push_back(venda);
}

void Vendedor :: listarVendas(){
    for(auto it : vendas){
        cout << *it;
    }
}

double Vendedor :: calculaVendas(){
    double valorVendas = 0.0;

    for(Venda* v : vendas){
        valorVendas += (v->getValor() * v->getQuantidade());
    }

    return valorVendas;
}

double Vendedor :: calcularBonificacao(){
    return 0.1 * calculaVendas();
}

void Vendedor :: serialize (ostream &out){
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<< (ostream& out, Vendedor& v){
    v.serialize(out);

    return out;
}

vector<Venda*> Vendedor :: getVendas(){
    return this->vendas;
}

double Vendedor :: calcularSalarioFinal(){
    int minutosPendentes = getMinutosPendentes();

    double salarioFinal = 0.0;

    if(minutosPendentes < 0){
        //horas extras
        int horasExtras = abs(minutosPendentes)/60;
        int minutosExtras = abs(minutosPendentes) - (horasExtras * 60);

        salarioFinal = (CARGA_HORARIA_MENSAL/60) * getSalarioHora();
        salarioFinal += horasExtras * getSalarioHora() * 2;
        salarioFinal += minutosExtras * (getSalarioHora()/60) * 2;
    }
    else if(minutosPendentes == 0)
        //0 horas extras e 0 horas pendentes
        salarioFinal = (CARGA_HORARIA_MENSAL/60) * getSalarioHora();
        
    else {
        //horas pendentes
        int minutosTrabalhados = CARGA_HORARIA_MENSAL - minutosPendentes;
        int horasTrabalhadas = minutosTrabalhados / 60;
        minutosTrabalhados -= horasTrabalhadas*60;
        
        salarioFinal = horasTrabalhadas * getSalarioHora();
        salarioFinal += minutosTrabalhados * (getSalarioHora()/60);
    }

    return salarioFinal;
}