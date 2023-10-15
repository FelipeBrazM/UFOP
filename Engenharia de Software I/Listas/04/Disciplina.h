#ifdef DISCIPLINA_H
#define DISCIPLINA_H

using namespace std;

class Disciplina{
private: 
    int andar, sala;
public:
    Disciplina(int=0, int=0);
    virtual ~Disciplina();

    int getSala() const;
    void setSala(int);

    int getAndar() const;
    void setAndar(int);
};

#endif /* DISCIPLINA_H */