#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "AbstractSystem.h"

using namespace std;
/**
 * @brief System that represents something that stores something
 * 
 */
class System: public AbstractSystem{
protected: 
    double value;/**< System initial value*/
    string name; /**< Name of System*/

private:
    /**
     * @brief Operator = overload
     * 
     * @param s System to be copied
     * @return System& 
     */
	System& operator= (const System& s);

public:
    /**
     * @brief Construct a new System object
     * 
     */
    System(void);
    /**
     * @brief Construct a new System object
     * 
     * @param value initial value
     * @param name system name
     */
    System(double value, string name);
    /**
     * @brief Construct a new System object
     * 
     * @param sys System to be copied
     */
    System(const System& sys);
    /**
     * @brief Destroy the System object
     * 
     */
    virtual ~System();

    /**
     * @brief Set the Initial Value object
     * 
     */
    void setValue(double);
    /**
     * @brief Get the Initial Value object
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
     * @return double 
     */
    string getName(void) const;


    /**
     * @brief Class of output default
     * 
     */
    virtual void saida(ostream&) const;
    /**
     * @brief cout operator overload
     * 
     * @return ostream& 
     */
    friend ostream& operator << (ostream&, const AbstractSystem&); 
};

#endif //SYSTEM_H