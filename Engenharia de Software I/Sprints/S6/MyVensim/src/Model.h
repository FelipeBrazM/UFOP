#ifndef MODEL_H
#define MODEL_H

#include <algorithm>
#include <vector>
#include <string>
#include "System.h"
#include "Flow.h"

/**
 * @brief Model interface for the user
 * 
 */
class Model{
    public:
        // typedef vector<System*>::iterator systemIterator;
        // typedef vector<Flow*>::iterator flowIterator; 
        /**
         * @brief Destroy the Model object
         * 
         */
        virtual ~Model(){}

        /**
         * @brief Get the Name of a Model
         * 
         * @return string : Model name
         */
        virtual string getName() const = 0;
        /**
         * @brief Set the Name of a Model
         * 
         * @param name Name to be seted
         */
        virtual void setName(const string name) = 0;

        /**
         * @brief Get the Time Initial for a Model
         * 
         * @return double : Initial Time for Model 
         */
        virtual double getTimeInitial() const = 0;
        /**
         * @brief Set the Time Initial for a Model
         * 
         * @param timeInitial time initial to be seted
         */
        virtual void setTimeInitial(const double timeInitial) = 0;

        /**
         * @brief Get the Time Final for a Model
         * 
         * @return double : Final Time for Model
         */
        virtual double getTimeFinal() const = 0;
        /**
         * @brief Set the Time Final for a Model
         * 
         * @param timeFinal time final to be seted
         */
        virtual void setTimeFinal(const double timeFinal) = 0;

        /**
         * @brief Get the current time for a Model
         * 
         * @return double return the time
         */
        virtual double getTime() const = 0;
        /**
         * @brief Set the current time for a Model
         * 
         * @param time current time to be seted
         */
        virtual void setTime(const double time) = 0;

        /**
         * @brief Create a System object by fabric
         * 
         * @param name name of the System created
         * @param value initial value for the System created
         * @return System* pointer to the System created
         */
        virtual System* createSystem(const string name="NoName", const double value=0.0) = 0;
        /**
         * @brief Create a Model object by fabric
         * 
         * @param name name of the Model created
         * @param timeInitial initial time of model created
         * @param timeFinal final time for model created
         * @return Model* pointer to the Model created
         */
        static Model* createModel(const string name="NoName", const double timeInitial=0.0, const double timeFinal=0.0);

        /**
         * @brief Create a Flow object by fabric
         * 
         * @tparam FlowImplemented template for flows created by user
         * @param name name of the Flow created
         * @param input input or source of the flow created
         * @param output output or target of the flow created
         * @return Flow* pointer to the Flow created
         */
        template <typename FlowImplemented>
        Flow* createFlow(const string name="NoName", System* input=NULL, System* output=NULL){
            Flow* flow = new FlowImplemented(name, input, output);
            add(flow);
            return flow;
        }

        /**
         * @brief delete systems created by fabric
         * 
         * @param system system to be deleted
         */
        virtual void deleteSystem(System* system) = 0;
        /**
         * @brief delete flows created by fabric
         * 
         * @param flow flow to be deleted
         */
        virtual void deleteFlow(Flow* flow) = 0;
        // /**
        //  * @brief delete models created by fabric
        //  * 
        //  * @param model model to be deleted
        //  */
        // static void deleteModel(Model* model);

        /**
         * @brief remove a system from container
         * 
         * @param system system to be removed
         */
        virtual void removal(System* const system) = 0;
        /**
         * @brief remove a flow from container
         * 
         * @param flow flow to de removed
         */
        virtual void removal(Flow* const flow) = 0;
        /**
         * @brief remove a Model from container
         * 
         * @param model model to de removed
         */
        static void removal(Model* const model);

        /**
         * @brief begin Iterator for the systems container
         * 
         * @return vector<System*>::iterator iterator for container (begin)
         */
        virtual vector<System*>::iterator systemBegin()  = 0;
        /**
         * @brief end Iterator for the systems container
         * 
         * @return vector<System*>::iterator iterator for container (end)
         */
        virtual vector<System*>::iterator systemEnd()  = 0;

        /**
         * @brief begin Iterator for the flows container
         * 
         * @return vector<Flow*>::iterator iterator for container (begin)
         */
        virtual vector<Flow*>::iterator flowBegin()  = 0;
        /**
         * @brief end Iterator for the flows container
         * 
         * @return vector<Flow*>::iterator iterator for container (end)
         */
        virtual vector<Flow*>::iterator flowEnd()  = 0;

        /**
         * @brief begin Iterator for the models container
         * 
         * @return vector<Model*>::iterator iterator for container (begin)
         */
        virtual vector<Model*>::iterator modelBegin() = 0;
        /**
         * @brief end Iterator for the models container
         * 
         * @return vector<Model*>::iterator iterator for container (end)
         */
        virtual vector<Model*>::iterator modelEnd() = 0;

        /**
         * @brief function to execute all flows equations 
         * 
         * @param timeInitial Initial time for simulation
         * @param timeFinal Final time for simulation
         */
        virtual void execute(double timeInitial, double timeFinal) = 0;

    protected:
        /**
         * @brief add a flow to container
         * 
         * @param flow flow to be added
         */
        virtual void add(Flow* flow) = 0;

};


#endif