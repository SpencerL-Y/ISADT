#include <iostream>
#include "Model/Type/Type.hpp"
#include "Model/Model.hpp"
using namespace std;
using namespace isadt;

int main() {
    BoolType type;
    cout << type.getName() << endl;
    Model* model = new Model();
}
