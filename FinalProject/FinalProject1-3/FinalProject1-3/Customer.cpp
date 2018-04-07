//
//  Customer.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "Customer.hpp"
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
Customer::Customer()
{
    customerName = "";
    emailAddress = "";
    phoneNumber = 0;
    homeAddress = "";
    style = "";
}
void Customer::summary(string name, string email, string home, int phone)
{
        string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        string confirmation;
        int length = 5;
        confirmation.resize(length);
        
        // srand is for generating random (ints, strings, chars, etc)
        srand(time(NULL));
        for (int i = 0; i < length; i++)
            confirmation[i] = characters[rand() % characters.length()];
        
        ofstream info;
        /*cout << "Enter your name: " << endl;
         cin >> customerName;
         cout << endl;
         cout << "Enter your phone number: " << endl;
         cin >> phoneNumber;
         cout << endl;
         cout << "Enter your email address: " << endl;
         cin >> emailAddress;
         cout << endl;
         cout << "Enter your home address: " << endl;
         cin >> homeAddress;
         cout << endl;*/
    customerName = name;
    emailAddress = email;
    homeAddress = home;
    phoneNumber = phone;
    
        info << "Name: " << name << endl << "Phone Number: " << phone << endl << "Email: " << email << endl << "Address: " << home << endl;
        info << "Confirmation Number: " << confirmation << endl;
    
        
    }
