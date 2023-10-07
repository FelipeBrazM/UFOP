// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Modulo: Administracao de Veiculos
// Autor: Tiago Garcia de Senna Carneiro
// Ultima alteracao:15/12/2006
// Responsavel: Tiago G. S. Carneiro
//
// Descrição:  Mantém cadastro de veiculos da concessionaria. Cada veículo 
// possui um orçamento a ele associado. 
//             
// Serviços (API): 
//           - Cria novo veiculo
//           - Remove veiculo
//           - Edita veiculo
//           - Informa o numero de objetos veiculos carregados na memoria 
// Requisitos:
//           -
#include "veiculo.h" 
#include <cstdlib>
#include <cstring>

Veiculo::Veiculo( float orc ):orcamento(orc){  cont++; }
Veiculo::~Veiculo( void ){ cont--; }
void Veiculo::setOrcamento( float o ) { orcamento = o; }
float Veiculo::getOrcamento( void ) { return orcamento; }
int Veiculo::getCont( void ){ return cont; }

//-----------------------------------------------------------------------------

Moto::Moto( float orc ):Veiculo( orc ), classe("Biciclo") {}
const char* const Moto::getClasse( void ) const { return classe; };

//-----------------------------------------------------------------------------

Automovel::Automovel( float orc ):Veiculo(orc), classe("Quadriciclo"){ }
const char* const Automovel::getClasse( void ) const { return classe; };

//-----------------------------------------------------------------------------

Carro::Carro( float orc ):Automovel(orc) { }

//-----------------------------------------------------------------------------

Caminhao::Caminhao( float orc ):Automovel(orc){  }
