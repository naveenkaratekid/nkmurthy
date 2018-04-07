//
//  Engine.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Engine
{
public:
    Engine();
    string gasoline = "Gasoline", electric = "Electric", hybrid = "Hybrid";
    string v4 = "V4", v6 = "V6", v8 = "V8", v12 = "V12";
    void addEngine();
    
};
#endif /* Engine_hpp */
