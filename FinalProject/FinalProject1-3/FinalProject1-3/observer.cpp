//
//  observer.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/24/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "observer.hpp"
#include "Customer.hpp"
#include <iostream>
#include "database.hpp"
#include "CarDirector.hpp"
using namespace std;

Observer::Observer(OrderPublisher *s)
{
    op = s;
    op->addObserver(this);
    
}

OrderPublisher* Observer::getPublisher()
{
    return op;
}

InventoryObserver::InventoryObserver(OrderPublisher *s): Observer(s)
{
    
}

void InventoryObserver::update(string customerName, string orderId, map<string, int> items)
{
    Database *db = Database::getInstance();
    string status = db->getCustomerOrderStatus(orderId);
    if (status == "OrderReceived")
    {
        db->updateInventory(items, "-");
    }
    
}


PurchaseObserver::PurchaseObserver(OrderPublisher *pub): Observer(pub)
{
    //this->publisher = pub;
    //publisher->addObserver(this);
}

PurchaseOrder::PurchaseOrder(map<string, int> items)
{
    
}

void PurchaseObserver::update(string customerName, string orderId, map<string, int> items)
{
    //string q1, it1;
    PurchaseOrder *po;
    // it2 represents quantity in inventory database: how much of a particular item there is in stock
    po = new PurchaseOrder(items);
    string status = Database::getInstance()->getCustomerOrderStatus(orderId);
    if (status == "OrderReceived")
    {
        Database::getInstance()->createPurchaseOrder(orderId, items);
    }
}

NotifyCustomerObserver::NotifyCustomerObserver(OrderPublisher *s): Observer(s)
{
    
}

void NotifyCustomerObserver::update(string customerName, string orderId, map<string, int> items)
{
    string status = Database::getInstance()->getCustomerOrderStatus(orderId);
    if(status == "Delayed")
    {
        cout << "Notifying " << customerName << " that order " << orderId << " is delayed. Pushing back delivery date" << endl;
    }
    else if(status == "ReadyForPickup")
    {
        cout << "Notifying " << customerName << " that order " << orderId << " is ready for pickup." << endl;
    }
    else
    {
        cout << "Order " << orderId << " is proceeding as planned. No need to notify customer" << endl;
    }
}

CarBuilderObserver::CarBuilderObserver(OrderPublisher *op): Observer(op)
{
    
}

void CarBuilderObserver::update(string customerName, string orderId, map<string, int> items)
{
    CarDirector *cd = new CarDirector;
    CarBuilder *cb = new CarBuilder;
    CustomerItem *ci;
    string status = Database::getInstance()->getCustomerOrderStatus(orderId);
    if(status == "Constructing")
    {
        ci = Database::getInstance()->getCustomerCarOrderInfo(orderId);
        cout << "Building the car for order " << orderId << "." << endl;
        cd->setCarBuilder(cb);
        cd->buildCar(ci->getEngine(), ci->getPowerTrain(), ci->getTransmission(), ci->getExterior(), ci->getInterior());
        Car *c = cd->getCar();
        cout << "Engine: " << c->getEngine() << endl;
        cout << "Transmission: " << c->getTransmission() << endl;
        cout << "Powertrain: " << c->getPowerTrain() << endl;
        cout << "Exterior: " << c->getExterior() << endl;
        cout << "Interior: " << c->getInterior() << endl;
        
    }
    else if (status == "Delayed") {
        Database::getInstance()->checkInventoryAndStartBuilding(orderId, items);
    }
}
