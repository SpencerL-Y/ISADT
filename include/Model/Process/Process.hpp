//
//  Process.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Process_hpp
#define Model_Process_hpp 
#include "Method.hpp"
#include "CommMethod.hpp"
#include "../StateMachine/StateMachine.hpp"

namespace isadt {
    class Model;

    /// \brief the process of model.
    class Process {
    public:
        Process();
        Process(Model* model);
        ~Process() {
            //delete attributes, methods, signals and fst.
        }

        Model* getModel() const;
        void setModel(Model* model);

        Attribute* mkAttribute(Type* type, const string& name);
        Method* mkMethod(const string& name, Type* returnType, list<Attribute*> parameters);
        CommMethod* mkCommMethod(const string& name, bool inout, Attribute* parameter);
        
        StateMachine* mkFst(){
            StateMachine* sm = new StateMachine();
        }

        const list<Attribute*>& getAttributes()const{
            return this->attributes_;
        }

        const std::string& getProcName(){
            return this->procName_;
        }

        void setProcName(std::string procName){
            this->procName_ = procName;
        }

        const list<Method*>& getMethods() const{
            return this->methods_;
        }
        const list<CommMethod*>& getCommMethods() const {
            return this->commMethods_;
        }
        const StateMachine* getStateMachine(){
            return &(this->statemachine_);
        }
    private:
        std::string procName_;
        list<Attribute*> attributes_;        ///< the attributes for this process.
        list<Method*> methods_;              ///< the methods for this process.
        list<CommMethod*> commMethods_;      ///< the communication methods for this process.
        list<StateMachine*> statemachines_;  ///< the finite state machines for this process.
        StateMachine statemachine_;
        Model* model_;                       ///< the model this process from.
    };
}

#endif /* Model_Process_hpp */
