/* Felipe Braz Marques - 22.1.4030 */

#ifndef ABSTRACTFLOW_H 
#define ABSTRACTFLOW_H

#include "AbstractSystem.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AbstractFlow{
public:
    virtual ~AbstractFlow(){};

    virtual void setOrigin(AbstractSystem *origin ) = 0;
    virtual AbstractSystem* getOrigin() const = 0;

    virtual void setDestiny(AbstractSystem *destiny ) = 0;
    virtual AbstractSystem* getDestiny() const = 0;

    virtual void setValue(double value) = 0;
    virtual double getValue() const = 0;

    virtual void setName(string name) = 0;
    virtual string getName() const = 0;

    virtual void setFunction(double (*function)(AbstractSystem *o, AbstractSystem *d)) = 0;
    virtual void execute() = 0;

    virtual void output(ostream& out) const = 0;
};

#endif