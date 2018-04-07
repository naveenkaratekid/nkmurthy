//
//  CustomerOrder.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef CustomerOrder_hpp
#define CustomerOrder_hpp

#include <stdio.h>
#include "Customer.hpp"
#include "CustomerItem.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "subject.hpp"

using namespace std;
//class Customer;
class CustomerOrder
{
public:
    Customer *customer;
    CustomerItem *customerItem;
    //InventoryObserver *obs;
    CustomerOrder();
    int orderID;
    struct tm *orderDate;
    string confirmationNum;
    int statusOfOrder;
    
    void createOrder(Customer*, CustomerItem*);
};

#endif /* CustomerOrder_hpp */
