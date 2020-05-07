#include <iostream>
#include <list>
#include "Model/Type/Type.hpp"
#include "Model/Model.hpp"
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
    p->mkFst();

    list<Process*> processes = model->getProcesses();

}
