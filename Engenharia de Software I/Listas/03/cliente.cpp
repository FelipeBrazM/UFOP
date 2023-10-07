// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Modulo: Administracao de Clientes
// Autor: Tiago Garcia de Senna Carneiro
// Ultima alteracao:15/12/2006
// Responsavel: Tiago G. S. Carneiro
//
// Descrição:  Mantém cadastro de clientes da concessionaria. Os clientes sao
// identificados pelo nome.
//             
// Serviços (API): 
//           - Cria novo cliente
//           - Remove cliente
//           - Edita cliente
// Requisitos:
//           -
#include "cliente.h"

#include <cstring>

using namespace std;
Cliente::Cliente(char *n) { nome = n; }
void Cliente::setNome( char* n  ){ nome = n; } 
char* Cliente::getNome( void ) { return nome; }

