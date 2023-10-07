// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Interface: Administracao de Funcionarios
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
#if ! defined( FUNCIONARIO_H ) 
#define FUNCIONARIO_H

typedef const char* String;
class Funcionario {
protected:
      float salario;
      char* nome;
public:
      Funcionario( void );
      Funcionario( float, String&);
      virtual ~Funcionario( void );
      void setSalario( float );
      float getSalario( void );
      virtual void reajustaSalario( void );
      char* getNome( void );
private:
      Funcionario( Funcionario& );
      Funcionario& operator=(const Funcionario&);
      
};

//-----------------------------------------------------------------------------

class Gerente : public  Funcionario {
public:
       Gerente( float, String&);
       virtual void reajustaSalario( void );
protected:
       Gerente( void );
};

//-----------------------------------------------------------------------------

class GerenteGeral : public Gerente {
public:
       GerenteGeral( float, String&);
       void reajustaSalario(void);
protected:
       GerenteGeral( void );
};

//-----------------------------------------------------------------------------

class Mecanico : public Funcionario {
public:
       Mecanico( float, String&);
       void reajustaSalario( void );
};

#endif
