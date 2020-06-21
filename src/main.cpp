#include <iostream>
#include <list>
#include "../include/Model/Type/Type.hpp"
#include "../include/Model/Model.hpp"
#include "../include/CodeGenerator/CCodeGenerator.hpp"
using namespace std;
using namespace isadt;

int main() {
     cout << "here";
     
    Model* model = new Model();
    Process* p  = model->mkProcess("TestClazz");
    Type* type = new Type();
    cout << "here";
    type->setName("int");
    p->mkAttribute(type, "testAttr1_");
    p->mkAttribute(type, "testAttr2_");
    list<Attribute*> attrList; 
    cout << "here";
    StateMachine* m = p->mkFst();
    m->mkStartVertex("start");
    m->addVertex("mid1");
    Guard* g = new Guard(new Expression("testAttr1_ > 0"));
    Action* act = new Action("testAttr2_ = -1");
    list<Action*> l;
    l.push_back(act);
    Edge* edge = new Edge(m->getVertexByName("start"), m->getVertexByName("mid1"), g, l);
    m->addEdge(edge);
    CCodeGenerator * gen = new CCodeGenerator();
    
    gen->generateCode("./generatedCode", model->getProcesses().front());
    
}
