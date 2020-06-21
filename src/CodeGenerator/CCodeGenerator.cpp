#include "CodeGenerator/CCodeGenerator.hpp"
#define INCLUDE_HEADER "#include <stdio.h>\n#include <thread>\n#include <uinstd.h>\n#include <stdlib.h>\n"
#define LOCAL_INCLUDE ""
#define REAL_INCLUDE ""
#define CR "\n"
#define TAB "\t"
namespace isadt{
    void CCodeGenerator::addPlugin(Plugin* plugin){
        // 1. check the language is the same as the class
		// 2. avoid redundant addition
		for (Plugin* p : this->plugins)
		{
			if (!(!p->getPluginAlgorithmId().compare(plugin->getPluginAlgorithmId())
				|| !p->getPluginLanguage().compare(plugin->getPluginLanguage()))
				|| !p->getPluginName().compare(plugin->getPluginName()))
			{
				std::cout << "Error: plugin adding error, plugin already exists." << std::endl;
			}
			else
			{
				this->plugins.push_front(plugin);
			}
		}
    }

        Plugin*  CCodeGenerator::getFirstPlugin()
        {
            // iterate the list and return the first usable plugin
		    // otherwise return null
		    if (this->plugins.size() > 0)
		    {
		    	return this->getPlugins().front();
		    }
		    else
		    {
		    	std::cout << "WARNING: no available plugin.";
		    	return nullptr;
		    }
        }
        Plugin*  CCodeGenerator::getPlugin(std::string algorithmId, std::string pluginLanguage)
        {
            // get the correspoding plugin in the list
		    // otherwise return null
		    for (Plugin* p : this->getPlugins())
		    {
		    	if (!p->getPluginLanguage().compare(pluginLanguage) &&
		    		!p->getPluginAlgorithmId().compare(algorithmId))
		    	{
		    		return p;
		    	}
		    }
		    std::cout << "WARNING: plugin not found.";
		    return nullptr;
        }  

        void  CCodeGenerator::rmPlugin(std::string pluginName)
        {
            // remove all algorithms of the same plugin
		    for (Plugin* p : this->getPlugins())
		    {
		    	if (!p->getPluginName().compare(pluginName))
		    	{
		    		this->getPlugins().remove(p);
		    	}
		    }
        }

        std::list<Plugin*>  CCodeGenerator::getPlugins()
        {
            return this->plugins;
        }
        // methods for generating header file 
        void  CCodeGenerator::generateHeaderFile(std::string path, Process* proc)
        {
            std::ofstream outHeadFile;
		    //TODO: make sure here
		    std::string tempFileName = proc->getProcName() + ".h";
		    std::string outStr = "";
		    // if def
		    outStr += generateHeaderIfDef(proc);
		    // generate includes 
		    outStr += this->generateCommonIncludes();
		    outStr += this->generateCommunicationIncludes();
		    outStr += this->generateDependIncludes(proc);
		    // generate attrs and methods declaration
		    // attrs
			outStr += this->generateClassPre(proc);
		    for (Attribute* attr : proc->getAttributes()) {
		    	outStr += TAB + this->appendAttrDef(outStr, attr);
		    }
			outStr += "\tpublic: \n";
		    // getters and setters
		    for (Attribute* attr : proc->getAttributes()) {
		    	outStr += TAB + this->appendGetterAndSetter(outStr, attr);
		    }
		    // methods
		    for (Method* m : proc->getMethods()) {
		    	outStr += TAB + this->appendMethodDeclaration(outStr, m);
		    }
			outStr += "};\n";

		    //endif
		    outStr += "#endif\n";
			std::cout << outStr << std::endl;
		    outHeadFile.open(path + "/generatedHeader" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outHeadFile << outStr << std::endl;
		    outHeadFile.close();
        }

		std::string CCodeGenerator::generateClassPre(Process* proc){
			std::string result = "class " + proc->getProcName() + " {" + CR;
			result += "\tprivate: \n";
			return result;
		}

        std::string  CCodeGenerator::generateCommonIncludes()
        {
            std::string commonIncludes =
			"#include <iostream>\n#include <string>\n#include <vector>\n";
		    commonIncludes += INCLUDE_HEADER;
		    return commonIncludes;
        }

        std::string  CCodeGenerator::generateCommunicationIncludes()
        {
			// for real world we use libcap or libnet for the ethernet comm
			// use linux socket for the udp transmission
            std::string communicationIncludes = LOCAL_INCLUDE;
		    return communicationIncludes;
        }

        std::string  CCodeGenerator::generateDependIncludes(Process* currentProc)
        {
            //TODO: make sure here
            std::string dependHeaders = CR;
            /*
		    std::string dependHeaders = CR;
		    for (Process* p : currentProc->getDependProcs()) {
		    	//TODO: add path for process here
		    	std::string headerPath;
		    	dependHeaders += "#include \"" + headerPath + "\\" + p->getProcName() + ".h\" \n";
		    }
            */
            dependHeaders += "#include \"UserType.h\" \n";
		    return dependHeaders;
        }

        std::string  CCodeGenerator::appendAttrDef(std::string inStr, Attribute* attr)
        {
            std::string result = CR;
		    result += attr->getType()->getName() + " " + attr->getIdentifier() + ";" + CR;
		    return result;
        }

        std::string CCodeGenerator::appendGetterAndSetter(std::string inStr, Attribute* attr)
        {
            std::string result = CR;
		    char first[1];
		    first[0] = std::toupper(attr->getIdentifier()[0]);
		    result += attr->getType()->getName() + " get" + first + attr->getIdentifier().substr(1, attr->getIdentifier().size()) + "();" + CR;
		    result += attr->getType()->getName() + " set" + first + attr->getIdentifier().substr(1, attr->getIdentifier().size()) + "(" + attr->getType()->getName() + " " + attr->getIdentifier() + ");" + CR;
		    return result;
        }
        std::string CCodeGenerator::appendMethodDeclaration(std::string inStr, Method* method)
        {
            std::string result = CR;
		    std::string attrStr;
		    int i = 1;
		    for (Attribute* a : method->getParameters()) 
			{
		    	attrStr += a->getType()->getName() + " " + a->getIdentifier();
		    	if (i < method->getParameters().size()) 
				{
		    		attrStr += ", ";
		    	}
		    	i++;
		    }
		    result += method->getReturnType()->getName() + " " + method->getName() + "(" + attrStr + ");" + CR;
		    return result;
        }

        std::string CCodeGenerator::generateHeaderIfDef(Process* proc)
        {
            std::string result = "#ifndef " + proc->getProcName() + "_" + "h" + CR;
		    result += "#define " + proc->getProcName() + "_" + "h" + CR;
            return result;
        }

        // methods for generating src file
        void  CCodeGenerator::generateSrcFile(std::string path, Process* proc)
        {
            //TODO: imple later
            std::string outStr = "";
		    std::ofstream outSrcFile;
		    std::string tempFileName = proc->getProcName() + ".cpp";
			std::cout << "genSrcInclude" << std::endl;
		    outStr += this->generateSrcIncludes(proc);
			outStr += this->generateStateDef(proc);
			std::cout << "genSrcMethod" << std::endl;
		    outStr += this->generateSrcMethods(proc);
			
			std::cout << "genSrcMain" << std::endl;
		    outStr += this->generateMain(proc);

			std::cout << outStr << std::endl;
		    outSrcFile.open(path + "/generatedSrc" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outSrcFile << outStr << std::endl;
		    outSrcFile.close();
        }

        std::string  CCodeGenerator::generateStateDef(Process* proc)
        {
            std::string defs = "";
		    defs += "#define STATE__START__STATE 0\n";
		    int i = 1;
		    for (Vertex* v : proc->getStateMachine()->getVertices()) 
			{
		    	//TODO: refine the state definition later
		    	defs += "#define STATE__" + v->getName() + " " + std::to_string(i) + CR;
		    	i++;
		    }
		    defs += "#define STATE__STOP__STATE " + std::to_string(i) + "\n";
		    return defs;
        }
        
		std::string  CCodeGenerator::generateSrcIncludes(Process* proc)
		{
			//TODO: add path latter
			std::string headerPath;
			std::string srcIncludeStr = "#include \"" + headerPath + ".\\generatedHeader\\" + proc->getProcName() + ".h\"\n";
			return srcIncludeStr;
		}

        std::string  CCodeGenerator::generateSrcMethods(Process* proc)
		{		
			std::string outStr = "";
			for (Method* m : proc->getMethods())
			{
				
				// make sure here, add marker for methods
				
				//TODO: add comm method lib and use interfaces here
			
				
				//TODO: add en/decrypt lib and use interfaces here
				
				std::string rttStr =  m->getReturnType()->getName();
				std::string classNamespace = proc->getProcName() + "::";
				std::string methodName = m->getName();
				std::string attrStr = "(";
				int i = 1;
				for (Attribute* a : m->getParameters()) 
				{
					std::string termStr = a->getType()->getName() + " " + a->getIdentifier();
					attrStr += termStr;
					if (i < m->getParameters().size()) 
					{
						attrStr += ", ";
					}
					i++;
				}
				attrStr += ")";
				std::string methodDef = rttStr + " " + classNamespace + methodName + attrStr;
				std::string returnVal = rttStr + " result;" + CR;
				std::string ret = "return result;\n";
				std::string methodBody = "{\n" + returnVal + ret + "；\n}\n";
				outStr += (methodDef + methodBody);
				
			}
			return outStr;
		}

        std::string CCodeGenerator::generateMain(Process* proc)
		{
			std::string outStr = "";
			// current state 
			outStr += "int __currentState = STATE__START__STATE;\n";
			
			outStr += "int main(int argc, char** argv) {\n";
			outStr += generateSMLoop(proc);
			outStr += "}\n";
			return outStr;
		}

        //std::string  CCodeGenerator::generateGuardVarsDef(Process* proc);
        std::string  CCodeGenerator::generateSMLoop(Process* proc)
		{
			std::string outStr = "";
			outStr += "while(__currentState != STATE__STOP__STATE) {\n";
			outStr += "\tswitch(__currentState){\n";
			//make sure that start state is included
			//TODO
			outStr += this->generateStateBehavior((StateMachine *)proc->getStateMachine());
			outStr += "\t\tdefault: break;\n";
			outStr += "\t}\n";
			outStr += "}\n";

			return outStr;
		}

		std::string CCodeGenerator::generateStateBehavior(StateMachine* sm)
		{
			std::string casesBody;
			std::string caseTab = "\t\t";
			std::string caseBodyTab = "\t\t\t";
			for(Vertex* v : sm->getVertices()){
				
				std::cout << "vertex " + v->getName() << std::endl;
				casesBody += (caseTab + "STATE__" + v->getName() + ":") + CR;
				bool elseIf = false;
				for(Edge* e : sm->getEdges()){
					std::cout << "edge loop" << std::endl;
					if(!e->getFromVertex()->getName().compare(v->getName())){
						// if the edge starts from v
						// makesure Make sure guard to string method
						std::cout << "here" << std::endl;
						casesBody += (caseBodyTab + (elseIf ? "else if(" : "if(") + e->getGuard()->to_string() + "){") + CR;
						elseIf = true;
						for(Action* a : e->getActions()){
							casesBody += TAB + (caseBodyTab + a->to_string() + ";") + CR;
						}
						casesBody += (caseBodyTab + "}") + CR;
					}
					
					std::cout << "edge loop end" << std::endl;
				}
			}
			std::cout << "endGenStateBehave" << std::endl;
			return casesBody;
		}
        /*-------------Generate UserTypes-------------*/
		
		std::string CCodeGenerator::generateUserTypes(std::string path, Model* model)
		{
			std::ofstream outUserTypeFile;
		    //TODO: make sure here
		    std::string fileName = "UserType.h";
		    std::string outStr = "";
			for(UserType* u : model->getUserTypes()){
				//make sure 
				outStr += ("class " + u->getName() + "{") + CR;
				outStr += "\tpublic:\n";
				for(Attribute* a : u->getParameters()){
					outStr += "\t\t" + (a->getType()->getName() + " " + a->getIdentifier()) + "\n";
				}
				outStr += "};\n";
			}
			outUserTypeFile.open(path + "\\" + fileName);
			outUserTypeFile << outStr << std::endl;
			outUserTypeFile.close();
		}

		/*---------Gen---------*/
        void  CCodeGenerator::generateCode(std::string path, Process* proc){
			this->generateHeaderFile(path, proc);
			this->generateSrcFile(path, proc);
			//TODO: this->generateUserTypes(path, proc);
		}

        //constructors
         CCodeGenerator::CCodeGenerator(/*args*/)
         {

         }

         CCodeGenerator::~CCodeGenerator()
         {

         }
    
}
