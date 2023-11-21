/* Felipe Braz Marques - 22.1.4030 */

#ifndef ABSTRACT_MODEL_H
#define ABSTRACT_MODEL_H

#include <vector> 
#include <string>
#include "AbstractSystem.h"
#include "AbstractFlow.h"

using namespace std;

class AbstractModel {
public:
    virtual ~AbstractModel(){};

    virtual void add(AbstractSystem* const s) = 0;
	virtual void add(AbstractFlow* const f) = 0;

	virtual int getSystensSize() = 0;
	virtual int getFlowsSize() = 0;

	virtual void setTime(const double time) = 0;
	virtual double getTime() = 0;

	virtual void setName(const string name) = 0;
	virtual string getName() = 0;
	
	virtual bool execute(double initialTime, double finalTime, double timeStep) = 0;

};

#endif