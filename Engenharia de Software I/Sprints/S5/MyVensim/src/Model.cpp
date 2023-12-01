// Felipe Braz Marques - 22.1.4030

#include "Model.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "System.h"
#include "Flow.h"

vector<AbstractModel*> Model::models;

Model::Model(){
	name = "";
	time = 0.0;
}

Model::Model(const string name, const double time) : name(name), time(time) {}

Model::~Model() {
	for(auto sys : systens){
		delete sys;
	}
	this->systens.clear();

	for(auto flw : flows){
		delete flw;
	}
	this->flows.clear();

	models.erase(std::remove(models.begin(), models.end(), this), models.end());
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

void Model::add(AbstractSystem* const s){
    this->systens.push_back(s);
}

void Model::add(AbstractFlow* const f){
    this->flows.push_back(f);
}

int Model::getSystensSize(){
	return this->systens.size();
}
int Model::getFlowsSize(){
	return this->flows.size();
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

AbstractSystem* Model::createSystem(double value, string name){
	AbstractSystem *sys = new System(value, name);
	add(sys);
	return sys;
}

AbstractFlow* Model::createFlow(AbstractSystem *origin , AbstractSystem *destiny , double (*function)(AbstractSystem *o, AbstractSystem *d), string name){
	AbstractFlow *flw = new Flow(origin, destiny, function, name);
	add(flw);
	return flw;
}

AbstractModel* AbstractModel::createModel(string name, double time){
	return Model::createModel(name, time);
}

AbstractModel* Model::createModel(string name, double time){
	AbstractModel *model = new Model(name, time);
	models.push_back(model);
	return model;
}

bool Model::execute(double initialTime, double finalTime, double timeStep){

	setTime(initialTime);

    for (double tempo = initialTime; tempo < finalTime; tempo += timeStep) {

        for (auto i : flows) {
			i->execute();
		}

        for (auto i : flows) {
			AbstractSystem *origin = i->getOrigin();
			if (origin != NULL)
				origin->setValue(origin->getValue() - i->getValue());

			AbstractSystem *destiny = i->getDestiny();
			if (destiny != NULL)
				destiny->setValue(destiny->getValue() + i->getValue());
		}

		setTime(getTime() + timeStep);
    }

    for (auto i : systens) {
		std::cout << *i;
	}

	return true;
}