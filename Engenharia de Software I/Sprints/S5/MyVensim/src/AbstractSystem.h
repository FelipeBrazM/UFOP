#ifndef ABSTRACTSYSTEM_H
#define ABSTRACTSYSTEM_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Abstarct class that represent a System
 * 
 */
class AbstractSystem{
public:
    /**
     * @brief Destroy the Abstract System object
     * 
     */
    virtual ~AbstractSystem(){};

    /**
     * @brief Set the Value object
     * 
     * @param value 
     */
    virtual void setValue(double value) = 0;
    /**
     * @brief Get the Value object
     * 
     * @return double 
     */
    virtual double getValue(void) const = 0;

    /**
     * @brief Set the Name object
     * 
     * @param name 
     */
    virtual void setName(string name) = 0;
    /**
     * @brief Get the Name object
     * 
     * @return string 
     */
    virtual string getName(void) const = 0;

    /**
     * @brief string of out
     * 
     * @param out 
     */
    virtual void saida(ostream& out) const = 0;
    /**
     * @brief << owerflow
     * 
     * @return ostream& 
     */
    friend ostream& operator << (ostream&, const AbstractSystem&); 
};

#endif //SYSTEM_H