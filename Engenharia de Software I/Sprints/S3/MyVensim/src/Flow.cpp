/*  
    Felipe Braz Marques 22.1.4030
*/
#include "Flow.h"
#include "System.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

Flow::Flow() : origin(NULL), destiny(NULL), function(NULL), name(""){}

Flow::Flow(System *origin = NULL, System *destiny = NULL, double (*function)(System *o, System *d) = NULL, string name = "") : origin(origin), destiny(destiny), function(function), name(name){}

Flow::Flow(const Flow& f){
    this->origin = f.origin;
    this->destiny = f.destiny;
    this->value = f.value;
    this->function = f.function;
    this->name = f.name;
}

Flow::~Flow(){}

Flow& Flow::operator= (const Flow& f) {
	if (this == &f)
		return *this;

	this->origin = f.origin;
	this->destiny = f.destiny;
	this->value= f.value;
	this->function = f.function;
    this->name = f.name;

	return *this;
}

void Flow::setOrigin(System *origin){
    this->origin = origin;
}
System* Flow::getOrigin(void) const{
    return this->origin;
}

void Flow::setDestiny(System *destiny){
    this->destiny = destiny;
}
System* Flow::getDestiny(void) const{
    return this->destiny;
}

void Flow::setValue(double value){
    this->value = value;
}
double Flow::getValue(void) const{
    return this->value;
}

void Flow::setName(string name){
    this->name = name;
}
string Flow::getName(void) const{
    return this->name;
}

void Flow::setFunction(double (*function)(System *o, System *d)){
    this->function = function;
}
void Flow::execute(){
    this->setValue(this->function(this->origin, this->destiny));
}

void Flow::output(ostream& out) const{
    out << "Origem: " << getOrigin() << endl
        << "Destino :" << getDestiny() << endl 
        << "Value :" << getValue() << endl
        << "Name :" << getName() << endl;
}
ostream& operator << (ostream& out, const Flow& flow){
    flow.output(out);
    return out;
} 