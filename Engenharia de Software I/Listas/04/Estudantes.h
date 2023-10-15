#ifdef ESTUDANTE_H
#define ESTUDANTE_H

#include "string"
using namespace std;

class Estudante{
private:
    string nome;
    float nota;
public:
    Estudante(string = "", float = 0);
    virtual ~Estudante();
    
    string getNome() const;
    void setNome(string);

    float getNota() const;
    void setNota(float);
};

#endif /* ESTUDANTE_H */