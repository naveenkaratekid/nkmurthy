//
//  Car.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//


#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "Car.hpp"
#include "CarDirector.hpp"
#include "CarBuilder.hpp"

using namespace std;

CarDirector::CarDirector()
{
    
}

void CarDirector::setCarBuilder(CarBuilder *carBuilder)
{
    cb = carBuilder;

}

Car *CarDirector::getCar()
{
    return cb->getCar();
}

void CarDirector::buildCar(string engine, string powerTrain, string transmission, string exterior, string interior)
{
    cb->buildEngine(engine);
    cb->buildTransmission(transmission);
    cb->buildExterior(exterior);
    cb->buildInterior(interior);
    cb->buildPowerTrain(powerTrain);
}

