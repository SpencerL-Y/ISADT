#ifndef CodeGenerator_CodeGenerator_h
#define CodeGenerator_CodeGenerator_h
#include "Model.hpp"
namespace isadt
{
    class CodeGenerator
    {
        protected:
            Model* model;
        public:
            Model* getModel() const;
            virtual void generateCode(std::string path);
    };
}


#endif