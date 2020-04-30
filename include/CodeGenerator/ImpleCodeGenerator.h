#ifndef CodeGenerator_ImpleCodeGenerator_h
#define CodeGenerator_ImpleCodeGenerator_h
#include "CodeGenerator.h"
namespace isadt 
{
    class ImpleCodeGenerator : public CodeGenerator
    {
        private:

        public:
            ImpleCodeGenerator(/*args*/);
            ~ImpleCodeGenerator();
            virtual std::string generateDecrptAlgorithm() = 0;
            virtual std::string generateEncrptAlgorithm() = 0;
    };
}

#endif