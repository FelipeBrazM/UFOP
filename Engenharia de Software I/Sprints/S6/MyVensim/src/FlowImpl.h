#ifndef FLOWIMPL_H
#define FLOWIMPL_H


#include <string>
#include "Flow.h"
#include "System.h"
#include "handleBodySemDebug.h"

/**
 * @brief Flows abstract class
 * 
 */
class FlowImpl : public Body{
    protected:
        string name;/**< Flow name*/
        System *systemInput;/**< Pointer to flow source or input*/
        System *systemOutput;/**< Pointer to flow target or output*/
        double tax;/**< Flow value of execution*/
    
    private:
        /**
         * @brief Construct a new Flow object by copy
         * 
         * @param copy Flow to be copied
         */
        FlowImpl(const FlowImpl& copy); // copy constructor
        /**
         * @brief overloaded = operator
         * 
         * @param f compared Flow 
         * @return FlowImpl& : return the copy
         */
        FlowImpl& operator= (const FlowImpl& f); // copy assignment operator

    public:
        /**
         * @brief empty contructor
         * 
         */
        FlowImpl(); // empty constructor
        /**
         * @brief Construct a new Flow object with parameters
         * 
         * @param name Flow name
         * @param systemInput source or input of a Flow
         * @param systemOutput target or output of a Flow
         * @param tax flow value of execution
         */
        FlowImpl(const string name, System *systemInput, System *systemOutput, double tax); // constructor
        /**
         * @brief Destroy the Flow object
         * 
         */
        virtual ~FlowImpl(); // destructor

        /**
         * @brief Get the Name of Flow
         * 
         * @return string : Flow name
         */
        string getName() const; // name getters and setters
        /**
         * @brief Set the Name of Flow
         * 
         * @param name string to be seted
         */
        void setName(const string name);

        /**
         * @brief Get the System Input of a Flow
         * 
         * @return System* : System source or input
         */
        System *getSystemInput() const; // system input getters and setters
        /**
         * @brief Set the System Input of a Flow
         * 
         * @param systemInput system to be seted
         */
        void setSystemInput(System* const systemInput);

        /**
         * @brief Get the System Output for a Flow
         * 
         * @return System* : System target or output
         */
        System *getSystemOutput() const; // system output getters and setters
        /**
         * @brief Set the System Output for a Flow
         * 
         * @param systemOutput system to be seted
         */
        void setSystemOutput(System* const systemOutput);

        /**
         * @brief Get the Tax
         * 
         * @return double : Tax after execution
         */
        double getTax() const; // tax getters and setters
        /**
         * @brief Set the Tax
         * 
         * @param tax : tax to be seted
         */
        void setTax(const double tax);

};

class FlowHandlePointer : public Flow, public Handle<FlowImpl>{
    public:
    FlowHandlePointer(const string name="NoName", System *systemInput=NULL, System *systemOutput=NULL, double tax=0.0){
        pImpl_->setName(name);
        pImpl_->setSystemInput(systemInput);
        pImpl_->setSystemOutput(systemOutput);
        pImpl_->setTax(tax);
    }

    virtual ~FlowHandlePointer(){}

    string getName() const{
        return pImpl_->getName();
    } 

    void setName(const string name){
        return pImpl_->setName(name);
    }

    System *getSystemInput() const{
        return pImpl_->getSystemInput();
    }

    void setSystemInput(System* const systemInput){
        return pImpl_->setSystemInput(systemInput);
    }

    System *getSystemOutput() const{
        return pImpl_->getSystemOutput();
    }

    void setSystemOutput(System* const systemOutput){
        return pImpl_->setSystemOutput(systemOutput);
    }
    
    double getTax() const{
        return pImpl_->getTax();
    }
    
    void setTax(const double tax){
        return pImpl_->setTax(tax);
    }

    virtual double execute() = 0;

};


#endif