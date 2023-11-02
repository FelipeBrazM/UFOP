#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "System.h"
#include "Flow.h"

using namespace std;

class Model {
protected:
	double time; 
	vector<System*> systens;
	vector<Flow*> flows;
	string name;

private:
	Model& operator= (const Model& m);

public:
	Model();
	Model(const string name = "", const double time = 0.0);
	Model(const Model& m);
	~Model();

	void add(System* const s);

	void add(Flow* const f);
	
	void setTime(const double time);
	double getTime();

	void setName(const string name);
	string getName();
	bool execute(double initialTime, double finalTime, double timeStep);

};

#endif //MODEL_H