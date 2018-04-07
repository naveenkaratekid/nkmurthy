//
//  OrderDetails.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/6/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef OrderDetails_hpp
#define OrderDetails_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "OrderDetails.hpp"
#include "CustomerItem.hpp"
#include "CustomerOrder.hpp"

class CustomerItem;
class CustomerOrder;
using namespace std;

class OrderDetails
{
public:
    CustomerOrder *co;
    CustomerItem *ci;
    int quantity;
};

#endif /* OrderDetails_hpp */
