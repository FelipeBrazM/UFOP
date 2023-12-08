#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "Model.h"
#include "System.h"
#include "Flow.h"
#include "SystemImpl.h"
#include "handleBodySemDebug.h"

using namespace std;

/**
 * @brief Model representation class
 * 
 */
class ModelImpl : public Body{
    protected:
        vector<System*> systens; /**< Container for systems in a Model*/
        static vector<Model*> models; /**< Container for models*/
        vector<Flow*> flows; /**< Container for flows in a Model*/
    private:
        string name; /**< Model name*/
        double timeInitial; /**< Initial Time for Model*/
        double timeFinal; /**< Final Time for Model*/
        double time; /**<Current time*/

        /**
         * @brief Construct a new Model object by copy
         * 
         * @param copy Model to be copied
         */
        ModelImpl(const ModelImpl& copy); // copy constructor
        /**
         * @brief overload = operator
         * 
         * @param m compared Model
         * @return Model& : return the copy
         */
        ModelImpl& operator= (const ModelImpl& m); // copy assignment operator


        /**
         * @brief add a model to container
         * 
         * @param model model to be added
         */
        static void add(Model* model);

    public:
        /**
         * @brief add a system to container
         * 
         * @param system system to be added
         */
        void add(System* system);
        /**
         * @brief empty constructor
         * 
         */
        ModelImpl(); // empty constructor
        /**
         * @brief Construct a new Model object
         * 
         * @param name Model name
         * @param timeInitial Model Initial Time
         * @param timeFinal Model Final Time
         */
        ModelImpl(const string name, const double timeInitial, const double timeFinal); // full constructor
        /**
         * @brief Destroy the Model object
         * 
         */
        virtual ~ModelImpl(); // destructor

        /**
         * @brief Get the Name of a Model
         * 
         * @return string : Model name
         */
        string getName() const; // Name getters and setters
        /**
         * @brief Set the Name of a Model
         * 
         * @param name Name to be seted
         */
        void setName(const string name);

        /**
         * @brief Get the Time Initial for a Model
         * 
         * @return double : Initial Time for Model
         */
        double getTimeInitial() const; // time initial getters and setters
        /**
         * @brief Set the Time Initial for a Model
         * 
         * @param timeInitial time initial to be seted
         */
        void setTimeInitial(const double timeInitial);

        /**
         * @brief Get the Time Final for a Model
         * 
         * @return double : Final Time for Model
         */
        double getTimeFinal() const; // time final getters and setters
        /**
         * @brief Set the Time Final for a Model
         * 
         * @param timeFinal time final to be seted
         */
        void setTimeFinal(const double timeFinal);

        /**
         * @brief Get the current time for a Model
         * 
         * @return double return the time
         */
        double getTime() const;
        /**
         * @brief Set the current time for a Model
         * 
         * @param time current time to be seted 
         */
        void setTime(const double time);

        
        /**
         * @brief Create a System object by fabric
         * 
         * @param name name of the System created
         * @param value initial value for the System created
         * @return System* pointer to the System created
         */
        System* createSystem(const string name="NoName", const double value=0.0);
        /**
         * @brief Create a Model object by fabric
         * 
         * @param name name of the Model created
         * @param timeInitial initial time of model created
         * @param timeFinal final time for model created
         * @return Model* pointer to the Model created
         */
        static Model* createModel(const string name="NoName", const double timeInitial=0.0, const double timeFinal=0.0);


        virtual void deleteSystem(System* system);
        virtual void deleteFlow(Flow* flow);
        // static void deleteModel(Model* model);

        /**
         * @brief add a flow to container
         * 
         * @param flow flow to be added
         */
        void add(Flow* flow);

        /**
         * @brief remove a system from container
         * 
         * @param sys system to be removed
         */
        void removal(System* const sys);
        /**
         * @brief remove a flow from container
         * 
         * @param flow flow to de removed
         */
        void removal(Flow* const flow);
        /**
         * @brief remove a model from container
         * 
         * @param model model to de removed
         */
        static void removal(Model* const model);

        //System iterator
        /**
         * @brief begin Iterator for the systems container
         * 
         * @return systemIterator: iterator for container (begin)
         */
        vector<System*>::iterator systemBegin(void);
        /**
         * @brief end Iterator for the systems container
         * 
         * @return systemIterator: iterator for container (end)
         */
        vector<System*>::iterator systemEnd(void);

        //Flow iterator
        /**
         * @brief begin Iterator for the flows container
         * 
         * @return flowIterator : iterator for container (begin)
         */
        vector<Flow*>::iterator flowBegin(void);
        /**
         * @brief end Iterator for the flows container
         * 
         * @return flowIterator : iterator for container (end)
         */
        vector<Flow*>::iterator flowEnd(void);

        vector<Model*>::iterator modelBegin(void);
        vector<Model*>::iterator modelEnd(void);

        /**
         * @brief function to execute all flows equations 
         * 
         * @param timeInitial Initial time for simulation
         * @param timeFinal Final time for simulation
         */
        void execute(double timeInitial, double timeFinal);

};

class ModelHandlePointer : public Model, public Handle<ModelImpl>{
    public:
    ModelHandlePointer(const string name="NoName", const double timeInitial=0.0, const double timeFinal=0.0){
        // cout << "const" << endl
        pImpl_->setName(name);
        pImpl_->setTimeInitial(timeInitial);
        pImpl_->setTimeFinal(timeFinal);
    }

    virtual ~ModelHandlePointer(){}

    void add(System* system){
        return pImpl_->add(system);
    }

    string getName() const{
        return pImpl_->getName();
    }
    
    void setName(const string name){
        return pImpl_->setName(name);
    }

    double getTimeInitial() const{
        return pImpl_->getTimeInitial();
    }
    
    void setTimeInitial(const double timeInitial){
        return pImpl_->setTimeInitial(timeInitial);
    }

    double getTimeFinal() const{
        return pImpl_->getTimeFinal();
    }
    
    void setTimeFinal(const double timeFinal){
        return pImpl_->setTimeFinal(timeFinal);
    }

    double getTime() const{
        return pImpl_->getTime();
    }
    
    void setTime(const double time){
        return pImpl_->setTime(time);
    }

    System* createSystem(const string name="NoName", const double value=0.0){
        return pImpl_->createSystem(name, value);
    }

    virtual void deleteSystem(System* system){
        return pImpl_->deleteSystem(system);
    }

    virtual void deleteFlow(Flow* flow){
        return pImpl_->deleteFlow(flow);
    }

    void add(Flow* flow){
        return pImpl_->add(flow);
    }

    void removal(System* const sys){
        return pImpl_->removal(sys);
    }
    
    void removal(Flow* const flow){
        return pImpl_->removal(flow);
    }

    vector<System*>::iterator systemBegin(void){
        return pImpl_->systemBegin();
    }
    
    vector<System*>::iterator systemEnd(void){
        return pImpl_->systemEnd();
    }

    vector<Flow*>::iterator flowBegin(void){
        return pImpl_->flowBegin();
    }

    vector<Flow*>::iterator flowEnd(void){
        return pImpl_->flowEnd();
    }

    vector<Model*>::iterator modelBegin(void){
        return pImpl_->modelBegin();
    }
    vector<Model*>::iterator modelEnd(void){
        return pImpl_->modelEnd();
    }

    void execute(double timeInitial, double timeFinal){
        return pImpl_->execute(timeInitial, timeFinal);
    }

};

#endif