// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Interface: Administracao de Clientes
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
//
          
#if ! defined( CLIENTE_H ) 
#define CLIENTE_H

class Cliente {
      char *nome;
public:
	
      Cliente( char* );
      void setNome( char*  );
      char* getNome( void );
};
#endif
