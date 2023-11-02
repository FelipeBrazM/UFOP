#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class System{
protected: 
    double value;
    string name;

private:
	System& operator= (const System& s);

public:
    System();
    System(double value, string name);
    System(const System& sys);
    virtual ~System();

    void setvalue(double);
    double getvalue(void) const;

    void setName(string);
    string getName(void) const;

    virtual void saida(ostream&) const;
    friend ostream& operator << (ostream&, const System&); 
};

#endif //SYSTEM_H