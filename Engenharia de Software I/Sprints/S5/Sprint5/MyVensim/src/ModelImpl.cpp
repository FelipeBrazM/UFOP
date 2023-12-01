#include "ModelImpl.h"


using namespace std;

vector<Model*> ModelImpl::models;

ModelImpl::ModelImpl() : name("NoName"), timeInitial(0.0), timeFinal(0.0){};
ModelImpl::ModelImpl(const string name, const double timeInitial, const double timeFinal) : name(name), timeInitial(timeInitial), timeFinal(timeFinal) {};
ModelImpl::~ModelImpl() {
    for(auto flow : flows){
        delete flow;
    }

    for(auto system : systens){
        delete system;
    }

    for(auto model : models){
        if(model == this)
            removal(model);
    }
};

ModelImpl::ModelImpl(const ModelImpl& copy) {
    this->name = copy.name;
    this->timeInitial = copy.timeInitial;
    this->timeFinal = copy.timeFinal;

    for(std::vector<Flow*>::size_type i = 0; i < copy.flows.size(); i++){
        flows.push_back(copy.flows[i]);
    }
    for(std::vector<System*>::size_type i = 0; i < copy.systens.size(); i++){
        systens.push_back(copy.systens[i]);
    }

}

string ModelImpl::getName() const
{
    return this->name;
}

void ModelImpl::setName(const string name)
{
    this->name = name;
}

double ModelImpl::getTimeInitial() const
{
    return this->timeInitial;
}


void ModelImpl::setTimeInitial(const double timeInitial)
{
    this->timeInitial = timeInitial;
}


double ModelImpl::getTimeFinal() const
{
    return this->timeFinal;
}


void ModelImpl::setTimeFinal(const double timeFinal)
{
    this->timeFinal = timeFinal;
}

void ModelImpl::setTime(const double time)
{
    this->time = time;
}

double ModelImpl::getTime() const
{
    return this->time;
}

void ModelImpl::add(System* system){
    bool found = find(this->systens.begin(), this->systens.end(), system) != this->systens.end();
    if(!found)
        systens.push_back(system);
}

void ModelImpl::add(Flow* flow){
    bool found = find(this->flows.begin(), this->flows.end(), flow) != this->flows.end();
    if(!found)
        flows.push_back(flow);
}

void ModelImpl::add(Model* model){
    bool found = find(models.begin(), models.end(), model) != models.end();
    if(!found)
        models.push_back(model);
}

void ModelImpl::removal(System* const sys) {
    this->systens.erase(remove(this->systens.begin(), this->systens.end(), sys), this->systens.end());
}

void ModelImpl::removal(Flow* const flow) {
    this->flows.erase(remove(this->flows.begin(), this->flows.end(), flow), this->flows.end());
}

void ModelImpl::removal(Model* const model){
    models.erase(remove(models.begin(), models.end(), model), models.end());
}

void Model::removal(Model* const model){
    return ModelImpl::removal(model);
}

ModelImpl& ModelImpl::operator= (const ModelImpl& m) {
    if (this == &m)
        return *this;

    this->name = m.name;
    this->time = m.time;

    this->systens.clear();
    this->flows.clear();

    for(std::vector<Flow*>::size_type i = 0; i < m.flows.size(); i++){
        flows.push_back(m.flows[i]);
    }
    for(std::vector<System*>::size_type i = 0; i < m.systens.size(); i++){
        systens.push_back(m.systens[i]);
    }

    return *this;
}

void ModelImpl::execute(double timeInitial, double timeFinal){
    System *Begin, *End;
    for(time= timeInitial; time< timeFinal; time++) {
        for(auto flow : this->flows){
            flow->setTax(flow->execute());
        }

        for(auto flow : this->flows){
            Begin = flow->getSystemInput();
            Begin->setValue(Begin->getValue() - flow->getTax());

            End = flow->getSystemOutput();
            End->setValue(End->getValue() + flow->getTax());

        }
    }

}

vector<System*>::iterator ModelImpl::systemBegin(void){
    return this->systens.begin();
}

vector<Flow*>::iterator ModelImpl::flowBegin(void){
    return this->flows.begin();
}

vector<System*>::iterator ModelImpl::systemEnd(void) {
    return this->systens.end();
}

vector<Flow*>::iterator ModelImpl::flowEnd(void) {
    return this->flows.end();
}

vector<Model*>::iterator ModelImpl::modelBegin(void) {
    return this->models.begin();
}

vector<Model*>::iterator ModelImpl::modelEnd(void) {
    return this->models.end();
}

System* ModelImpl::createSystem(const string name, const double value){
    System* system = new SystemImpl(name, value);
    add(system);
    return system;
}

Model* ModelImpl::createModel(const string name, const double timeInitial, const double timeFinal){
    Model* model = new ModelImpl(name, timeInitial,timeFinal);
    add(model);
    return model;
}

Model* Model::createModel(const string name,const double timeInitial, const double timeFinal){
    return ModelImpl::createModel(name, timeInitial, timeFinal);
}

void ModelImpl::deleteSystem(System* system){
    removal(system);

    for(auto flow : flows){
        if(flow->getSystemInput() == system)
            flow->setSystemInput(NULL);
        if(flow->getSystemOutput() == system)
            flow->setSystemOutput(NULL);
    }

    delete system;
}
void ModelImpl::deleteFlow(Flow* flow){
    removal(flow);
    delete flow;
}
// void ModelImpl::deleteModel(Model* model){
//     removal(model);
//     delete model;
// }

// void Model::deleteModel(Model* model){
//     return ModelImpl::deleteModel(model);
// }