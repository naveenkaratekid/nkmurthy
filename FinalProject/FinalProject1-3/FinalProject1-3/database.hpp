//
//  database.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/12/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "Customer.hpp"
#include "CustomerOrder.hpp"
#include "CustomerItem.hpp"
#include <map>
using namespace std;
class Database
{

private:
    Database(char* filename);
    
    ~Database();
    
    bool open(char* filename);
    
public:
    static bool isThereInstance;
    vector<vector<string>> query(char* q);
    void saveCustomerInfo(Customer *);
    void saveCustomerOrderInfo(CustomerOrder*);
    void saveCustomerCarSpecs(CustomerItem *, string);
    //void saveCustomerMaterialSpecs(string, string, string , string, string, string, string);
    void saveCustomerMaterialSpecs(string, map<string, int>);
    void close();
    void updateInventory(map<string, int>, string);
    static Database *instance;
    public:
        static Database *getInstance();
        void createPurchaseOrder(string, map<string, int>);
        void updatePurchaseOrder(string,string, string);
        vector<vector<string>> getOpenPurchaseOrders();
        vector<vector<string>> getOpenCustomerOrders();
        map<string, int> getCustomerOrderMaterialSpecs(string);
        void updateCustomerOrder(string, string);
        void resetCustomerOrderStatus(string, string);
        string getCustomerOrderStatus(string);
        void checkInventoryAndStartBuilding(string, map<string, int>);
        CustomerItem *getCustomerCarOrderInfo(string);
        bool hasEnding(string const&, string const&);
private:
    sqlite3 *db;
};
#endif /* database_hpp */
