#include "SystemImpl.h"

using namespace std;

SystemImpl::SystemImpl(string name, double value) : name(name), value(value) {}
SystemImpl::SystemImpl() : name("NoName"), value(0.0) {}
SystemImpl::SystemImpl(const SystemImpl& copy){
    this->name = copy.name;
    this->value = copy.value;
}

SystemImpl::~SystemImpl(){}

SystemImpl& SystemImpl::operator= (const SystemImpl& s) {
    if (this == &s)
        return *this;

    this->name = s.name;
    this->value = s.value;

    return *this;
}

string SystemImpl::getName() const
{
    return this->name;
}

void SystemImpl::setName(const string name)
{
    this->name = name;
}

double SystemImpl::getValue() const
{
    return this->value;
}

void SystemImpl::setValue(const double value)
{
    this->value = value;
}

// ostream& operator<<(ostream& os, const SystemImpl& s) {
//     os << "\n\tNome: " << s.name << "\n\tValor: " << s.value << endl;
//     return os;
// }