//
//  CarBuilder.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "CarBuilder.hpp"
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

CarBuilder::CarBuilder()
{
    c = new Car();
}

void CarBuilder::buildEngine(string eng)
{
    c->setEngine(eng);
}

void CarBuilder::buildExterior(string ext)
{
    c->setExterior(ext);
}

void CarBuilder::buildInterior(string int1)
{
    c->setInterior(int1);
}

void CarBuilder::buildTransmission(string trans)
{
    c->setTransmission(trans);
}

void CarBuilder::buildPowerTrain(string powerTrain)
{
    c->setPowerTrain(powerTrain);
}

Car *CarBuilder::getCar()
{
    return c;
}


