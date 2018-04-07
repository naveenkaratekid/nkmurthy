//
//  Car.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "Car.hpp"

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

Car::Car()
{
    
}

string Car::getEngine()
{
    return engine;
}

string Car::getExterior()
{
    return exterior;
}

string Car::getTransmission()
{
    return transmission;
}

string Car::getInterior()
{
    return interior;
}

string Car::getPowerTrain()
{
    return powerTrain;
}

void Car::setEngine(string eng)
{
    engine = eng;
}

void Car::setExterior(string ext)
{
    exterior = ext;
}

void Car::setTransmission(string trans)
{
    transmission = trans;
}

void Car::setInterior(string int1)
{
    interior = int1;
}

void Car::setPowerTrain(string power)
{
    powerTrain = power;
}
