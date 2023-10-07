// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Modulo: Administracao de Funcionarios
// Autor: Tiago Garcia de Senna Carneiro
// Ultima alteracao:15/12/2006
// Responsavel: Tiago G. S. Carneiro
//
// Descrição:  Mantém cadastro de funcionarios da concessionaria. Cada 
// funcionario recebe um salario e é identificado pelo nome. 
//             
// Serviços (API): 
//           - Cria novo funcionario
//           - Remove funcionario
//           - Edita funcionario
//           - Realiza o rejuste dos salarios dos funcionarios
// Requisitos:
//           -
#include "funcionario.h"

using namespace std;

#include <cstdlib>
#include <iostream>
#include <cstring>


Funcionario::Funcionario( void ){};
Funcionario::~Funcionario( void ){ delete [] nome; }
Funcionario::Funcionario( float s, String& n):salario(s), nome((char *)n){ };
Funcionario::Funcionario( Funcionario& f){
    delete [] nome;
    nome = new char[ strlen(f.nome) + 1 ];
    strcpy( nome, f.nome );
    salario = f.salario;
}
void Funcionario::setSalario( float s ) { salario = s; }
float Funcionario::getSalario( void ) { return salario; }
void Funcionario::reajustaSalario( void ) { salario *= 1.05; }
char* Funcionario::getNome( void ){ return nome; }
Funcionario& Funcionario::operator=(const Funcionario& f){
    
    if( &f == this ) { return *this;}
    
    salario = f.salario;
 
    delete [] nome;
    nome = new char[ strlen(f.nome) + 1 ];
    strcpy( nome, f.nome );
    return (*this);
}

//-----------------------------------------------------------------------------

Gerente::Gerente( void ){}
Gerente::Gerente(float s, String& n):Funcionario(s,n){}
void Gerente::reajustaSalario( void ) { salario *= 1.15; }

//-----------------------------------------------------------------------------

GerenteGeral::GerenteGeral( void ){}
GerenteGeral::GerenteGeral(float s, String& n):Gerente(s,n){}
void GerenteGeral::reajustaSalario( void ) { salario *= 1.2; }

//-----------------------------------------------------------------------------

Mecanico::Mecanico(float s, String& n):Funcionario(s,n){}
void Mecanico::reajustaSalario( void ) { salario *= 1.1; }
