//
//  Inventory.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "Inventory.hpp"
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

void Inventory::track()
{
    /*
     for now this function will display and output the current data time month and year to a file. change it later
     This will use the database
     */
    ofstream day ("day.txt");
    struct tm *now;
    day << "Date: " << now->tm_mon << "/" << now->tm_mday << " " << now->tm_year << endl;
    day << "Time: " << now->tm_hour << ":" << now->tm_min << endl;
    
    
    string status[10] = {"Order Received","Constructing","Delayed","Cancelled", "Out for delivery","Ready for pickup"};
}
