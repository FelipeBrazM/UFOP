#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H


#include "System.h"
#include <string>
#include <iostream>
using namespace std;

/**
 * @brief System class implementation
 * 
 */
class SystemImpl : public System{

    private:
        string name; /**< system name*/
        double value; /**< value of a System*/
        /**
         * @brief Construct a new System object by copy
         * 
         * @param copy System to be copied
         */

        SystemImpl(const SystemImpl& copy); // copy constructor
        /**
         * @brief overload = operator
         * 
         * @param s compared system
         * @return System& : return the copy 
         */
        SystemImpl& operator= (const SystemImpl& s); //copy assignment operator
    
    public:
        /**
         * @brief Construct a new System object with parameters
         * 
         * @param name System name
         * @param value System value
         */
        SystemImpl(string name, double value); // constructor
        /**
         * @brief Construct a new System object
         * 
         */
        SystemImpl(); // empty constructor
        /**
         * @brief Destroy the System object
         * 
         */
        virtual ~SystemImpl(); // destructor

        /**
         * @brief Get the Name of a System
         * 
         * @return string : System name
         */
        string getName() const; // name getters and setters
        /**
         * @brief Set the Name of a System
         * 
         * @param name string to be seted
         */
        void setName(const string name);
        /**
         * @brief Get the Value of a  System
         * 
         * @return double : System value
         */
        double getValue() const; // value getters and setters
        /**
         * @brief Set the Value of a System
         * 
         * @param value double to be seted
         */
        void setValue(const double value);


        /**
         * @brief overload << operator
         * 
         * @param os output stream
         * @param s system printed
         * @return ostream& new stream
         */
        // friend ostream& operator<<(ostream& os, const System& s); //printf operator<<

};

#endif