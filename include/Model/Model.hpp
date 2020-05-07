//
//  Model.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Model_hpp
#define Model_Model_hpp 
#include "Type/UserType.hpp"
#include "Process/Process.hpp"
#include "Pragma/Property.hpp"
#include "Pragma/InitialKnowledge.hpp"
#include "SequenceDiagram/SequenceDiagram.hpp"

namespace isadt {
    /// \brief the model in isadt.
    class Model {
    public:
        Model();
        ~Model() {
            //delete processes, properties, initialknowledges.
        }

        Process* mkProcess();
        Process* mkProcess(std::string procName){
            for(Process* p : this->processes_){
                if(!procName.compare(p->getProcName())){
                    std::cout << "Process Exists" << std::endl;
                    return NULL;
                }
            }
            Process* p = new Process(this);
            p->setProcName(procName);
            this->processes_.push_front(p);
            return p;
        }

        ConfidentialProperty*
        mkConfidentialProperty(Process* process, Attribute* attribute);

        AuthenticityProperty* 
        mkAuthenticityProperty(Process* process1, Vertex* vertex1, Attribute* attribute1,
                               Process* process2, Vertex* vertex2, Attribute* attribute2);

        InitialKnowledge* 
        mkInitialKnowledge(Process* process, Attribute* attribute);
        
        const list<Process*>& getProcesses() const{
            return this->processes_;
        }

        list<UserType*> getUserTypes();
    private:
        list<Process*> processes_;
        list<Property*> properties_;
        list<InitialKnowledge*> initialKnowledges_;
        list<UserType*> userTypes_;
        SequenceDiagram* sd_;
    };
}

#endif /* Model_Model_hpp */
