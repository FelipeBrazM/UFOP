/*  
    Felipe Braz Marques 22.1.4030
*/
#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "System.h"
#include "Flow.h"

using namespace std;

/**
 * @brief Model class that stores the systems, flows and variables
 * 
 */
class Model {
protected:
	double time;/**< Model time*/
	vector<System*> systens;/**< Systens contained in the model*/
	vector<Flow*> flows;/**< Flows contained in the model*/
	string name;/**< Model name*/

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
	Model(const string name = "", const double time = 0.0);
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
	 * @brief Add System to the model
	 * 
	 * @param s system to be added
	 */
	void add(System* const s);

	/**
	 * @brief Add Flow to the model
	 * 
	 * @param f flow to be added
	 */
	void add(Flow* const f);
	
	/**
	 * @brief Set the Time object
	 * 
	 * @param time model time at the moment
	 */
	void setTime(const double time);
	/**
	 * @brief Get the Time object
	 * 
	 * @return double time of moment in the model
	 */
	double getTime();

	/**
	 * @brief Set the Name object
	 * 
	 * @param name to be given to model
	 */
	void setName(const string name);
	/**
	 * @brief Get the Name object
	 * 
	 * @return string name of model
	 */
	string getName();

	/**
	 * @brief function that runs the model
	 * 
	 * @param initialTime start time
	 * @param finalTime maximum time
	 * @param timeStep step of time
	 * 
	 * @return true everything ok
	 * @return false somenthing is wrong
	 */
	bool execute(double initialTime, double finalTime, double timeStep);

};

#endif //MODEL_H