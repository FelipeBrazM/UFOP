#include "Disciplina.h"

using namespace std;

Disciplina :: Disciplina(int sala, int andar): sala(sala), andar(andar){}

Disciplina :: ~Disciplina(){}

int Disciplina :: getSala(){
    return sala;
}

int Disciplina :: getAndar(){
    return andar;
}

void Disciplina :: setSala(int sala) {
    this->sala = sala;
}

void Disciplina :: setAndar(int andar) {
    this->andar = andar;
}
