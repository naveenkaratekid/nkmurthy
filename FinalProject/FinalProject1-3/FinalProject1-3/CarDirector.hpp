//
//  Car.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef CarDirector_hpp
#define CarDirector_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
//#include "Customer.hpp"
//#include "CustomerItem.hpp"
//#include "CustomerOrder.hpp"
#include "CarBuilder.hpp"
#include "Car.hpp"


using namespace std;

//class Car;
class CarDirector // this is the director class for builder 
{
    
public:
    CarDirector ();
    //CustomerItem *c;
    //void construct();
    CarBuilder *cb = new CarBuilder;
    // this function will store the customer's choices from user input
    /*void addCustomer(CustomerItem* c)
    {
        //this->c = c;
    }*/
    void buildCar(string engine, string, string transmission, string exterior, string interior);
    /*{
        cb->buildEngine(engine);
        cb->buildTransmission(transmission);
        cb->buildExterior(exterior);
        cb->buildInterior(interior);
    }*/
    void setCarBuilder(CarBuilder*);
    
    Car *getCar();
    /*{
        return cb->getCar();
    }*/
    //Car *createCar();
    
};



#endif /* Car_hpp */
