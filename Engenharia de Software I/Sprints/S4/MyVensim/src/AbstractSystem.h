/* Felipe Braz Marques - 22.1.4030 */

#ifndef ABSTRACTSYSTEM_H
#define ABSTRACTSYSTEM_H

#include <stdlib.h>
#include <iostream> 
#include <vector>
#include <string>

using namespace std;

class AbstractSystem{
public:
    virtual ~AbstractSystem(){};

    virtual void setValue(double value) = 0;
    virtual double getValue(void) const = 0;

    virtual void setName(string name) = 0;
    virtual string getName(void) const = 0;

    virtual void saida(ostream& out) const = 0;
    friend ostream& operator << (ostream&, const AbstractSystem&); 
};

#endif //SYSTEM_H