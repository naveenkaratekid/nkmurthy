//
//  CarBuilder.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef CarBuilder_hpp
#define CarBuilder_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "Car.hpp"

using namespace std;
//class Car;
class CarBuilder
{
public:
    Car *c;
    CarBuilder();
    void buildEngine(string);
    void buildTransmission(string);
    void buildExterior(string);
    void buildInterior(string);
    void buildPowerTrain(string);
    
    Car *getCar();

};
#endif /* CarBuilder_hpp */
