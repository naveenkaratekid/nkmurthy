//
//  CustomerOrder.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "CustomerOrder.hpp"
#include "CustomerItem.hpp"

using namespace std;

CustomerOrder::CustomerOrder()
{
   
    
}
void CustomerOrder::createOrder(Customer *c, CustomerItem *ci)
{
    customer = c;
    customerItem = ci;
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string confirmation;
    int length = 5;
    confirmation.resize(length);
    
    // srand is for generating random (ints, strings, chars, etc)
    srand(time(NULL));
    for (int i = 0; i < length; i++)
        confirmation[i] = characters[rand() % characters.length()];
    confirmationNum = confirmation;
    
    time_t time1;
    time (&time1);
    orderDate = localtime(&time1);
    statusOfOrder = 0;
    cout << "orderDate is: " << orderDate << endl;
}
