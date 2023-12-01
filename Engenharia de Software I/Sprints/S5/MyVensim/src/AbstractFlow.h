// Felipe Braz Marques - 22.1.4030
#ifndef ABSTRACTFLOW_H
#define ABSTRACTFLOW_H

#include "AbstractSystem.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Abstract class tha represente a Flow
 * 
 */
class AbstractFlow{
public:
    /**
     * @brief Destroy the Abstract Flow object
     * 
     */
    virtual ~AbstractFlow(){};

    /**
     * @brief Set the Origin object
     * 
     * @param origin 
     */
    virtual void setOrigin(AbstractSystem *origin ) = 0;
    /**
     * @brief Get the Origin object
     * 
     * @return AbstractSystem* 
     */
    virtual AbstractSystem* getOrigin() const = 0;

    /**
     * @brief Set the Destiny object
     * 
     * @param destiny 
     */
    virtual void setDestiny(AbstractSystem *destiny ) = 0;
    /**
     * @brief Get the Destiny object
     * 
     * @return AbstractSystem* 
     */
    virtual AbstractSystem* getDestiny() const = 0;

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
    virtual double getValue() const = 0;

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
    virtual string getName() const = 0;

    /**
     * @brief Set the Function object
     * 
     * @param function 
     */
    virtual void setFunction(double (*function)(AbstractSystem *o, AbstractSystem *d)) = 0;
    /**
     * @brief 
     * 
     */
    virtual void execute() = 0;

    /**
     * @brief 
     * 
     * @param out 
     */
    virtual void output(ostream& out) const = 0;
};

#endif