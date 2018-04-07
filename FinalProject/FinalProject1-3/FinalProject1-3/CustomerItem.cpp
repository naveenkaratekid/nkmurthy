//
//  CustomerItem.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "CustomerItem.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include <sqlite3.h>

using namespace std;

CustomerItem::CustomerItem(string style, string carPowerTrain, string carEngine, string transmission)
{
    styleCar = style;
    powertrain = carPowerTrain;
    engine = carEngine;
    carTransmission = transmission;
}

void CustomerItem::storeDetails(string style, string carPowerTrain, string carEngine, string transmission)
{
    // carPowerTrain: gas, electric, hybrid
    map<string, string> details;
    details.insert(pair<string, string>("Style of Car", style));
    details.insert(pair<string, string>("Power Train", carPowerTrain));
    details.insert(pair<string, string>("Engine", carEngine));
    details.insert(pair<string, string>("Transmission", transmission));
    
    ofstream carDetails ("specs.txt");
    for(map<string, string>::iterator it = details.begin(); it != details.end(); it++)
    {
        carDetails << it->first << " " << it->second << endl;
    }
}

void CustomerItem::setEngine(string eng)
{
    engine = eng;
}

void CustomerItem::setPowerTrain(string pT)
{
    powertrain = pT;
}

void CustomerItem::setStyleOfCar(string styleOfCar)
{
    styleCar = styleOfCar;
}

void CustomerItem::setTransmission(string transmission)
{
    carTransmission = transmission;
}

void CustomerItem::setExterior(string ext)
{
    exterior = ext;
}

void CustomerItem::setInterior(string intr)
{
    interior = intr;
}

string CustomerItem::getEngine()
{
    return engine;
}
string CustomerItem::getPowerTrain()
{
    return powertrain;
}
string CustomerItem::getStyleOfCar()
{
    return styleCar;
}
string CustomerItem::getTransmission()
{
    return carTransmission;
}

string CustomerItem::getExterior()
{
    return exterior;
}
string CustomerItem::getInterior()
{
    return interior;
}

