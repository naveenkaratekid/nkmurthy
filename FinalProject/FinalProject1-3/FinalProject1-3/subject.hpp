//
//  subject.hpp
//  FinalProject1-3
//
//  Created by Naveen on 11/24/16.
//  Copyright © 2016 KrishnaSwift. All rights reserved.
//

#ifndef subject_hpp
#define subject_hpp

#include <stdio.h>
#include <vector>
#include "observer.hpp"
#include <map>
using namespace std;
class Observer;
class OrderPublisher
{
    vector <Observer*> observerViews;
    //int value;
public:
    void addObserver(Observer *observer);
    void setQuantity(string, string, map<string, int>);
    //int getVal();
    void notifyAll(string, string, map<string, int>);
};

#endif /* subject_hpp */
