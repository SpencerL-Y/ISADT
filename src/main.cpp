#include <iostream>
#include <list>
#include "../include/Model/Type/Type.hpp"
#include "../include/Model/Model.hpp"
#include "../include/CodeGenerator/CCodeGenerator.hpp"
using namespace std;
using namespace isadt;

int main() {
    
    Model* model = new Model();
    Process* p  = model->mkProcess("TestClazz");
    Type* type = new Type();
    type->setName("int");
    p->mkAttribute(type, "testAttr1_");
    p->mkAttribute(type, "testAttr2_");
    list<Attribute*> attrList;
    p->mkMethod("getTestAttr1", type, attrList);
    attrList.push_front(new Attribute(type, "testAttr1"));
    p->mkMethod("setTestAttr2", type, attrList);
    StateMachine* m = p->mkFst();
    m->addVertex("start");
    m->addVertex("mid1");
    Guard* g = new Guard(new Expression("testAttr1_ > 0"));
    Action* act = new Action("testAttr2_ = -1");
    list<Action*> l;
    l.push_back(act);
    Edge* edge = new Edge(m->getVertexByName("start"), m->getVertexByName("mid1"), g, l);
    m->addEdge(edge);
    CCodeGenerator * gen = new CCodeGenerator();
    
    gen->generateCode("C:\\Users\\10244\\Desktop\\generatedCode", model->getProcesses().front());
    
}
