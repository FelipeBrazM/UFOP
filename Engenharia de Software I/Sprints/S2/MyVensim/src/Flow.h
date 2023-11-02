#ifndef FLOW_H
#define FLOW_H

#include "System.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Flow{
protected:
    System *origin;
    System *destiny; 
    double value;
    string name;
	double (*function)(System* const o, System* const d);

private:
	Flow& operator= (const Flow& s);

public:
    Flow();
    Flow(System *origin , System *destiny , double (*function)(System *o, System *d), string name);
    Flow(const Flow&);
    virtual ~Flow();

    void setOrigin(System *origin );
    System* getOrigin(void) const;

    void setDestiny(System * destiny);
    System* getDestiny(void) const;

    void setValue(double value);
    double getValue(void) const;

    void setName(string);
    string getName(void) const;

    void setFunction(double (*function)(System *o, System *d));
    void execute();

    virtual void saida(ostream&) const;
    friend ostream& operator << (ostream&, const Flow&); 
};

#endif