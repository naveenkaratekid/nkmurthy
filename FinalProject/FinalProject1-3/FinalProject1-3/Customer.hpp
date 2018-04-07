//
//  Customer.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef Customer_hpp
#define Customer_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
/*#include "CarDirector.hpp"
#include "Engine.hpp"
#include "CustomerItem.hpp"
#include "StyleOfCar.hpp"
#include "Transmission.hpp"
#include "Materials.hpp"
#include "CustomerOrder.hpp"
#include "Inventory.hpp"
#include "OrderDetails.hpp"*/


using namespace std;

class Customer // customer information
{
public:
    Customer();
    string customerName, emailAddress, homeAddress, style;
    int phoneNumber;
    
    /*
     input deals with the customer entering their details: name, phone number, email, home address, and the program will output their data to a file as well as print a confirmation number for their order
     */
    void summary(string, string, string, int);
};


#endif /* Customer_hpp */
