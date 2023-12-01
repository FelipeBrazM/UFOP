#include "FlowImpl.h"
#include "System.h"

#include <string>
#include <iostream>

using namespace std;

FlowImpl::FlowImpl(const string name, System *systemInput, System *systemOutput, double tax) : name(name), systemInput(systemInput), systemOutput(systemOutput), tax(tax) {}
FlowImpl::FlowImpl() : name("NoName"), systemInput(NULL), systemOutput(NULL), tax(0.0) {}
FlowImpl::FlowImpl(const FlowImpl& f) {
    this->name = f.name;
    this->systemInput = f.systemInput;
    this->systemOutput = f.systemOutput;
    this->tax = f.tax;
}

string FlowImpl::getName() const
{
    return this->name;
}

void FlowImpl::setName(const string name)
{
    this->name = name;
}

System *FlowImpl::getSystemInput() const
{
    return this->systemInput;
}

void FlowImpl::setSystemInput(System* const systemInput)
{
    this->systemInput = systemInput;
}

System *FlowImpl::getSystemOutput() const
{
    return this->systemOutput;
}

void FlowImpl::setSystemOutput(System* const systemOutput)
{
    this->systemOutput = systemOutput;
}

double FlowImpl::getTax() const
{
    return this->tax;
}

void FlowImpl::setTax(const double tax)
{
    this->tax = tax;
}

FlowImpl& FlowImpl::operator= (const FlowImpl& f) {
    if (this == &f)
        return *this;

    this->name = f.name;
    this->systemInput = f.systemInput;
    this->systemOutput = f.systemOutput;
    this->tax = f.tax;

    return *this;
}

FlowImpl::~FlowImpl() {}


