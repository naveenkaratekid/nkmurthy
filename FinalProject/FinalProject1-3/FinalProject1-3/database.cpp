//
//  database.cpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#include "database.hpp"
#include <iostream>
#include "Customer.hpp"
#include <sstream>
#include "CustomerOrder.hpp"
#include "CustomerItem.hpp"

bool Database::isThereInstance = false;
Database* Database::instance = NULL;

Database::Database(char* filename)
{
    db = NULL;
    open(filename);

}

Database::~Database()
{
    isThereInstance = false;
}

Database* Database::getInstance()
{
    if(!isThereInstance)
    {
        instance = new Database ("db.sqlite");
        isThereInstance = true;
    }
    return instance;
}

bool Database::open(char* f)
{
    if(sqlite3_open(f, &db) == SQLITE_OK)
    {
        return true;
    }
    return false;

}

vector<vector<string>> Database::query(char* q)
{
    sqlite3_stmt *statement;
    vector<vector<string>> results;
    if(sqlite3_prepare_v2(db, q, -1, &statement, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
            if(result == SQLITE_ROW)
            {
                vector<string> values;
                for(int col = 0; col < cols; col++)
                {
                    values.push_back((char*)sqlite3_column_text(statement, col));
                }
                results.push_back(values);
            }
            else
            {
                break;
            }
        }
        sqlite3_finalize(statement);
    }
    string err = sqlite3_errmsg(db);
    if(err != "not an error") cout << q << " " << err << endl;

        return results;
}

void Database::close()
{
    sqlite3_close(db);
}

void Database::saveCustomerInfo(Customer *c)
{
    char* q = "CREATE TABLE customer (customerName VARCHAR(100), customerAddress VARCHAR(255), customerEmail VARCHAR(200), customerPhoneNumber VARCHAR(11));";
    
    string q1 = "INSERT INTO customer VALUES ('" + c->customerName + "','" + c->homeAddress + "','" + c->emailAddress + "','" + to_string(c->phoneNumber) + "');";
    char * q2 = new char [q1.length()+1];
    strcpy (q2, q1.c_str());
    
    query(q);
    query(q2);
    //close();
}

void Database::saveCustomerOrderInfo(CustomerOrder *co)
{
    string orderId;
    struct tm *t;
    time_t rawtime;
    char b [100];
    string status = " ";
    
    time (&rawtime);
    //t = localtime (&rawtime);
    t = co->orderDate;
    
    char* q = "CREATE TABLE customerOrder (customerName VARCHAR(100), orderId VARCHAR(255), confirmationNumber VARCHAR(200), orderDate TEXT(20), status VARCHAR(200));";
    
    query(q);
    strftime (b, 100, "%m-%e-%Y %I:%M%p", t);
    cout << b << endl;
    
    char* q0 = "select max(cast(orderid as integer)) from customerorder;";
    vector<vector<string>> result = query(q0);
    vector<vector<string>>::iterator it;// = find(result.begin(), result.end(), orderId);
    vector<string>::iterator it1;
    int maxOrder = 0;
    for(it = result.begin(); it != result.end(); it++)
    {
        for(it1 = (*it).begin();it1!=(*it).end();++it1)
        {
            //cout<<"max count: " << *it1<<endl;
            maxOrder = stoi(*it1) + 1;
        }
        /*if(maxOrder == result.size())
        {
            cout << "Out of bounds!" << endl;
        }
        maxOrder++; // maxOrder can be a simple counter starting at 0;
        cout << maxOrder << endl;*/
        //maxOrder = distance(result.begin(), it);
    }
    //maxOrder = (find(result.begin(), result.end(), orderId) - result.begin());
    
    string q1 = "INSERT INTO customerOrder VALUES ('" + co->customer->customerName + "','" + to_string(maxOrder) + "','" + co->confirmationNum + "','" + b + "', 'OrderReceived');";
    
   
    char * q2 = new char [q1.length()+1];
    strcpy (q2, q1.c_str());
    
    query(q);
    query(q2);
    co->orderID = maxOrder;
    //close();
}

void Database::saveCustomerCarSpecs(CustomerItem *ci, string orderId)
{
    char* q = "CREATE TABLE customerCarOrderInfo (orderId VARCHAR(100), styleOfCar VARCHAR(200), powerTrain VARCHAR(200), engine VARCHAR(300), transmission VARCHAR(200));";

    
    string q1 = "INSERT INTO customerCarOrderInfo VALUES ('" + orderId + "','" + ci->styleCar + "','" + ci->powertrain + "','" + ci->engine + "','" + ci->carTransmission + "');";
    
    char * q2 = new char [q1.length()+1];
    strcpy (q2, q1.c_str());
    
    query(q);
    query(q2);
    //close();
}


 /*void Database::saveCustomerMaterialSpecs(string orderId, string numberOfSeats, string interiorSeatMaterial, string interiorCabinMaterial, string exteriorMaterial, string typeOfWheel, string brakes)
 {
     char* q = "CREATE TABLE customerMaterialSpecs (orderId VARCHAR(100), numberOfSeats VARCHAR(100), interiorSeatMaterial VARCHAR(255), interiorCabinMaterial VARCHAR(200), exteriorMaterial VARCHAR(20), typeOfWheel VARCHAR(50), brakes VARCHAR(100));";

     string q1 = "INSERT INTO customerMaterialSpecs VALUES ('" + orderId + "','" + numberOfSeats + "','" + interiorSeatMaterial + "','" + interiorCabinMaterial + "','" + exteriorMaterial + "','" + typeOfWheel + "','" + brakes + "');";
 
     char *q2 = new char [q1.length()+1];
     strcpy (q2, q1.c_str());
 
     query(q);
     query(q2);
     //close();
}*/

void Database::saveCustomerMaterialSpecs(string orderId, map<string, int> items)
{
    string q1;
    char* q = "CREATE TABLE customerMaterialSpecs (orderId VARCHAR(100), itemName VARCHAR(100), quantity VARCHAR(200));";
    
    query(q);
    for(map<string, int>::iterator it = items.begin(); it != items.end(); it++)
    {
        //cout << it->first << " " << it->second << endl;
        q1 = "INSERT INTO customerMaterialSpecs VALUES ('" + orderId + "','" + it->first + "','" + to_string(it->second) + "');";
    
        char *q2 = new char [q1.length()+1];
        strcpy (q2, q1.c_str());
    
        query(q2);
        //close();
    }
}


void Database::updateInventory(map<string, int> items, string operation)
{
    //int amount;
    string buffer;
    string q1;
    string it1;
    int it2;
    char *q2;
    for(map<string, int>::iterator it = items.begin(); it != items.end(); it++)
    {
        //cout << it->first << " " << it->second << endl;
        it1 = it->first;
        it2 = it->second;
        q1 = "UPDATE inventory set quantity =  quantity " + operation + to_string(it2) + " where itemName = '" + it1 + "';";
        q2 = new char [q1.length()+1];
        strcpy (q2, q1.c_str());
        query(q2);
    }
}

void Database::updateCustomerOrder(string orderId, string status)
{
    string q1 = "update customerOrder set status = '" + status + "' where orderId = '" + orderId + "' and status !='Delayed';";
    char* q2 = new char[q1.length() + 1];
    strcpy (q2, q1.c_str());
    query(q2);
}

string Database::getCustomerOrderStatus(string orderId)
{
    string q1 = "select status from customerOrder where orderId = '" + orderId + "';";
    char *q2 = new char[q1.length()+1];
    strcpy(q2, q1.c_str());
    vector<vector<string>> result = query(q2);
    vector<vector<string>>::iterator it;
    vector<string>::iterator it1;
    string status = " ";
    for(it = result.begin(); it != result.end(); it++)
    {
        for(it1 = (*it).begin(); it1 != (*it).end(); it1++)
        {
            status = (*it1);
        }
    }
    return status;
}

void Database::resetCustomerOrderStatus(string orderId, string status) {
    string q1 = "update customerOrder set status = '" + status + "' where orderId = '" + orderId + "';";
    char* q2 = new char[q1.length() + 1];
    strcpy (q2, q1.c_str());
    query(q2);
    
}
void Database::checkInventoryAndStartBuilding(string orderId, map<string, int> items)
{
    bool isQtyEnough = true;
    for(map<string, int>::iterator it0 = items.begin(); it0 != items.end(); it0++)
    {
        //cout << it0->first << " " << it0->second << endl;
        string itemName = it0->first;
        int quantity = it0->second;
        int availibleQuantity = 0;
        string q11 = "select quantity from inventory where itemName = '" + itemName + "';";
        char *q5 = new char[q11.length()+1];
        strcpy (q5, q11.c_str());
        vector<vector<string>> result1 = query(q5);
        vector<vector<string>>::iterator it11;
        vector<string>::iterator it12;
        for(vector<vector<string>>::iterator it11 = result1.begin(); it11 != result1.end(); it11++)
        {
            for(it12 = (*it11).begin(); it12!=(*it11).end(); ++it12)
            {
                availibleQuantity = stoi(*it12);
            }
        }
        if(availibleQuantity < quantity)
        {
            isQtyEnough = false;
        }
    }
    
    if (isQtyEnough) {
        resetCustomerOrderStatus(orderId, "Constructing");
    }
}

void Database::createPurchaseOrder(string orderId, map<string, int> items)
{
    //CustomerOrder *co;
    int qty = 100;
    bool isDelayed = false;
    struct tm *t;
    time_t rawtime;
    char b [100];
    cout << "creating purchase order" << endl;
    time (&rawtime);
    t = localtime(&rawtime);
    
    strftime (b, 100, "%m-%e-%Y %I:%M%p", t);
    cout << b << endl;
    char* q = "CREATE TABLE purchaseOrder (orderId VARCHAR(100), itemName VARCHAR(100), vendorName VARCHAR(100), quantity VARCHAR(255), orderDate TEXT(100), status VARCHAR(100));";
    query(q);
    
    for(map<string, int>::iterator it0 = items.begin(); it0 != items.end(); it0++)
    {
        cout << it0->first << " " << it0->second << endl;
        string itemName = it0->first;
        int quantity = it0->second;
        int availibleQuantity = 0;
        int numOfOpenOrders = 0; // number of open orders that are pending
        string q11 = "select quantity from inventory where itemName = '" + itemName + "';";
        char *q5 = new char[q11.length()+1];
        strcpy (q5, q11.c_str());
        vector<vector<string>> result1 = query(q5);
        vector<vector<string>>::iterator it11;
        vector<string>::iterator it12;
        for(vector<vector<string>>::iterator it11 = result1.begin(); it11 != result1.end(); it11++)
        {
            for(it12 = (*it11).begin(); it12!=(*it11).end(); ++it12)
            {
                availibleQuantity = stoi(*it12);
            }
        }
        if(availibleQuantity < 10) // here we are checking if the quantity in the inventory database for a particular item is < 10
        {
            // print
            isDelayed = true;
            cout << itemName << " is low on stock. Checking open orders" << endl;
            string q3 = "select count (*) from purchaseOrder where itemName = '" + itemName + "' and status != 'closed';";
            char *q4 = new char[q3.length()+1];
            strcpy(q4, q3.c_str());
            
            string q1;
            char *q2;
            
            char* q0 = "select max(cast(orderid as integer)) from purchaseorder;";
            vector<vector<string>> result1 = query(q0);
            vector<vector<string>>::iterator it;// = find(result.begin(), result.end(), orderId);
            vector<string>::iterator it1;
            int maxOrder = 0;
            for(it = result1.begin(); it != result1.end(); it++)
            {
                for(it1 = (*it).begin();it1!=(*it).end();++it1)
                {
                    cout<<"max count: " << *it1<<endl;
                    maxOrder = stoi(*it1) + 1;
                }
                /*if(maxOrder == result.size())
                 {
                 cout << "Out of bounds!" << endl;
                 }
                 maxOrder++; // maxOrder can be a simple counter starting at 0;
                 cout << maxOrder << endl;*/
                //maxOrder = distance(result.begin(), it);
            }
            //––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
            // original vector for result of query q4: "select count (*) from purchaseOrder where itemName = '" + itemName + "' and status != 'closed';"
            
            
            vector<vector<string>> result = query(q4);
            vector<vector<string>>::iterator it2;
            vector<string>::iterator it3;
            for(it2 = result.begin(); it2 != result.end(); it2++)
            {
                for(it3 = (*it2).begin();it3!=(*it2).end();++it3)
                {
                    numOfOpenOrders = stoi(*it3); // store the num of pending orders
                }
            }
            if(numOfOpenOrders == 0)
            {
                cout << "Reordering " << qty << " " << itemName << endl;
                q1 = "INSERT INTO purchaseOrder VALUES ('" + to_string(maxOrder) + "','" + itemName + "','" + "vendorname" + "','" + to_string(qty) +  "','" + b + "','" + "open" + "');";
                q2 = new char [q1.length()+1];
                strcpy (q2, q1.c_str());
                query(q2);
            }
            else
            {
                cout << "There are already " << numOfOpenOrders << " pending orders for this item. Will not create order now" << endl;
            }
        }
    }
    if(isDelayed)
    {
        updateCustomerOrder(orderId, "Delayed");
    }
}

vector<vector<string>> Database::getOpenPurchaseOrders()
{
    char* q1 = "select * from purchaseOrder where status != 'closed'";
    
    vector<vector<string>> result = query(q1);
    return result;
}

void Database::updatePurchaseOrder(string orderId, string status, string itemName)
{
    string q1 = "update purchaseOrder set status = '" + status + "' where orderId = '" + orderId + "' and itemName = '" + itemName + "';";
    char *q2 = new char[q1.length() + 1];
    strcpy(q2, q1.c_str());
    query(q2);
}

vector<vector<string>> Database::getOpenCustomerOrders()
{
    char* q1 = "select * from customerOrder where status != 'Closed'";
    
    vector<vector<string>> result = query(q1);
    return result;
}

map<string, int> Database::getCustomerOrderMaterialSpecs(string orderId)
{
    map<string, int> items;
    string q1 = "select itemName, quantity from customerMaterialSpecs where orderId = '" + orderId + "';";
    char *q2 = new char[q1.length() + 1];
    strcpy(q2, q1.c_str());
    string itemName = " ";
    int quantity = 0;
    vector<vector<string>> result = query(q2);
    vector<vector<string>>::iterator it;
    vector<string>::iterator it1;
    int column = 0;
    for(it = result.begin(); it != result.end(); it++)
    {
        column = 0;
        for(it1 = (*it).begin(); it1 != (*it).end(); it1++)
        {
            //items.insert(pair<string, int>(it, stoi(it1)));
            switch(column)
            {
                case 0:
                    itemName = (*it1);
                    break;
                case 1:
                    quantity = stoi(*it1);
                    break;
                default:
                    break;
            }
            column++;
        }
        items.insert(pair<string, int>(itemName, quantity));
    }
    cout << "Items chosen and quantity needed for order " << orderId << ": " << endl;
    for(map<string, int>::iterator it = items.begin(); it != items.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
    return items;
}

bool Database::hasEnding(string const &fullStr, string const &end)
{
    if (fullStr.length() >= end.length()) {
        return (0 == fullStr.compare (fullStr.length() - end.length(), end.length(), end));
    } else {
        return false;
    }
}


CustomerItem *Database::getCustomerCarOrderInfo(string orderId)
{
    string q0 = "select styleOfCar, powerTrain, engine, transmission from customerCarOrderInfo where orderId = '" + orderId + "';";
    char *q1 = new char[q0.length() + 1];
    CustomerItem *ci;
    string style = "", powerTrain = "", engine = "", transmission = "";
    strcpy(q1, q0.c_str());
    vector<vector<string>> result = query(q1);
    vector<vector<string>>::iterator it;
    vector<string>::iterator it1;
    
    for(it = result.begin(); it != result.end(); it++)
    {
        int col = 0;
        for(it1 = (*it).begin(); it1 != (*it).end(); it1++)
        {
            switch (col)
            {
                case 0:
                    style = (*it1);
                    //ci->setStyleOfCar(style);
                    break;
                case 1:
                    powerTrain = (*it1);
                    //ci->setPowerTrain(powerTrain);
                    break;
                case 2:
                    engine = (*it1);
                    //ci->setEngine(engine);
                    break;
                case 3:
                    transmission = (*it1);
                    //ci->setTransmission(transmission);
                default:
                    break;
            }
            col++;
        }
    }
    
    string q2 = "select itemname from customerMaterialSpecs where itemname like '%Exterior%' or itemname like '%Interior%' and orderid='" + orderId + "';'";
    char *q3 = new char[q2.length() + 1];
    strcpy(q3, q2.c_str());
    vector<vector<string>> result1 = query(q3);
    vector<vector<string>>::iterator it2;
    vector<string>::iterator it3;
    
    string exterior = "", interior = "";
    for(it2 = result1.begin(); it2 != result1.end(); it2++)
    {
        //int col = 0;
        for(it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
        {
            if(hasEnding(*it3, " Exterior"))
            {
                exterior = (*it3);
            }
            else if(hasEnding(*it3, " Interior"))
            {
                interior = (*it3);
            }
        }
    }
    
    ci = new CustomerItem(style, powerTrain, engine, transmission);
    ci->setExterior(exterior);
    ci->setInterior(interior);
    ci->setPowerTrain(powerTrain);
    return ci;
}
