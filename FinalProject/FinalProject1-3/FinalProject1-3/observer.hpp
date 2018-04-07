//
//  observer.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/24/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef observer_hpp
#define observer_hpp

#include <stdio.h>
//#include "database.hpp"
#include "subject.hpp"
#include <vector>
#include <map>
using namespace std;
class OrderPublisher;

class Observer
{
public:
    OrderPublisher *op;
    Observer(OrderPublisher*);
    virtual void update(string, string, map<string, int>) = 0;
    OrderPublisher *getPublisher();
};

class InventoryObserver:public Observer
{
    public:
    //Database *dataBase = Database::getInstance();
    void update(string, string, map<string, int>);
    InventoryObserver(OrderPublisher* );
};

class PurchaseObserver:public Observer
{
public:
    //OrderPublisher *publisher;
    PurchaseObserver(OrderPublisher*);
    void update(string, string, map<string, int>);
};

class PurchaseOrder
{
public:
    PurchaseOrder(map<string, int>);
};

class NotifyCustomerObserver:public Observer
{
public:
    NotifyCustomerObserver(OrderPublisher*);
    void update(string, string, map<string, int>);
};

class CarBuilderObserver:public Observer
{
public:
    CarBuilderObserver(OrderPublisher*);
    void update(string, string, map<string, int>);
    
};

#endif /* observer_hpp */
