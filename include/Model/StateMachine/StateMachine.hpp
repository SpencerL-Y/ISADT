//
//  StateMachine.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_StateMachine_hpp
#define Model_StateMachine_hpp
#include <list>
#include "Vertex.hpp"
#include "Edge.hpp"
using std::string;
namespace isadt {
    class Process;

    /// \brief StateMachine class
	class StateMachine {
	public:
		StateMachine();
		StateMachine(Process* p){
			this->process_ = p;
		}
		~StateMachine(){

		}
		void mkStartVertex(std::string name){
			if(this->startVertex_ != nullptr){
				std::cout << "startVertex exist" << std::endl;
				return;
			}
			for(Vertex * v : this->getVertices()){
				if(!v->getName().compare(name)){
					std::cout << "vertex name exists" << std::endl;
				}
			}
			Vertex * vertex = new Vertex(name);
			this->startVertex_ = vertex;
			this->vertices_.push_front(vertex);
		}

		const Vertex* getStartVertex(){
			return this->startVertex_;
		}

		const std::list<Vertex *>& getVertices() const{
			return this->vertices_;
		}

		const std::list<Edge*>& getEdges() const{
			return this->edges_;
		}

		void addVertex(){

		}

		void addEdge(){

		}

	private:
    	std::list<Vertex*> vertices_;    //< the set of the states of this fsm.
    	std::list<Edge*> edges_;         //< the set of the transitions of this fsm.
    	Vertex* startVertex_;            //< record the start state of this fsm.
    	Process* process_;               //< the StateMachine belongs to the process.
	};
}
#endif /* Model_StateMachine_hpp */
