/*
      Nome: Felipe Braz Marques 
      Matrícula: 22.1.4030
*/

#define EXERC1

#include <cstdlib>
#include <iostream>

using namespace std;
            
#if defined(EXERC1)
// QUEST�O 1: Critique o c�digo abaixo e aponte seus problemas com rela��o:
//          a) � flexibilidade da implementa��o: altera��es em pequenos trechos 
//             do c�digo n�o deveriam exigir recodifica��o de outras partes
//          b) � legibilidade do c�digo: lendo o c�digo � f�cil entrender os 
//             objetos e processos que ele representa. Qual � seu objetivo?
class Casa {
      float orc;
      int a;
public:
       Casa( float o ):orc(o){ cout << "Casa criada..." << endl; }
       void setOrc( float o ) { orc = o; }
       float getOrc( void ) { return orc; }
};

/*
      A variavel "a" nao entra no construtor, sem get nem set, e a variavel"orc" tem que ser obrigatoriamnte iniciada, sem a opção de uma associao depois.
      O codigo é facil de entender, porem nao mosta muito bem o objetivo, ele pode ser apenas uma casa,
      mas sua variaveis nao passam nenhuma informação, faltam coisa que uma casa teria.
*/

#else
// QUESTAO 2: Corrija os problemas identificado na quest�o 1.
class Casa {
      // Coloque suas corre��es aqui...
      float orcamento;
      int numero;
      char* logradouro;

public: 
      Casa(){};
      Casa(float orc, int num, char* log) : orcamento(orc), numero(num), logradouro(log){
            cout << "Casa criada..." << endl;
      }
      //get and set de cada uma das variaveis
};
// ...e aqui se necess�rio.
#endif

// QUESTAO 3: Explique o c�digo abaixo e cada uma das linhas de texto que 
// formam sua sa�da.
int main(int argc, char *argv[])
{
    Casa c1(7), *c2 = &c1, &c3 = c1;
    
    cout << "C1: " << c1.getOrc() << endl; //"C1: 7"
    c1.setOrc(3);
    cout << "C2: " << c2->getOrc() << ", "; //"C2: 3, C3: 3"
    cout << "C3: " << c3.getOrc() << endl; 
    cout << "C2: " << c2 << ", C3: " << &c3 << endl; //"C2: 3, C3: endereço de C3"

    system("PAUSE");
    return EXIT_SUCCESS;
}
// QUESTAO 4: Quantas vezes o construtor da classe foi invocado? Por que?
//Apenas uma vez, pois foi estanciado apenas uma casa.
