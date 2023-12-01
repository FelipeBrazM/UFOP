// Felipe Braz Marques - 22.1.4030

#ifndef ABSTRACT_MODEL_H
#define ABSTRACT_MODEL_H

#include <vector>
#include <string>
#include "AbstractSystem.h"
#include "AbstractFlow.h"

using namespace std;

/**
 * @brief Abstract class that represent a Model
 * 
 */
class AbstractModel {
protected:

	/**
	 * @brief Add a System to Model
	 * 
	 * @param s system to be added
	 */
    virtual void add(AbstractSystem* const s) = 0;
	/**
	 * @brief Add a Flow to Model
	 * 
	 * @param f flow do be added
	 */
	virtual void add(AbstractFlow* const f) = 0;


public:
	/**
	 * @brief Destroy the Abstract Model object
	 * 
	 */
    virtual ~AbstractModel(){};

	/**
	 * @brief Get the Systens Size object
	 * 
	 * @return int number of systens in the model
	 */
	virtual int getSystensSize() = 0;
	/**
	 * @brief Get the Flows Size object
	 * 
	 * @return int number of flows in the model
	 */
	virtual int getFlowsSize() = 0;

	/**
	 * @brief Set the Time object
	 * 
	 * @param time to be seted to model in a moment
	 */
	virtual void setTime(const double time) = 0;
	/**
	 * @brief Get the Time object
	 * 
	 * @return double time of moment of model
	 */
	virtual double getTime() = 0;

	/**
	 * @brief Set the Name object
	 * 
	 * @param name to be seted to model
	 */
	virtual void setName(const string name) = 0;
	/**
	 * @brief Get the Name object
	 * 
	 * @return string name of Model
	 */
	virtual string getName() = 0;

	/**
	 * @brief Create a System object
	 * 
	 * @param value initial value
     * @param name system name 
	 * @return AbstractSystem* 
	 */
	virtual AbstractSystem* createSystem(double value = 0.0, string name = "") = 0;

	/**
	 * @brief Create a Flow object
	 * 
	 * @param origin source AbstractSystem
     * @param destiny target AbstractSystem
     * @param function function that governs the flow
     * @param name flow name 
	 * @return AbstractFlow* 
	 */
	virtual AbstractFlow* createFlow(AbstractSystem *origin , AbstractSystem *destiny , double (*function)(AbstractSystem *o, AbstractSystem *d), string name) = 0;

	/**
	 * @brief Create a Model object
	 * 
	 * @param name model name
	 * @param time model time 
	 * @return AbstractModel* 
	 */
	static AbstractModel* createModel(string name = "", double time = 0.0);
	
	/**
	 * @brief 
	 * 
	 * @param initialTime initial time of Model execute
	 * @param finalTime final time of Model execute
	 * @param timeStep time step by step
	 * @return true = everything ok
	 * @return false = somenthing is wrong
	 */
	virtual bool execute(double initialTime, double finalTime, double timeStep) = 0;

};

#endif