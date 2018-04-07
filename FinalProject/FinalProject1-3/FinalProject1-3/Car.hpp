//
//  Car.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef Car_hpp
#define Car_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
/*#include "Customer.hpp"
#include "CarDirector.hpp"
#include "Engine.hpp"
#include "CustomerItem.hpp"
#include "StyleOfCar.hpp"
#include "Transmission.hpp"
#include "Materials.hpp"
#include "CustomerOrder.hpp"
#include "Inventory.hpp"
#include "OrderDetails.hpp"*/

using namespace std;

class Car
{
public:
    string engine, transmission, exterior, interior, powerTrain;
    Car();
   
    // getters
    string getEngine();
    string getTransmission();
    string getExterior();
    string getInterior();
    string getPowerTrain();
    
    // setters
    void setEngine(string);
    void setTransmission(string);
    void setExterior(string);
    void setInterior(string);
    void setPowerTrain(string);
};



#endif /* Car_hpp */
