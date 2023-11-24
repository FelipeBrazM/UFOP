#include "System.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

System::System(void){
    this->name = "";
    this->value = 0.0;
}

System::System(double value, string name) : value(value), name(name){}

System::System(const System& sys){
    this->value = sys.value;
    this->name = sys.name;
}

System::~System(){}

System& System::operator= (const System& s){
    if (this == &s)
		return *this;

	this->value = s.value;
    this->name = s.name;
	
	return *this;
}

void System::setValue(double value){
    this->value = value;
}
double System::getValue(void) const{
    return this->value;
}

void System::setName(string name){
    this->name = name;
}
string System::getName(void) const{
    return this->name;
}

void System::saida(ostream& out) const{
    out << "Name: " << getName() << endl
        << "Value: " << getValue() << endl;
}
ostream& operator << (ostream& out, const AbstractSystem& system){
    system.saida(out);
    return out;
}

//97548862