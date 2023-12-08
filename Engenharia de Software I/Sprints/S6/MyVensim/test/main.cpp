#include <cstdlib>
#include <iostream>
#include <cstdlib>

#define DEBUGING
#ifdef DEBUGING
     int numHandleCreated = 0;
	 int numHandleDeleted = 0;
	 int numBodyCreated = 0;
	 int numBodyDeleted = 0;
#endif

#include "../src/SystemImpl.h"
#include "../src/FlowImpl.h"
#include "../src/Model.h"

using namespace std;

class FlowLog:public FlowHandlePointer{
   public:
    FlowLog(const string name = "ExponentialFlow", System *source = NULL, System *target = NULL) : FlowHandlePointer(name, source, target,0.0) {}

    double execute(){
          double q = pImpl_->getSystemOutput()->getValue();
          return q*(0.3*(1-(q/70)));;
    }    
};

class FlowExp:public FlowHandlePointer{
  public:
   FlowExp(const string name = "ExponentialFlow", System *source = NULL, System *target = NULL) : FlowHandlePointer(name, source, target,0.0) {}

   double execute(){
         return pImpl_->getSystemOutput()->getValue()*0.3;
   }      
};

int main(int argc, char *argv[])
{
    // Apenas a implementacao da classe "Flow" precisa ser conhecida na
    // fase de "cria��o de objetos", pois o usu�rio precisa implementar 
    // v�rios tipos de fluxo. Ent�o, o m�dulo de cria��o de objetos precisa
    // conhecer os fluxos implementados pelo usu�rio.No entanto, nenhuma outra 
    // implementa��o precisa ser conhecida por qq outro m�dulo.
    
    // Cria modelo
    Model* m = Model::createModel("Modelo de Pop", 0.0, 100.0);     
    Flow* f1 = m->createFlow<FlowLog>("nascimento");    

    // USANDO REFERENCIAS PARA INTERFACE (CLASSE ABSTRATA)
    //System& s1 = m.createSystem("populacao",10.0);
    //System& s2 = m.createSystem("Teste", 7.90)   ;
    //cout << "s1: " << s1.getName() << ", s2: " <<  s2.getName() << endl;
    //s1 = s2;  // nao funciona pq s1 � uma referencia, portanto nao pode ser redefinida
    //cout << "s1: " << s1.getName() << ", s2: " <<  s2.getName() << endl;    
    
    // USANDO PONTEIROS PARA INTERFACE (CLASSE ABSTRATA)
    System* s1 = m->createSystem("populacao", 10.0);
    System* s2 = m->createSystem("Teste", 7.90);
    cout << "s1: " << s1->getName() << ", s2: " <<  s2->getName() << endl;
    //s1 = s2;
    *s1 = *s2;
    cout << "s1: " << s1->getName() << ", s2: " <<  s2->getName() << endl;    
    cout << "s1: " << s1 << ", s2: " <<  s2 << endl;    
    
    
    // Fa�a o teste COM e SEM as chaves abaixo
{
    // USANDO OBJETOS HANDLES (DELEGA��O)
    SystemHandlePointer s3("tiago", 7), s4("antonio", 8);
    cout << "s3: " << s3.getName() << ", s4: " <<  s4.getName() << endl;
    s3 = s4;  // comente esta linha e veja que o resultado muda
    cout << "s3: " << s3.getName() << ", s4: " <<  s4.getName() << endl;        
	s3 = s3;
	cout << "s3: " << s3.getName() << ", s4: " <<  s4.getName() << endl;        
}   
    // Monta Modelo
    //m.setTarget(f1, s1);
    // m->setTarget(f1, *s1);
    f1->setSystemOutput(s1);
    
    // executa o modelo
    m->execute(0,30);
    
    // imprime relatorio
    //cout << s1.getValue() << endl;
    cout << s1->getValue() << endl;

    delete m;

    cout << "Created handles: "  << numHandleCreated << endl;
    cout << "Deleted handles: "  << numHandleDeleted << endl;    
    cout << "Created bodies: "  << numBodyCreated << endl;
    cout << "Deleted bodies: "  << numBodyDeleted << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}