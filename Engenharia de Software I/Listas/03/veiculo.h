// Sistema: Gerenciamento de Concessionaria de Automoveis - AutoMananger
// Interface: Administracao de Veiculos
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
//           - Classifica os veiculos em "biciclos" e "quadriciclos"
// Requisitos:
//           -
#if ! defined( VEICULO_H ) 
#define VEICULO_H
class  Veiculo{
      float orcamento;
      static unsigned int cont;
public:    
      Veiculo( float );
      ~Veiculo( void );
      void setOrcamento( float );
      float getOrcamento( void );
      static int getCont(void);
      virtual const char* const getClasse( void ) const = 0;
};
//-----------------------------------------------------------------------------
class Moto : public Veiculo {
protected:
      const char* const classe;
public:
       Moto( float );
       const char* const getClasse( void ) const;
       void setClasse( void ) const;
};
//-----------------------------------------------------------------------------
class Automovel : public Veiculo {
protected:
      const char* const classe;
public:
       Automovel( float );
       const char* const getClasse( void ) const;
};
//-----------------------------------------------------------------------------
class Carro : public Automovel{   
public:
       Carro( float);
};
//-----------------------------------------------------------------------------
class Caminhao : public Automovel{
public:
       Caminhao( float);
};

#endif
