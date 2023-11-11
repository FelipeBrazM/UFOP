/*  
    Felipe Braz Marques 22.1.4030
*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/**
 * @brief System that represents something that stores something
 * 
 */
class System{
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
    System();
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
    void setvalue(double);
    /**
     * @brief Get the Initial Value object
     * 
     * @return double value of System
     */
    double getvalue(void) const;

    /**
     * @brief Set the Name object
     * 
     */
    void setName(string);
    /**
     * @brief Get the Name object
     * 
     * @return double name of System
     */
    string getName(void) const;


    /**
     * @brief Class of output default
     * 
     */
    virtual void output(ostream&) const;
    /**
     * @brief cout operator overload
     * 
     * @return ostream& 
     */
    friend ostream& operator << (ostream&, const System&); 
};

#endif //SYSTEM_H