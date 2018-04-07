//
//  Transmission.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef Transmission_hpp
#define Transmission_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "StyleOfCar.hpp"

using namespace std;

class Transmission
{
    
    Transmission();
    string transmission[3] = {"Manual", "CVT", "Automatic"};
};

#endif /* Transmission_hpp */
