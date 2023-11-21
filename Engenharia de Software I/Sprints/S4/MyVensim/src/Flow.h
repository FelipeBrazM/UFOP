/* Felipe Braz Marques - 22.1.4030 */

#ifndef FLOW_H
#define FLOW_H 

#include "AbstractSystem.h"
#include "AbstractFlow.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Flow connecting two Systems
 * 
 */
class Flow: public AbstractFlow{
protected:
    AbstractSystem *origin;
    AbstractSystem *destiny;
    double value;
    string name;
	double (*function)(AbstractSystem* const o, AbstractSystem* const d);

private:
    /**
     * @brief Operator = overload
     * 
     * @param s Flow to be copied
     * @return Flow& 
     */
	Flow& operator= (const Flow& s);

public:
    /**
     * @brief Construct a new Flow object
     * 
     */
    Flow();

    /**
     * @brief Construct a new Flow object
     * 
     * @param origin source AbstractSystem
     * @param destiny target AbstractSystem
     * @param function function that governs the flow
     * @param name flow name
     */
    Flow(AbstractSystem *origin , AbstractSystem *destiny , double (*function)(AbstractSystem *o, AbstractSystem *d), string name);

    /**
     * @brief Construct a new Flow object
     * 
     */
    Flow(const Flow&);

    /**
     * @brief Destroy the Flow object
     * 
     */
    virtual ~Flow();

    /**
     * @brief Set the Origin object
     * 
     * @param origin pointer to source AbstractSystem
     */
    void setOrigin(AbstractSystem *origin );
    /**
     * @brief Get the Origin object
     * 
     * @return AbstractSystem* 
     */
    AbstractSystem* getOrigin(void) const;

    /**
     * @brief Set the Destiny object
     * 
     * @param destiny pointer to destiny AbstractSystem
     */
    void setDestiny(AbstractSystem * destiny);
    /**
     * @brief Get the Destiny object
     * 
     * @return AbstractSystem* 
     */
    AbstractSystem* getDestiny(void) const;

    /**
     * @brief Set the Value object
     * 
     * @param value new value
     */
    void setValue(double value);
    /**
     * @brief Get the Value object
     * 
     * @return double 
     */
    double getValue(void) const;

    /**
     * @brief Set the Name object
     * 
     */
    void setName(string);
    /**
     * @brief Get the Name object
     * 
     * @return string 
     */
    string getName(void) const;

    /**
     * @brief Set the Function object
     * 
     * @param function 
     */
    void setFunction(double (*function)(AbstractSystem *o, AbstractSystem *d));
    /**
     * @brief Execute function to add to value
     * 
     */
    void execute();

    /**
     * @brief Class of output default
     * 
     */
    void output(ostream& out) const;
    /**
     * @brief cout operator overload
     * 
     * @return ostream& 
     */
    friend ostream& operator << (ostream&, const Flow&); 
};

#endif