// Felipe Braz Marques - 22.1.4030

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "AbstractSystem.h"
#include "AbstractFlow.h"
#include "AbstractModel.h"

using namespace std;

/**
 * @brief Model class that stores the systems, flows and variables
 * 
 */
class Model: public AbstractModel{
protected:
	string name;/**< Model name*/
	double time;/**< Model time*/
	vector<AbstractSystem*> systens;/**< Systens contained in the model*/
	vector<AbstractFlow*> flows;/**< Flows contained in the model*/
	static vector<AbstractModel*> models;
	
	/**
	 * @brief Add System to the model
	 * 
	 * @param s system to be added
	 */
	void add(AbstractSystem* const s);

	/**
	 * @brief Add Flow to the model
	 * 
	 * @param f flow to be added
	 */
	void add(AbstractFlow* const f);

private:
	/**
	 * @brief Operator = overload
	 * 
	 * @param m Model to be copied
	 * @return Model& 
	 */
	Model& operator= (const Model& m);

public:
	/**
	 * @brief Construct a new Model object
	 * 
	 */
	Model();
	/**
	 * @brief Construct a new Model object
	 * 
	 * @param name model name
	 * @param time model time
	 */
	Model(const string name, const double time = 0.0);
	/**
	 * @brief Construct a new Model object
	 * 
	 * @param m model to be copied
	 */
	Model(const Model& m);
	/**
	 * @brief Destroy the Model object
	 * 
	 */
	~Model();

	/**
	 * @brief Get the Systens Size object
	 * 
	 * @return int size of System vector
	 */
	int getSystensSize();
	/**
	 * @brief Get the Flows Size object
	 * 
	 * @return int size of Flow vector 
	 */
	int getFlowsSize();
	
	/**
	 * @brief Set the Time object
	 * 
	 * @param time 
	 */
	void setTime(const double time);
	/**
	 * @brief Get the Time object
	 * 
	 * @return double 
	 */
	double getTime();

	/**
	 * @brief Set the Name object
	 * 
	 * @param name 
	 */
	void setName(const string name);
	/**
	 * @brief Get the Name object
	 * 
	 * @return string 
	 */
	string getName();
	
	/**
	 * @brief Create a System object
	 * 
	 * @param value initial value
     * @param name system name 
	 * @return AbstractSystem*
	 */
	AbstractSystem* createSystem(double value = 0.0, string name = "");

	/**
	 * @brief Create a Flow object
	 * 
	 * @param origin source AbstractSystem
     * @param destiny target AbstractSystem
     * @param function function that governs the flow
     * @param name flow name 
	 * @return AbstractFlow* 
	 */
	AbstractFlow* createFlow(AbstractSystem *origin , AbstractSystem *destiny , double (*function)(AbstractSystem *o, AbstractSystem *d), string name);

	/**
	 * @brief Create a Model object
	 * 
	 * @param name model name
	 * @param time model time 
	 * @return AbstractModel*
	 */
	static AbstractModel* createModel(string name = "", double time = 0.0);

	/**
	 * @brief function that runs the model
	 * 
	 * @param initialTime start time
	 * @param finalTime maximum time
	 * @param timeStep step of time
	 * @return true 
	 * @return false 
	 */
	bool execute(double initialTime, double finalTime, double timeStep);

};

#endif //MODEL_H