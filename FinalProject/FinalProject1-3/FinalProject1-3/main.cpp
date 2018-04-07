//
//  main.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "Customer.hpp"
#include "CarDirector.hpp"
#include "Engine.hpp"
#include "CustomerItem.hpp"
#include "StyleOfCar.hpp"
#include "Transmission.hpp"
#include "Materials.hpp"
#include "CustomerOrder.hpp"
#include "Inventory.hpp"
#include "OrderDetails.hpp"
#include "database.hpp"
#include "observer.hpp"
#include <sqlite3.h>
#include <thread>

/*
 
 notification: get the part where the customer is notified (not necessarily emailed. Simple print statement on the console is fine)
 fix use case diagram (draw rectangle around the circles
 
 */

using namespace std;
enum statusOfPurchaseOrder {open, received, inTransit, delivered, closed};
// in database, make enum for status of purchase order (2 = Order Received 4; closed)

void changeCustomerOrderStatus(string orderId, string status)
{
    status = Database::getInstance()->getCustomerOrderStatus(orderId);
    
    if(status != "Delayed")
    {
        if(status == "OrderReceived")
        {
            status = "Constructing";
            cout << "Order " << orderId << " is in construction" << endl;
        }
        else if(status == "Constructing")
        {
            status = "NearCompletion";
            cout << "Order "<< orderId << " is almost finished" << endl;
        }
        else if(status == "NearCompletion")
        {
            status = "ReadyForPickup";
            cout << "Order " << orderId << " is ready for pickup." << endl;
        }
        else if (status == "ReadyForPickup")
        {
            status = "Closed";
            cout << "Payment has been received. Order " << orderId << " is closed" << endl;
        }
        
        Database::getInstance()->updateCustomerOrder(orderId, status);
    }
    
    //Database::getInstance()->updateCustomerOrder(orderId, status);
}

void fulfillCustomerOrderThread()
{
    OrderPublisher *op = new OrderPublisher;
    InventoryObserver *obs = new InventoryObserver(op);
    PurchaseObserver *purchaseObserver = new PurchaseObserver(op);
    NotifyCustomerObserver *nco = new NotifyCustomerObserver(op);
    CarBuilderObserver *cbo = new CarBuilderObserver(op);
    while(true)
    {
        cout << "Processing customer's order" << endl;
        Database *db = Database::getInstance();
        vector<vector<string>> result = db->getOpenCustomerOrders();
        if(result.size() == 0)
        {
            cout << "No open customer orders to process" << endl;
            cout << "Sleeping for 30 minutes" << endl;
            //sqlite3_sleep(15000);
            break;
        }
        else
        {
            string customerName = " ";
            string vendor = " ";
            string time = " ";
            string confirmationNumber = " ";
            string status = " ";
            string orderId = " ";
            int column = 0;
            vector<vector<string>>::iterator it;
            vector<string>::iterator it1;
            for(it = result.begin(); it!= result.end(); it++)
            {
                column = 0;
                for(it1 = (*it).begin();it1!=(*it).end();++it1)
                {
                    switch(column)
                    {
                        case 0:
                            customerName = (*it1);
                            break;
                        case 1:
                            orderId = (*it1);
                            break;
                        case 2:
                            confirmationNumber = (*it1);
                            break;
                        case 3:
                            time = (*it1);
                            break;
                        case 4:
                            status = (*it1);
                            break;
                        default:
                            break;
                    }
                    //cout << "Col: " << column << endl;
                    column++;
                    
                }
                map<string, int> items = db->getCustomerOrderMaterialSpecs(orderId);
                op->setQuantity(customerName, orderId, items);
                changeCustomerOrderStatus(orderId, status);
            }
            //map<string, int> items = db->getCustomerOrderMaterialSpecs(orderId);
            //op->setQuantity(customerName, orderId, items);
            //changeCustomerOrderStatus(orderId, status);
            // method to change customer order status. dont update status if delayed
        }
        sqlite3_sleep(20000);
    }
    /*
     
     create orderPublisher (similar to subject)
     create carBuilderObserver
     create notifyCustomerObserver // both should go in observer file
     
     while true
     
     db->getOpenCustomerOrders();
     iterate through results vector
     for each row, get next status based on current status
     
     
     */
}



void fulfillPurchaseOrderThread()
{
    while (true)
    {
        cout << "Processing Purchase Orders......" << endl;
        sqlite3_sleep(15000);
        Database *db = Database::getInstance();
        vector<vector<string>> result = db->getOpenPurchaseOrders();
        if(result.size() == 0)
        {
            cout << "No open orders to process" << endl;
            cout << "Sleeping for 30 minutes" << endl;
            //sqlite3_sleep(15000);
            break;
        }
        else
        {
            vector<vector<string>>::iterator it;
            vector<string>::iterator it1;

            string itemName = " ", vendor = " ";
            string time = " ";
            string status = " ";
            int orderAmount = 0;
            string orderId = " ";
            int column = 0;
            for(it = result.begin(); it != result.end(); it++)
            {
                column = 0; // reset column count to 0 after going through each row
                // create enum for status for thread
                
                for(it1 = (*it).begin();it1!=(*it).end();++it1)
                {
                    switch(column)
                    {
                        case 0:
                            orderId = (*it1);
                            break;
                        case 1:
                            itemName = (*it1);
                            break;
                        case 2:
                            vendor = (*it1);
                            break;
                        case 3:
                            orderAmount = stoi(*it1);
                            break;
                        case 4:
                            time = (*it1);
                            break;
                        case 5:
                            status = (*it1);
                            break;
                        default:
                            break;
                    }

                    //cout << "Col: " << column << endl;
                    column++;
                }
                    cout << itemName << " is low on stock. Reordering" <<endl;
                    /*cout << "Vendor: " << vendor << endl;
                    cout << "Amount Ordered: " << orderAmount << endl;
                    cout << "Time Ordered: " << time << endl;
                    cout << "Order Id: " << orderId << endl;*/
                
                // if status = open, set status to received
                // if status = received, set new status to transit
                // if status = transit, set new status to delivered
                // if status = delivered, set status to closed
                if(status == "open")
                {
                    status = "received";
                    cout << "PurchaseOrder " << orderId << " is received" << endl;
                }
                else if(status == "received")
                {
                    status = "inTransit";
                    cout << "PurchaseOrder " << orderId << " is in Transit" << endl;
                }
                else if(status == "inTransit")
                {
                    status = "delivered";
                    cout << "PurchaseOrder " << orderId << " is delivered" << endl;
                }
                else if (status == "delivered")
                {
                    status = "closed";
                    cout << "PurchaseOrder " << orderId << " is closed" << endl;
                    map<string,int> items;
                    items.insert(pair<string,int>(itemName, orderAmount));
                    db->updateInventory(items, "+");
                }
                db->updatePurchaseOrder(orderId, status, itemName);
            }
        }
        cout << "Sleeping for 15 seconds" << endl;
        sqlite3_sleep(15000);
        
    }
    cout << "exiting loop from process purchase order" << endl;
}

void processLine(string line, char delimiter)
{
    string t;
    istringstream str;
    while(str)
    {
        if(!getline(str, t, delimiter))
        {
            break;
        }
    }
}


int main(void)
{
    Customer *c = new Customer;
    CustomerItem *ci;// = new CustomerItem;
    CustomerOrder *co;
    string carType[9] = {"Sub Compact", "Compact", "Midsize", "Fullsize", "Compact SUV", "Midsize SUV", "Fullsize SUV", "Pickup Truck", "Convertible"};
    //CarBuilder *cb = new CarBuilder;
    /*OrderPublisher *op = new OrderPublisher;
    InventoryObserver *obs = new InventoryObserver(op);
    PurchaseObserver *purchaseObserver = new PurchaseObserver(op);*/
    ofstream orderDetails, info;
    ifstream stock ("inventory.csv");
    string line;
    map<string, int> items;
    // the code below deals with the builder taking in their specs
    string power, engine, answer, transmission;
    string style;
    string stringPhoneNumber = to_string(c->phoneNumber);
    
    //thread t2 = thread(fulfillCustomerOrderThread);
    //t2.join();
    
    cout << "Enter your first name: " << endl;
    getline(cin, c->customerName);
    cout << "Name: " << c->customerName << endl;
    
    cout << "Email: " << endl;

    getline(cin, c->emailAddress);
    
    cout << "Email: " << c->emailAddress << endl;
    
    cout << "Home address: " << endl;
    
    getline(cin, c->homeAddress);
    cout << "Address: " << c->homeAddress << endl;
    
    cout << "Phone Number: " << endl;
   
    getline(cin, stringPhoneNumber);
    cout << "Number: " << stringPhoneNumber << endl;
    cout << endl;
    
    cout << "Welcome " << c->customerName << "!" << endl << "We are your #1 source for creating a custom car tailored to your needs." << endl;
    cout << endl;
    
    cout << "Please enter your style of car you would prefer (Sub Compact, Compact, Midsize, Fullsize, Compact SUV, Midsize SUV, Fullsize SUV, Pickup Truck, Convertible): " << endl;
    getline(cin , style);
    bool isValidStyle = true;
    for(int i = 0; i < style.length()/*(sizeof(carType) / sizeof(carType[0]))*/; i++)
    {
        if((style.compare(carType[i])) == 0)
        //if(style == carType[i])
        {
            isValidStyle = true;
            break;
        }
        else
        {
            isValidStyle = false;
        }
    }
    if(isValidStyle == false)
    {
        cout << "Invalid choice" << endl;
        exit(0);
    }
    cout << "Style: " << style << endl;
    /*if(style.find("Sub Compact") || style.find("Compact") || style.find("Midsize") || style.find("Fullsize") || !style.find("Compact SUV")|| style.find("Midsize SUV")||style.find("Fullsize SUV")|| style.find( "Pickup Truck")|| style.find("Convertible"))
    {
        cout << "Your style: " << style << endl;
        
    }
    else
    {
        cout << "Invalid choice";
        exit(0);
    }*/
    //cout << "Your style: " << style << endl;
    
    cout << "Enter what type of power you would like (Electric, Gas): ";
    cin >> power;
    if(power == "Gas" || power == "gas")
    {
        
        cout << "Choose from these engines: (V4, V6, V8, V12): " << endl;
        cin >> engine;
        //cb->buildEngine(engine);
        items.insert(pair<string, int>(engine + " Gas", 1));
        cout << "Do you want to add an electric battery and convert this vehicle into a hybrid?" << endl; // standard hybrid only
        cin >> answer;
        if(answer == "yes")
        {
            power = "Hybrid";
            cout << "Your vehicle is now a hybrid!" << endl;
            items.insert(pair<string, int>("Electric Battery", 1));
        }
    }
    else if (power == "Electric" || power == "electric")
    {
        cout << "electric" << endl;
        items.insert(pair<string, int>("Electric Battery", 1));
        cout << "Do you want to add a gas generator and convert this into a hybrid?" << endl;
        cin >> answer;
        if(answer == "yes" || answer == "y")
        {
            power = "Hybrid";
            cout << "Your vehicle is now a hybrid!" << endl;
            
            cout << "Choose from these engines: (V4, V6, V8, V12): " << endl;
            cin >> engine;
            //cb->buildEngine(engine);
            items.insert(pair<string, int>(engine + " Gas", 1));
        }
    }
    else
    {
        cout << "Invalid source of powertrain" << endl;
        exit(0);
    }
    cout << "";
    
    cout << "What kind of transmission would you like in your car? (CVT (continuously variable), automatic, manual)" << endl;
    cin.ignore();
    getline(cin,  transmission);
    if(transmission == "manual" || transmission == "Manual")
    {
        transmission = "6 Speed Manual";
    }
    else if(transmission == "automatic" || transmission == "Automatic")
    {
        transmission = "9 Speed Automatic";
    }
    
    else if(transmission == "CVT" || transmission == "cvt")
    {
        transmission = "CVT";
    }
    else
    {
        cout << "Invalid transmission" << endl;
        exit(0);
    }
    //cb->buildTransmission(transmission);
    items.insert(pair<string, int>(transmission + " Transmission", 1));
    
    ci = new CustomerItem(style, power, engine, transmission);
    co = new CustomerOrder();
    c->summary(c->customerName, c->emailAddress, c->homeAddress, c->phoneNumber);
    co->createOrder(c, ci);
    //ci->storeDetails(style, power, engine, transmission);
    Database *db = Database::getInstance();
    db->saveCustomerInfo(c);
    
    db->saveCustomerOrderInfo(co);
    db->saveCustomerCarSpecs(ci, to_string(co->orderID));
    string interiorSeatMaterial;
    string interiorCabinMaterial;
    string exteriorCarMaterial;
    string typeOfWheel;
    string brakes; // typeOfWheel: steel wheels, alloy wheels
    int numOfSeats = 0;
    
    cout << "What material would you like for your exterior (Bulletproof Steel, Steel, Iron, Bulletproof Iron)?" << endl;
    //cin.ignore();
    getline(cin, exteriorCarMaterial);
    if(exteriorCarMaterial == "bulletproof steel" || exteriorCarMaterial == "Bulletproof Steel")
    {
        exteriorCarMaterial = "Bulletproof Steel";
    }
    else if(exteriorCarMaterial == "bulletproof iron" || exteriorCarMaterial == "Bulletproof Iron")
    {
        exteriorCarMaterial = "Bulletproof Iron";
    }
    else
    {
        cout << "Invalid exterior material" << endl;
        exit(0);
    }
    cout << "Your exterior material: " << exteriorCarMaterial << endl;
    //cb->buildExterior(exteriorCarMaterial);
    items.insert(pair<string, int>(exteriorCarMaterial + " Exterior", 1));
    
    
    cout << "What kind of wheels would you like (Steel Wheels, (18, 20, 22, 24) inch Alloy Wheels?" << endl;
    getline(cin, typeOfWheel);
    if(typeOfWheel == "18")
    {
        typeOfWheel = "18 inch Alloy";
    }
    else if(typeOfWheel == "20")
    {
        typeOfWheel = "20 inch Alloy";
    }
    
    else if(typeOfWheel == "22")
    {
        typeOfWheel = "22 inch Alloy";
    }
    
    else if(typeOfWheel == "24")
    {
        typeOfWheel = "24 inch Alloy";
    }
    else if(typeOfWheel == "basic" || typeOfWheel == "Basic" || typeOfWheel == "cheapest" || typeOfWheel == "Cheapest")
    {
        typeOfWheel = "Steel";
    }
    else
    {
        cout << "Invalid wheel choice" << endl;
        exit(0);
    }
    
    cout << "Your wheel choice: " << typeOfWheel << " Wheels" << endl;
    
    items.insert(pair<string, int>(typeOfWheel + " Wheels", 4));
    
    cout << "What kind of brakes would you like? (Drum, (10, 15, 20) inch Solid Disc)" << endl;
    //cin >> brakes;
    getline(cin, brakes);
    
    if(brakes == "10" || brakes == "10 inch")
    {
        brakes = "10 inch Solid Disc";
    }
    else if(brakes == "15" || brakes == "15 inch")
    {
        brakes = "15 inch Solid Disc";
    }
    else if(brakes == "20" || brakes == "20 inch")
    {
        brakes = "20 inch Solid Disc";
    }
    else if(brakes == "basic" || brakes == "Basic" || brakes == "cheapest" || brakes == "Cheapest")
    {
        brakes = "Drum";
    }
    else
    {
        cout << "Invalid brake choice" << endl;
        exit(0);
    }
    cout << "Brakes: " << brakes << " Brakes" << endl;
    items.insert(pair<string, int>(brakes + " Brakes", 4));
    
    
    cout << "How many seats would you like in your " << style << "?" << endl;
    cin >> numOfSeats;
    cout << "Your number of seats: " << to_string(numOfSeats) << " seats" << endl;
    
    cout << "What kind of seats would you like? (Leather, Cloth)" << endl;
    cin.ignore();
    getline(cin, interiorSeatMaterial);
    cout << endl;
    if(interiorSeatMaterial == "Leather" || interiorSeatMaterial == "leather" || interiorSeatMaterial == "premium" || interiorSeatMaterial == "Premium")
    {
        interiorSeatMaterial = "Leather";
    }
    else if(interiorSeatMaterial == "cloth" || interiorSeatMaterial == "basic" || interiorSeatMaterial == "Basic" || interiorSeatMaterial == "cheapest" || interiorSeatMaterial == "Cheapest")
    {
        interiorSeatMaterial = "Cloth";
    }
    else if(interiorSeatMaterial == "Nappa" || interiorSeatMaterial == "nappa" || interiorSeatMaterial == "Nappa Leather" || interiorSeatMaterial == "nappa leather")
    {
        interiorSeatMaterial = "Nappa Leather";
    }
    else
    {
        cout << "Invalid seat material" << endl;
        exit(0);
    }
    cout << "Your seat material: " << interiorSeatMaterial << endl;
    items.insert(pair<string, int>(interiorSeatMaterial + " Seats", numOfSeats));
    
    
    cout << "Choose an interior cabin material (Real Rose Wood, Titanium, Leather, Plastic, Aluminum): " << endl;
    getline(cin, interiorCabinMaterial);
    
    if (interiorCabinMaterial == "titan" || interiorCabinMaterial == "titanium" || interiorCabinMaterial == "Titanium" || interiorCabinMaterial == "Titan")
    {
        interiorCabinMaterial = "Titanium";
    }
    
    else if(interiorCabinMaterial == "leather" || interiorCabinMaterial == "Leather")
    {
        interiorCabinMaterial = "Leather";
    }
    
    else if(interiorCabinMaterial == "Plastic" || interiorCabinMaterial == "plastic" || interiorCabinMaterial == "cheapest" || interiorCabinMaterial == "cheapest")
    {
        interiorCabinMaterial = "Plastic";
    }
    
    else if(interiorCabinMaterial == "Silver" || interiorCabinMaterial == "silver" || interiorCabinMaterial == "metallic" || interiorCabinMaterial == "Metallic" || interiorCabinMaterial == "Aluminum" || interiorCabinMaterial == "aluminum")
    {
        interiorCabinMaterial = "Aluminum";
    }
    
    else if(interiorCabinMaterial == "rose" || interiorCabinMaterial == "Rose" || interiorCabinMaterial == "Real Rose Wood" || interiorCabinMaterial == "real rose wood" || interiorCabinMaterial == "wood" || interiorCabinMaterial == "Wood")
    {
        interiorCabinMaterial = "Real Rose Wood";
    }
    else
    {
        cout << "Invalid interior material" << endl;
        exit(0);
    }
    
        cout << "Your interior cabin material: " << interiorCabinMaterial << endl;
    //cb->buildInterior(interiorCabinMaterial);
    items.insert(pair<string, int>(interiorCabinMaterial + " Trim Interior", 1));
    
    
    //db->saveCustomerMaterialSpecs(to_string(co->orderID), to_string(numOfSeats), interiorSeatMaterial, interiorCabinMaterial, exteriorCarMaterial, typeOfWheel, brakes);
    
    db->saveCustomerMaterialSpecs(to_string(co->orderID), items);
    
    //op->setQuantity(items);
    
    
    // worry about features later
    /*vector<string> features;
    string options;
    cout << "Enter what kind of features you would like in your vehicle (enter done when finished): " << endl;
    for(int i = 0; i < features.size(); i++)
    {
        cin.ignore();
        getline(cin, options);
        cout << "You entered: " << options;
        features.push_back(options);
        if(options == "done" || options == "Done")
        {
            break;
        }
    }*/
    
    //while(true)
    //{
        
        thread t1 = thread(fulfillPurchaseOrderThread);
        
        thread t2 = thread(fulfillCustomerOrderThread);
        t1.join();
        t2.join();
             
        //sqlite3_sleep(15000);
    //}*/
    
    
    return 0;
}
