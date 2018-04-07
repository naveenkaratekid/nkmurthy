//
//  CustomerItem.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef CustomerItem_hpp
#define CustomerItem_hpp

#include <stdio.h>
#include "Car.hpp"
#include <iostream>
#include "StyleOfCar.hpp"
#include "CustomerItem.hpp"
using namespace std;

class CustomerItem
{
public:
    CustomerItem(string, string, string, string);
    StyleOfCar *st = new StyleOfCar;
    string styleCar, carTransmission, powertrain, engine, exterior, interior;
    
    void storeDetails(string, string, string, string);
    void setStyleOfCar(string);
    void setPowerTrain(string);
    void setEngine(string);
    void setTransmission(string);
    void setExterior(string);
    void setInterior(string);
    
    
    string getEngine();
    string getStyleOfCar();
    string getPowerTrain();
    string getTransmission();
    string getExterior();
    string getInterior();
};


#endif /* CustomerItem_hpp */
