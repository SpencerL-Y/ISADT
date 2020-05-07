//
//  InitialKnowledge.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_InitialKnowledge_hpp
#define Model_InitialKnowledge_hpp 
#include "../Process/Process.hpp"

namespace isadt {
    class InitialKnowledge {
    public:
        InitialKnowledge();
        InitialKnowledge(Process* process, Attribute* attribute);
    private:
        Process* process_;
        Attribute* attribute_;
    };
}

#endif /* Model_InitialKnowledge_hpp */
