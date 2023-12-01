#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

using namespace std;

/**
 * @brief System interface for user
 * 
 */
class System{
    public:
        /**
         * @brief Destroy the System object
         * 
         */
        virtual ~System() {}

        /**
         * @brief Get the name of the System
         * 
         * @return string name of the System
         */
        virtual string getName() const = 0;
        /**
         * @brief Set a name for the System
         * 
         * @param name name to be assigned to the System
         */
        virtual void setName(const string name) = 0;

        /**
         * @brief Get the value of the System
         * 
         * @return double internal value of the System 
         */
        virtual double getValue() const = 0;
        /**
         * @brief Set a value for the System
         * 
         * @param value value to be assigned
         */
        virtual void setValue(const double value) = 0;

};


#endif