#include "../../src/FlowImpl.h"
#include "../../src/System.h"
#include "../../src/Model.h"
#include <string>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

/**
 * @brief Class for exponential test (funcional test)
 * 
 */
class Exponential : public FlowImpl{

    public:
    /**
     * @brief Construct a new Exponential object
     * 
     * @param name name of the Exponential Flow
     * @param input source or input of the Exponential Flow
     * @param output target or output of the Exponential Flow
     */
    Exponential(const string name="teste", System* input = NULL, System* output = NULL) : FlowImpl(name, input, output, 0.0) {}
    /**
     * @brief extended execution function
     * 
     * @return double value of the extended execution function
     */
    virtual double execute(){
        return 0.01 * systemInput->getValue();
    }
};

/**
 * @brief Class for logistic test (funcional test)
 * 
 */
class Logistic : public FlowImpl{
    public:
    /**
     * @brief Construct a new Logistic object
     * 
     * @param name name of Logistic Flow
     * @param input source or input of Logistic Flow
     * @param output target or output of Logistic Flow
     */
    Logistic(const string name="teste", System* input = NULL, System* output = NULL) : FlowImpl(name, input, output,0.0) {}
    /**
     * @brief extended execute function
     * 
     * @return double value of the extended execution function
     */
    virtual double execute(){
        return 0.01 * systemOutput->getValue() * (1-(systemOutput->getValue()/70));
    }
};

/**
 * @brief Class for complex test (funcional test)
 * 
 */
class ComplexFlow : public FlowImpl{
    public:
    /**
     * @brief Construct a new Complex Flow object
     * 
     * @param name name of the complex Flow
     * @param input source or input of the complex Flow
     * @param output target or output of the complex Flow
     */
    ComplexFlow(const string name="teste", System* input = NULL, System* output = NULL) : FlowImpl(name, input, output,0.0) {}
    /**
     * @brief extended execution function
     * 
     * @return double value of the extended execution function 
     */
    virtual double execute(){
        return 0.01 * systemInput->getValue();
    }
};