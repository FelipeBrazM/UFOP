/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "Supervisor.h"

Supervisor :: Supervisor(string nome, Cadastro * cadastro, double salarioHora):Funcionario(nome, cadastro, salarioHora){
    vendedores.resize(0);
}

Supervisor :: ~Supervisor(){}

void Supervisor :: cadastrarVendedor(Vendedor* vendedor){
    vendedores.push_back(vendedor);
}

void Supervisor ::  listarVendedores(){
    for(auto it : vendedores){
        cout << it;
    }
}

void Supervisor :: listarVendas(){
    if(vendedores.size() == 0) {
        cout << "O supervisor não possui nenhum vendedor" << endl;
        return;
    }

    for(auto vendedor : vendedores){
        cout << "-------------------" << endl;
        cout << vendedor->getNome() << endl;
        
        if((vendedor->getVendas()).size() != 0)
            vendedor->listarVendas();
    }
    cout << "-------------------" << endl;
}

double Supervisor :: calcularSalarioFinal(){
    int minutosPendentes = getMinutosPendentes();

    double salarioFinal = 0.0;

    if(minutosPendentes < 0){
        //horas extras
        int horasExtras = abs(minutosPendentes)/60;
        int minutosExtras = abs(minutosPendentes) - (horasExtras * 60);

        salarioFinal = (CARGA_HORARIA_MENSAL/60) * getSalarioHora();
        salarioFinal += horasExtras * getSalarioHora() * 2.5;
        salarioFinal += minutosExtras * (getSalarioHora()/60) * 2.5;
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

double Supervisor :: calcularBonificacao(){
    double bonificacao = 0.0;

    for(Vendedor * vendedor : vendedores){
        bonificacao += vendedor->calculaVendas();
    }

    bonificacao *= 0.01;

    return bonificacao;
}

void Supervisor :: serialize(ostream& out) {
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<<(ostream& out, Supervisor& s){
    s.serialize(out);

    return out;
}