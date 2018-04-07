    //
//  OrderPublisher.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/24/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "subject.hpp"
#include <iostream>
//#include "CustomerOrder.hpp"
#include "Customer.hpp"
#include <vector>
#include <map>

void OrderPublisher::addObserver(Observer *observer)
{
    observerViews.push_back(observer);
}

void OrderPublisher::setQuantity(string customerName, string orderId, map<string, int> items)
{
    notifyAll(customerName, orderId, items);
}

//int OrderPublisher::getVal()
//{
//    return value;
//}

void OrderPublisher::notifyAll(string customerName, string orderId, map<string, int> items)
{
    for (int i = 0; i < observerViews.size(); i++)
        observerViews[i]->update(customerName, orderId, items);
}

