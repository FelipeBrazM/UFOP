#ifndef FLOW_H
#define FLOW_H

#include "System.h"
#include <string>
using namespace std;

/**
 * @brief Flow interface for the user
 * 
 */
class Flow{
    public:
        /**
         * @brief Destroy the Flow object
         * 
         */
        virtual ~Flow(){}

        /**
         * @brief Get the Name of a Flow object
         * 
         * @return string name of the Flow object
         */
        virtual string getName() const = 0;
        /**
         * @brief Set the Name of a Flow object
         * 
         * @param name name to be assigned
         */
        virtual void setName(const string name) = 0;

        /**
         * @brief get source or input system
         * 
         * @return System* pointer to the source or input system
         */
        virtual System* getSystemInput() const = 0;
        /**
         * @brief set source or input system
         * 
         * @param input pointer to system to be assigned
         */
        virtual void setSystemInput(System* const input) = 0;

        /**
         * @brief get destination or output system
         * 
         * @return System* pointer to the destination or output system
         */
        virtual System* getSystemOutput() const = 0;
        /**
         * @brief set destination or output system
         * 
         * @param output pointer to system to be assigned
         */
        virtual void setSystemOutput(System* const output) = 0;

        /**
         * @brief Get the tax of a flow (value after execution)
         * 
         * @return double value after execution
         */
        virtual double getTax() const = 0;
        /**
         * @brief Set manually the tax of a flow (value after execution)
         * 
         * @param tax value to be assigned
         */
        virtual void setTax(const double tax) = 0;

        /**
         * @brief function to calculate the tax of a flow (value after execution)
         * 
         * @return double value after execution
         */
        virtual double execute() = 0;
};

#endif