/*  
    Felipe Braz Marques 22.1.4030
*/
#ifndef FLOW_H
#define FLOW_H

#include "System.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Flow connecting two systems
 * 
 */
class Flow{
protected:
    System *origin;/**< Pointer to the stream source system*/
    System *destiny;/**< Pointer to the stream's target system*/
    double value;/**< Current value that is passing in the stream*/
    string name;/**< Name of Flow*/
	double (*function)(System* const o, System* const d);/**< Function that affects the governs the flow and affects the target system*/

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
     * @param origin source system
     * @param destiny target system
     * @param function function that governs the flow
     * @param name flow name
     */
    Flow(System *origin , System *destiny , double (*function)(System *o, System *d), string name);

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
     * @param origin pointer to source system
     */
    void setOrigin(System *origin );
    /**
     * @brief Get the Origin object
     * 
     * @return System* to the origin system
     */
    System* getOrigin(void) const;

    /**
     * @brief Set the Destiny object
     * 
     * @param destiny pointer to destiny system
     */
    void setDestiny(System * destiny);
    /**
     * @brief Get the Destiny object
     * 
     * @return System* to destiny system
     */
    System* getDestiny(void) const;

    /**
     * @brief Set the Value object
     * 
     * @param value new value
     */
    void setValue(double value);
    /**
     * @brief Get the Value object
     * 
     * @return double value of flow
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
     * @return string name of flow
     */
    string getName(void) const;

    /**
     * @brief Set the Function object
     * 
     * @param function to be used by flow
     */
    void setFunction(double (*function)(System *o, System *d));
    /**
     * @brief Execute function to add to value
     * 
     */
    void execute();

    /**
     * @brief Class of output default
     * 
     */
    virtual void output(ostream&) const;
    /**
     * @brief cout operator overload
     * 
     * @return ostream& of output()
     */
    friend ostream& operator << (ostream&, const Flow&); 
};

#endif