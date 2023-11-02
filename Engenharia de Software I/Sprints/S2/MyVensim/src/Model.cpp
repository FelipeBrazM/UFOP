#include "Model.h"
#include "System.h"
#include "Flow.h"

#include <stdlib.h> 
#include <iostream>
#include <string>
#include <vector>

Model::Model(): name(""), time(0){}

Model::Model(const string name, const double time) : name(name), time(time) {}

Model:: ~Model() {
	this->systens.clear();
	this->flows.clear();
}

Model::Model(const Model& m) {
	this->name = m.name;
	this->time = m.time;
	this->systens = m.systens;
	this->flows = m.flows;
}

Model& Model::operator= (const Model& m) {
	if (this == &m)
		return *this;

	this->name = m.name;
	this->time = m.time;
	this->systens = m.systens;
	this->flows = m.flows;

	return *this;
}

void Model::add(System* const s){
    this->systens.push_back(s);
}
void Model::add(Flow* const f){
    this->flows.push_back(f);
}

void Model::setTime(const double time) {
	this->time = time;
}
double Model::getTime() {
	return this->time;
}

void Model::setName(const string name) {
	this->name = name;
}
string Model::getName() {
	return this->name;
}

bool Model::execute(double initialTime, double finalTime, double timeStep){

    for (double tempo = initialTime; tempo < finalTime; tempo += timeStep) {

        for (auto i : flows) {
			i->execute();
		}

        for (auto i : flows) {
			System *origin = i->getOrigin();
			if (origin != NULL)
				origin->setvalue(origin->getvalue() - i->getValue());

			System *destiny = i->getDestiny();
			if (destiny != NULL)
				destiny->setvalue(destiny->getvalue() + i->getValue());
		}
    }

    for (auto i : systens) {
		std::cout << *i;
	}

	return true;
}